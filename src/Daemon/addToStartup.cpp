#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include <Daemon.h>

void Daemon::addToStartup() {
    if (servicePath.empty()) {
        std::cerr << "Error: servicePath is empty!" << std::endl;
        // logError("Error: servicePath is empty!");
        return;
    }

    std::ofstream serviceFile(servicePath, std::ios::out | std::ios::trunc);
    if (!serviceFile) {
        std::cerr << "Could not open " << servicePath << " for writing." << std::endl;
        // logError("Could not open " + servicePath + " for writing.");
        return;
    }

    serviceFile << "[Unit]\n";
    serviceFile << "Description=wifi-scanner\n";
    serviceFile << "After=network.target\n\n";

    serviceFile << "[Service]\n";
    serviceFile << "ExecStart=" << program_path << "\n";
    serviceFile << "Restart=always\n";
    serviceFile << "User=root\n";
    serviceFile << "WorkingDirectory=" + working_directory + "/build\n\n";

    serviceFile << "[Install]\n";
    serviceFile << "WantedBy=multi-user.target\n";

    serviceFile.close();

    int reloadStatus = system("sudo systemctl daemon-reload");
    if (reloadStatus != 0) {
        std::cerr << "Error: Failed to reload systemd daemon!" << std::endl;
        // logError("Error: Failed to reload systemd daemon!");
        return;
    }

    int enableStatus = system("sudo systemctl enable wifi-scanner.service");
    if (enableStatus != 0) {
        std::cerr << "Error: Failed to enable wifi-scanner service!" << std::endl;
        // logError("Error: Failed to enable wifi-scanner service!");
        return;
    }

    std::cout << "\033[1m\033[33mDaemon added to autostart!\033[0m" << std::endl;
}
