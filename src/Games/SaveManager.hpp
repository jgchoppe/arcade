//
// Created by alexis on 05/04/2020.
//

#ifndef SPACE_ARCADE_SAVEMANAGER_HPP
#define SPACE_ARCADE_SAVEMANAGER_HPP


#include <string>

class SaveManager {
public:
    SaveManager(std::string filepath, std::string gameName);
    void save(std::string data);
    int loadSave();

private:
    std::string _filepath;
    std::string _game;
};


#endif //SPACE_ARCADE_SAVEMANAGER_HPP
