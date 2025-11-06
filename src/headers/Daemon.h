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

        // std::string getCurrentDateTime();

        void addToStartup();

        void removeFromAutostart();

};
