#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <Daemon.h> 
#include "Scanner.h"

int main() {
    Daemon daemon;
    daemon.addToStartup();
    
    // Scanner scanner("wlp3s0"); // laptop
    Scanner scanner("wlan0"); // Raspberry

    std::string filename = "wifi_scan_results.csv";
    
    std::cout << "Launching scanning and filtering Wi-Fi networks..." << std::endl;
    
    while (true) {
        if (scanner.scanAndSaveNetworks(filename)) {
            std::cout << "Scan cycle complete. Next scan in 60 seconds." << std::endl;
        } else {
            std::cerr << "Scan cycle error. Next attempt in 60 seconds." << std::endl;
        }
        
        std::cout << "-----------------------------------------------------" << std::endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    
    return 0;
}