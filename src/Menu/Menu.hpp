//
// Created by jean-gael on 23/03/2020.
//

#ifndef OOP_ARCADE_2019_MENU_HPP
#define OOP_ARCADE_2019_MENU_HPP

#include "../Utils/Using.hpp"
#include "../Lib/Graphic/IGraphic.hpp"
#include "../Lib/Game/IGame.hpp"
#include <string>
#include <map>
#include <vector>


class Menu : public IGame {
public:
    Menu();
    ~Menu() final override;

    void handleEvent(std::string &name) override;
    void handleUpdate(int elapsedTime) override;
    void handleRender(IGraphicRenderer &renderer) override;
    std::map<std::string, std::string> getGameData() override ;
    void setGameData(std::map<std::string, std::string> &data) override;

private:
    void openSave(std::string const &path);

    std::vector<s_ptr<Text> > _pseudoArray;
    std::map<std::string, s_ptr<Text> > _LosTextos;
    std::map<std::string, s_ptr<Sprite> > _spriteMap;
    int _mode = 0;
    int letter = 0;
    std::vector<Text> _games;
    std::vector<Text> _libs;
    int _idx = 0;
    std::vector<std::string> _gameNameList;
    std::vector<std::string> _libNameList;
    std::map<std::string, std::string> _return;
    std::map<std::string, std::string> _data;
    std::vector<std::string> strToTab(std::string str, std::string delimeter, std::vector<Text> &vec);
    void selectLib();
    size_t _score = 0;

};


#endif //OOP_ARCADE_2019_MENU_HPP
