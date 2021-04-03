//
// Created by jean-gael on 23/03/2020.
//

#include <fstream>
#include <ostream>
#include "Menu.hpp"

Menu::Menu() {
    _LosTextos["title"] = std::make_shared<Text>("Welcome into the Arc'Bad", Vector2f(5, 0), Vector2f(6, 20),Color(255, 255, 255, 255));
    _LosTextos["key"] = std::make_shared<Text>(" C = prev game  E = next game  A = next graphique  W = prev grahique",Vector2f(0, 95), Vector2f(2.2, 0), Color(255, 255, 255, 255));
    _LosTextos["gameAvailable"] = std::make_shared<Text>("Game available:", Vector2f(30, 20), Vector2f(3, 0),Color(255, 255, 0, 255));
    _LosTextos["libAvailable"] = std::make_shared<Text>("Library available:", Vector2f(30, 20), Vector2f(3, 0),Color(255, 255, 0, 255));
    _LosTextos["selectPseudo"] = std::make_shared<Text>("Pseudo:", Vector2f(30, 80), Vector2f(3, 0),Color(255, 255, 0, 255));
    _spriteMap["pacman"] = std::make_shared<Sprite>("resources/pacman", Vector2f(0,35), Vector2f(20,20));
    _spriteMap["snake"] = std::make_shared<Sprite>("resources/snake", Vector2f(74,35), Vector2f(20,20));
    _pseudoArray.push_back(std::make_shared<Text>("a", Vector2f(36, 85), Vector2f(4, 0),Color(255, 255, 255, 255)));
    _pseudoArray.push_back(std::make_shared<Text>("a", Vector2f(41, 85), Vector2f(4, 0),Color(255, 255, 255, 255)));
    _pseudoArray.push_back(std::make_shared<Text>("a", Vector2f(46, 85), Vector2f(4, 0),Color(255, 255, 255, 255)));
    _pseudoArray.push_back(std::make_shared<Text>("a", Vector2f(51, 85), Vector2f(4, 0),Color(255, 255, 255, 255)));
    _pseudoArray.push_back(std::make_shared<Text>("a", Vector2f(56, 85), Vector2f(4, 0),Color(255, 255, 255, 255)));
    openSave("./resources/save/aaaaa");
}
Menu::~Menu() {

}

void Menu::handleEvent(std::string &name) {
    _return.erase("changeGame");
    _return.erase("changeLib");
    if(name == "down")
    {
        if(_mode == 0)
        {
            if(_pseudoArray[letter]->getText()[0] <= 'a')
                _pseudoArray[letter]->setText("z");
            else {
                std::string tmp = _pseudoArray[letter]->getText();
                tmp[0] -= 1;
                _pseudoArray[letter]->setText(tmp);
            }
            std::string pseudo;
            for(int i = 0; i < _pseudoArray.size(); i++)
                pseudo+= _pseudoArray[i]->getText();
            openSave("./resources/save/" + pseudo);
        }
        else if (_mode == 1)
        {
            if( _idx >= _gameNameList.size() - 1)
                _idx = 0;
            else
                _idx++;
        }
        else if (_mode == 2)
        {
            if( _idx >= _libNameList.size() - 1)
                _idx = 0;
            else
                _idx++;
        }
    }
    if (name == "up")
    {
            ///           PSEUDO
        if(_mode == 0)
        {
            if(_pseudoArray[letter]->getText()[0] >= 'z')
                _pseudoArray[letter]->setText("a");
            else {
                std::string tmp = _pseudoArray[letter]->getText();
                tmp[0] += 1;
                _pseudoArray[letter]->setText(tmp);
            }
            std::string pseudo;
            for(int i = 0; i < _pseudoArray.size(); i++)
                pseudo+= _pseudoArray[i]->getText();
            openSave("./resources/save/" + pseudo);
        }
            ///           GAME
        else if (_mode == 1)
        {
            if( _idx <= 0)
                _idx = _gameNameList.size() - 1;
            else
                _idx--;
        }
        else if (_mode == 2)
        {
            if( _idx <= 0)
                _idx = _libNameList.size() - 1;
            else
                _idx--;
        }
    }
    if (name == "space")
    {
        if(_mode < 2)
            _mode++;
        else
            _mode = 0;
        _idx = 0;
    }
    if(name == "right" && _mode == 0)
    {
        if(letter < 4)
            letter++;
        else
            letter = 0;
    }
    if (name == "left" && _mode == 0)
    {
        if(letter > 0)
            letter--;
        else
            letter = 4;
    }
    if (name == "enter" && _mode == 1)
    {
            _return["changeGame"] = _gameNameList[_idx];
    }
    if (name == "enter" && _mode == 2)
    {
        _return["changeLib"] = _libNameList[_idx];
    }
}

void Menu::handleUpdate(int elaspedTime) {
}

