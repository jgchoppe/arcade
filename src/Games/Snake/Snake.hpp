//
// Created by alexis on 23/03/2020.
//

#ifndef OOP_ARCADE_2019_SNAKE_HPP
#define OOP_ARCADE_2019_SNAKE_HPP

#include <map>
#include <vector>
#include "../SaveManager.hpp"
#include "../../Utils/Using.hpp"
#include "../../Lib/Game/IGame.hpp"

class Snake: public IGame {
public:
    Snake();
    ~Snake() override;
    void handleEvent(std::string &name) override;

    void handleUpdate(int elapsedTime) override;

    void handleRender(IGraphicRenderer &renderer) override;

    std::map<std::string, std::string> getGameData();

    void setGameData(std::map<std::string, std::string> &data) override;

private:

private:
    SaveManager *_save = nullptr;
    int appleOnMap = 0;
    int score = 0;
    int highScore = 0;
    int _speed = 500;
    int dropRate = 6000;
    int _time = 0;
    bool _pause = false;
    std::map<std::string, s_ptr<Text> > _texts;
    std::vector<std::string> _map;
    std::vector<s_ptr<Vector2f> > _snake;
    Vector2f _dir;
    std::map<std::string, std::string> _data {
            {"name", "pseudo"},
            {"score", "0"}
    };
    std::string createSaveString();
    void save();
    void loadSave();
    void appleSpawn(int elapsedTime);
    void collision();
    void setMap(std::string filepath);
    void setupSnake();
    void resetGane();
};


#endif //OOP_ARCADE_2019_SNAKE_HPP
