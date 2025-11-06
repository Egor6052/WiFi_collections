#pragma once

#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
// #include <nlohmann/json.hpp>
#include <thread>

// using json = nlohmann::json;

class Daemon {
    private:

        std::string servicePath;

        // std::string configFilePath;
        // json configData;

        std::string dump_path;
        std::string program_path;
        std::string working_directory;
        std::string absolutePath();

        int timeout;
        int operatingFrequency;

    public:
        Daemon();
        ~Daemon();

        // void Configuration();
        // void ConfigFields();

        // void CheckStatus(int pin, bool& status, std::string name_dump_on, std::string name_dump_off, size_t deviceIndex, std::string can_path);

        // std::string getCurrentDateTime();

        void addToStartup();

        void removeFromAutostart();
        // void toggleGyroController();

        // bool readControllerPowerGPIO(int status_pin);

        // void CanPlayer(std::string nameFile, std::string can_path);
        // void CanSend(std::string nameFile, std::string can_path);

        std::string printStatusGyroController(int status_pin);
};
