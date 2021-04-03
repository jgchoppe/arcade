//
// Created by alexis on 16/03/2020.
//

#include <cmath>
#include "Core.hpp"
#include <thread>
#include <unistd.h>

void Core::useGraphic(const std::string &filename) {
    if (!_graphLoader) {
        int idx = _libs().find(filename);
        if (idx == -1) {
            throw Error("Core: cannot find the library " + filename);
        }
        _libs().setIdx(idx);
        _graphLoader = new SoLoader<IGraphic>(filename);
    }
    if(_lgraph) {
        delete _lgraph;
    }
    _graphLoader->load(filename);
    _lgraph = _graphLoader->getInstance();
}

void Core::useGame(const std::string &filename) {
    std::map<std::string, std::string> dataMap;
    dataMap["name"] = _pseudo;
    if (!_gameLoader) {
        int idx = _games().find(filename);
        if(idx == -1) {
            throw Error("Core: cannot find the game " + filename);
        }
        _games().setIdx(idx);
        _gameLoader = new SoLoader<IGame>(filename);
    }
    if(_game)
    {
        delete _game;
    }
    _gameLoader->load(filename);
    _game = _gameLoader->getInstance();
    _game->setGameData(dataMap);
}

void Core::handleEvents() {
    std::string event = _lgraph->handleEvent();

    if (_ptr.find(event) != _ptr.end())
        (this->*_ptr.at(event))();
    else
        _game->handleEvent(event);
}

void Core::nextGame() {
    useGame(_games().next());

}

void Core::prevGame() {
    useGame(_games().prev());
}

void Core::quitArcade() {
    _isQuit = true;
}

void Core::prevLib() {
    useGraphic(_libs().prev());
}

void Core::nextLib(void) {
    useGraphic(_libs().next());
}

void Core::loadMenu(void) {
    std::map<std::string, std::string> data;
    std::vector<std::string> gameList = parseLibPath(_games().getData());
    std::vector<std::string> libList = parseLibPath(_libs().getData());
    std::string gameListString;
    std::string libListString;
    for(int i = 0; i < gameList.size(); i++)
        gameListString += gameList[i] + ":";
    for(int i = 0; i < libList.size(); i++)
        libListString += libList[i] + ":";
    if(!libListString.empty())
        libListString.pop_back();
    if(!gameListString.empty())
        gameListString.pop_back();
    data["gameList"] = gameListString;
    data["libList"] = libListString;
    data["pseudo"] = _pseudo;
    if(_game)
    {
        delete _game;
    }
    _game = new Menu();
    _game->setGameData(data);
}

void Core::run() {
    std::string events;

    if (!_lgraph || !_game) {
        throw Error("Core: graphic or game hasn't been initiated");
    }
    _clock = new Clock;
    while (_lgraph->isOperational()) {
        // events
        handleEvents();

        // update
        if(!_isQuit) {
            if((1000 / fps) > (_clock->getElapsedTimeSinceLastReset() * 1000)) {
                long x = (1000 / fps) - (_clock->getElapsedTimeSinceLastReset() * 1000);
                std::this_thread::sleep_for(std::chrono::milliseconds(x));
            }
            _game->handleUpdate(_clock->getElapsedTimeSinceLastReset() * 1000);
            _clock->reset();
        }


        // display
        if(!_isQuit)
            _game->handleRender(*_lgraph);

        if(!_isQuit)
            parseGaneData(_game->getGameData());
    }
}

Core::~Core() {
    if (_lgraph)
        delete _lgraph;
    if (_game)
        delete _game;
    if (menu)
        delete menu;
    if(_graphLoader)
        delete _graphLoader;
    if (_gameLoader)
        delete _gameLoader;
    if (_clock)
        delete _clock;
}

std::vector<std::string> Core::parseLibPath(std::vector<std::string> data) {
    std::vector<std::string> onlyEnd;
    for(int i = 0; i < data.size(); i++)
    {
        int last = data[i].find_last_of('/');
        onlyEnd.push_back(data[i].substr(last+1));
    }
    return onlyEnd;
}

void Core::parseGaneData(std::map<std::string,std::string>  data) {
    if(data.find("changeLib") != data.end())
    {
        int idx = _libs().find("./lib/" + data["changeLib"]);
        if(idx == -1)
        {
            std::cout << "Core.cpp l.14 dont't find the game in the ringBuffer" << std::endl;
            throw std::exception();
        }
        _libs().setIdx(idx);
        useGraphic("./lib/" + data["changeLib"]);
    }
    if(data.find("changeGame") != data.end())
    {
        int idx = _games().find("./games/" + data["changeGame"]);
        if(idx == -1)
        {
            std::cout << "Core.cpp l.14 dont't find the game in the ringBuffer" << std::endl;
            throw std::exception();
        }
        _games().setIdx(idx);
        useGame("./games/" + data["changeGame"]);
    }
    if(data.find("pseudo") != data.end())
    {
        _pseudo = data["pseudo"];
    }

}