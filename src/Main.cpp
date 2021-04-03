//
// Created by alexis on 03/03/2020.
//

#include <string>
#include "Lib/Graphic/IGraphic.hpp"
#include "Lib/Game/IGame.hpp"
#include "Core/Core.hpp"

int main(int argc, char **argv) {
    std::string libsPath = "./lib/";
    std::string gamesPath = "./games/";
    Core *arcade = new Core(libsPath, gamesPath);
    if(argc != 2)
        return 84;
    arcade->useGraphic(argv[1]);

    arcade->run();
    delete(arcade);
}