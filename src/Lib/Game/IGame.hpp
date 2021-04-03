//
// Created by alexis on 03/03/2020.
//

#ifndef EX06_IGAME_HPP
#define EX06_IGAME_HPP

#include <string>
#include <map>
#include "../Graphic/IGraphic.hpp"

class IGame {
public:
    virtual ~IGame() = default;
    virtual void handleEvent(std::string &name) = 0;
    virtual void handleUpdate(int elapsedTime) = 0;
    virtual void handleRender(IGraphicRenderer &renderer) = 0;
    virtual std::map<std::string, std::string> getGameData() = 0;
    virtual  void setGameData(std::map<std::string, std::string> &data) = 0;
};

#endif //EX06_IGAME_HPP
