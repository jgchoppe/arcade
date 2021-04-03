//
// Created by alexis on 05/04/2020.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "SaveManager.hpp"

SaveManager::SaveManager(std::string filepath, std::string gameName): _filepath(filepath), _game(gameName) {
}

void SaveManager::save(std::string data) {
    std::string res = _game + ":" + data;
    std::string final;
    std::string line;
    std::vector<std::string> tmp;
    std::ifstream ifile;
    std::ofstream ofile;
    ifile = std::ifstream (_filepath);
    while(getline(ifile, line)) {
        tmp.push_back(line);
    }
    ifile.close();
    ofile = std::ofstream (_filepath, std::ofstream::out | std::ofstream::trunc);
    for(int i = 0; i < tmp.size(); i++)
    {
        if(tmp[i].find(_game) == std::string::npos)
            final+= tmp[i] + "\n";
    }
    final += res;
    ofile << final;
    ofile.close();
}

int SaveManager::loadSave() {
    std::vector<std::string> vec;
    std::string data;
    std::string path;
    std::ifstream ifFile;
    ifFile = std::ifstream(_filepath);
    while (getline(ifFile, data)) {
        if(data.find(_game) != std::string::npos) {
            if (!data.empty()) {
                std::string info = data.substr(data.find(':') + 1);
                return std::stoi(info);
            }
        }
    }
    ifFile.close();
    return 0;
}