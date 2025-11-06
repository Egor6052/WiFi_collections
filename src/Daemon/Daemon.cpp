#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <filesystem>
#include "../headers/Daemon.h"

Daemon::Daemon() {
    absolutePath();
    this->servicePath = "/etc/systemd/system/wifi-scanner.service";
    this->dump_path = absolutePath() + "/dumps/";
    // this->configFilePath = absolutePath() + "/conf/configFile.json";
    this->program_path = absolutePath() + "/build/start";
    this->working_directory = absolutePath();

    // this->apiGetJson = "http://192.168.100.1:3000/signalk/v1/api/sources";

    // Configuration();

    // this->operatingFrequency = configData["details"][0].value("operatingFrequency", 1000);
    // this->timeout = configData["details"][0].value("timeout", 1200000);
}


Daemon::~Daemon() {
    // gpioTerminate();
}

std::string Daemon::absolutePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        auto path = std::filesystem::path(std::string(result, count));
        return path.parent_path().parent_path().string();
    } else {
        return "";
    }
}