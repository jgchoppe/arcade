//
// Created by alexis on 16/03/2020.
//

#ifndef OOP_ARCADE_2019_CORE_HPP
#define OOP_ARCADE_2019_CORE_HPP

#include "../Utils/Using.hpp"
#include "../Utils/RingBufferString.hpp"
#include "../Utils/OpenFolder.hpp"
#include "../Clock/Clock.hpp"
#include "../Lib/Graphic/IGraphic.hpp"
#include "../Lib/Game/IGame.hpp"
#include "../Loader/SoLoader.hpp"
#include "../Menu/Menu.hpp"
#include <string>
#include <vector>

class Core {
public:
    Core(std::string &libsPath, std::string &gamesPath)
    : _lgraph(nullptr), _game(nullptr),
    _gameLoader(nullptr), _graphLoader(nullptr),menu(nullptr),
    _libs(libsPath, std::regex("lib_arcade_.*[.]so")),
    _games(gamesPath, std::regex("lib_arcade_.*[.]so")) {
        _ptr["next_graphic"] = &Core::nextLib;
        _ptr["prev_graphic"] = &Core::prevLib;
        _ptr["next_game"] = &Core::nextGame;
        _ptr["prev_game"] = &Core::prevGame;
        _ptr["quit"] = &Core::quitArcade;
        _ptr["menu"] = &Core::loadMenu;
//        useGame("./games/game_arcade_snake2.so");
        loadMenu();
    };
    ~Core();

    void useGraphic(const std::string &filename);
    void useGame(const std::string &filename);
    void run(void);

private:
    void handleEvents(void);
    void nextGame(void);
    void prevGame(void);
    void quitArcade(void);
    void prevLib(void);
    void nextLib(void);
    void loadMenu(void);
    void parseGaneData(std::map<std::string,std::string>  data);
    std::vector<std::string> parseLibPath(std::vector<std::string> data);

    std::map<std::string, void (Core::*)(void)> _ptr;
    OpenFolder _libs;
    OpenFolder _games;
    Clock *_clock;
    IGraphic *_lgraph;
    bool _isQuit = false;
    IGame *_game;
    SoLoader<IGraphic> *_graphLoader;
    SoLoader<IGame> *_gameLoader;
    IGame *menu;
    float fps = 30;
    std::string _pseudo;
};


#endif //OOP_ARCADE_2019_CORE_HPP