void Menu::handleRender(IGraphicRenderer &renderer) {
    renderer.clearScreen();
    std::string fScore = "score: " + std::to_string(_score);
    Text score(fScore, Vector2f(50 - ((fScore.size() * 3) / 2), 10), Vector2f(5, 5), Color(255, 255, 255, 255));
    renderer.drawText(score);
    renderer.drawText(*_LosTextos["title"]);
    int position = _LosTextos["gameAvailable"]->getPositionY();
    if(_mode != 1)
        _LosTextos["gameAvailable"]->setColor(Color(100, 100, 100, 255));
    else
        _LosTextos["gameAvailable"]->setColor(Color(255, 255, 0, 255));

    renderer.drawText(*_LosTextos["gameAvailable"]);
    renderer.drawSprite(*_spriteMap["pacman"]);
    renderer.drawSprite(*_spriteMap["snake"]);
    position += 5;
    int delta = position ;
    for(int i = 0; i < _games.size();i++)
    {
        _games[i].setPosition(Vector2f(30,delta + (i * 5)));
        if(_mode == 1)
        {
            if (i == _idx)
                _games[i].setColor(Color(255, 0, 0, 255));
            else
                _games[i].setColor(Color(255, 255, 255, 255));
        }
        else
            _games[i].setColor(Color(100, 100, 100, 255));
        position += 5;
        renderer.drawText(_games[i]);
    }
    if(_mode != 2)
        _LosTextos["libAvailable"]->setColor(Color(100, 100, 100, 255));
    else
        _LosTextos["libAvailable"]->setColor(Color(255, 255, 0, 255));
    _LosTextos["libAvailable"]->setPosition(Vector2f(30, position));
    renderer.drawText(*_LosTextos["libAvailable"]);
    position += 5;
    delta = position;
    for(int i = 0; i < _libs.size();i++)
    {
        _libs[i].setPosition(Vector2f(30,delta + (i * 5)));
        if(_mode == 2)
        {
            if (i == _idx)
                _libs[i].setColor(Color(255, 0, 0, 255));
            else
                _libs[i].setColor(Color(255, 255, 255, 255));
        }
        else
            _libs[i].setColor(Color(100, 100, 100, 255));
        renderer.drawText(_libs[i]);
        position += 5;
    }
    if(_mode != 0)
        _LosTextos["selectPseudo"]->setColor(Color(100, 100, 100, 255));
    else
        _LosTextos["selectPseudo"]->setColor(Color(255, 255, 0, 255));

    renderer.drawText(*_LosTextos["selectPseudo"]);
    _LosTextos["selectPseudo"]->setPositionY(position);
    for(int i = 0; i < _pseudoArray.size(); i++)
    {
        _pseudoArray[i]->setPosition(Vector2f(36 + (i * 5), position + 5));
        if(_mode == 0) {
            if (i == letter) {
                _pseudoArray[i]->setColor(Color(255, 0, 0, 255));
            } else
                _pseudoArray[i]->setColor(Color(255, 255, 255, 255));
        }
        else
            _pseudoArray[i]->setColor(Color(100, 100, 100, 255));
        renderer.drawText(*_pseudoArray[i]);
    }

    renderer.drawScreen();
}

void Menu::setGameData(std::map<std::string, std::string> &data) {
    _data = data;
    _gameNameList = strToTab(_data["gameList"], ":", _games);
    _libNameList = strToTab(_data["libList"], ":", _libs);
    if(data.find("pseudo") != data.end() && !data["pseudo"].empty()) {
        for (int i = 0; i < _pseudoArray.size(); i++) {

            _pseudoArray[i]->setText(std::string(1, data["pseudo"][i]));
        }
        openSave("./resources/save/" + data["pseudo"]);
    }
}

void Menu::openSave(std::string const &path) {
    std::string line;
    std::ifstream saveFile(path);
    size_t fscore = 0;

    if (saveFile.is_open()) {
        while (getline(saveFile, line)) {
            size_t pos = line.find_first_of(':');
            if (pos != std::string::npos) {
                std::string linescore = line.substr(pos + 1, line.size());
                fscore = fscore + std::stoi(linescore);
            }
        }
    }
    _score = fscore;
}

std::map<std::string, std::string> Menu::getGameData() {
    _return.erase("pseudo");
    for(int i = 0; i < _pseudoArray.size(); i++)
        _return["pseudo"]+= _pseudoArray[i]->getText();
    return _return;
}

std::vector<std::string> Menu::strToTab(std::string str, std::string delimeter, std::vector<Text> &vec) {
    size_t pos = 0;
    std::string token;
    std::vector<std::string> res;


    while ((pos = str.find(delimeter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        res.push_back(token);
        vec.emplace_back(token, Vector2f(5,0), Vector2f(3,0), Color(255,255,255,255));
        str.erase(0, pos + delimeter.length());
    }
    if((pos = str.find(delimeter)) == std::string::npos)
    {
        token = str.substr(0, pos);
        res.push_back(token);
        vec.emplace_back(token, Vector2f(5,0), Vector2f(3,0), Color(255,255,255,255));
    }
    return res;
}

void Menu::selectLib() {

}
