#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

#include <Scanner.h>
#include <Network.h>

Scanner::Scanner(const std::string& interface) : interfaceName(interface) {}

Scanner::~Scanner() {}

// Оновлена функція для завантаження мереж з файлу
void Scanner::loadNetworksFromFile(const std::string& filename) {
    std::string full_path = path_to_file + filename;
    foundNetworks.clear();
    std::ifstream file(full_path);

    if (!file.is_open()) {
        std::cout << "Warning: file " << filename << " not found. A new one will be created." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Пропускаємо заголовок

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t firstCommaPos = line.find(",");
        if (firstCommaPos == std::string::npos) continue;

        size_t secondCommaPos = line.find(",", firstCommaPos + 1);
        if (secondCommaPos == std::string::npos) continue;

        Network net;
        net.ssid = line.substr(0, firstCommaPos);
        net.bssid = line.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1);
        net.firstSeenDate = line.substr(secondCommaPos + 1);

        if (!net.bssid.empty()) {
            foundNetworks.push_back(net);
        }
    }
    
    std::cout << "Uploaded " << foundNetworks.size() << " networks from a file." << std::endl;
    file.close();
}

void Scanner::saveNetworksToFile(const std::string& filename) {

    std::string full_path = path_to_file + filename;
    std::cout << "DEBUG: Attempting to save to file: " << full_path << std::endl; // Корисний відладочний вивід

    std::ofstream file(full_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing " << full_path << std::endl;
        return;
    }

    file << "SSID,BSSID,Date" << std::endl;

    // Цей цикл просто не виконається жодного разу, якщо foundNetworks порожній
    for (const auto& net : foundNetworks) {
        if (!net.bssid.empty()) {
            file << net.ssid << "," << net.bssid << "," << net.firstSeenDate << std::endl;
        }
    }

    std::cout << "Saved " << foundNetworks.size() << " unique networks in a file " << filename << std::endl;
    file.close();
}

// Оновлена логіка сканування
bool Scanner::scanAndSaveNetworks(const std::string& filename) {
    loadNetworksFromFile(filename);

    std::vector<Network> currentScanNetworks;
    std::string command = "iwlist " + interfaceName + " scan 2>/dev/null";
    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe) {
        std::cerr << "Command execution error: " << command << std::endl;
        return false;
    }

    char buffer[256];
    std::string line;
    Network currentNetwork;
    bool inCell = false;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        line = buffer;
        if (line.find("Cell ") != std::string::npos) {
            if (inCell && !currentNetwork.bssid.empty()) currentScanNetworks.push_back(currentNetwork);
            inCell = true;
            currentNetwork = Network();
        }
        size_t bssidPos = line.find("Address: ");
        if (bssidPos != std::string::npos) {
            currentNetwork.bssid = line.substr(bssidPos + 9);
            currentNetwork.bssid.erase(currentNetwork.bssid.find_last_not_of(" \n\r\t") + 1);
        }
        size_t ssidPos = line.find("ESSID:\"");
        if (ssidPos != std::string::npos) {
            currentNetwork.ssid = line.substr(ssidPos + 7);
            currentNetwork.ssid.erase(currentNetwork.ssid.find_last_not_of("\"\n\r\t") + 1);
        }
    }
    if (inCell && !currentNetwork.bssid.empty()) currentScanNetworks.push_back(currentNetwork);
    pclose(pipe);

    std::cout << "Scanned " << currentScanNetworks.size() << " networks in the current session." << std::endl;

    // Отримуємо поточну дату
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm buf;

    // Залежність від системи
    #ifdef _WIN32
        localtime_s(&buf, &in_time_t);
    #else
        localtime_r(&in_time_t, &buf);
    #endif
    char dateStr[11];
    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &buf);
    std::string currentDate(dateStr);

    // Фільтруємо нові мережі і додаємо лише унікальні з поточною датою
    int newNetworksCount = 0;
    for (auto& newNetwork : currentScanNetworks) {
        auto it = std::find_if(foundNetworks.begin(), foundNetworks.end(),
                               [&newNetwork](const Network& existingNet) {
                                   return existingNet.bssid == newNetwork.bssid;
                               });

        // Якщо мережі не знайдено - це нова мережа
        if (it == foundNetworks.end()) {
            newNetwork.firstSeenDate = currentDate;
            foundNetworks.push_back(newNetwork);
            newNetworksCount++;
            std::cout << "New network: SSID=" << newNetwork.ssid 
                      << ", BSSID=" << newNetwork.bssid 
                      << ", Date=" << newNetwork.firstSeenDate << std::endl;
        }
    }

    if (newNetworksCount > 0) {
        std::cout << "Added " << newNetworksCount << " new unique networks to the database." << std::endl;
    } else if (!currentScanNetworks.empty()) {
        std::cout << "No new unique networks were found." << std::endl;
    }

    saveNetworksToFile(filename);

    return true;
}

