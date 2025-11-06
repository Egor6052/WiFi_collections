// Scanner.h
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <Network.h>

class Scanner {
public:
    Scanner(const std::string& interface);
    ~Scanner();

    std::string path_to_file = "/home/admin/Documents/";

    bool scanAndSaveNetworks(const std::string& filename);
    
    // static std::string getHomeDirectory();

private:
    std::string interfaceName;
    std::vector<Network> foundNetworks;
    
    void loadNetworksFromFile(const std::string& filename);
    void saveNetworksToFile(const std::string& filename);
};