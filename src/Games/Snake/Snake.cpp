//
// Created by alexis on 23/03/2020.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "Snake.hpp"

void Snake::handleEvent(std::string &name)
{
    if(name == "right")
    {
        _dir = Vector2f(1,0);
    }
    else if(name == "left")
    {
        _dir = Vector2f(-1,0);
    }
    else if(name == "up")
    {
        _dir = Vector2f(0,1);
    }
    else if(name == "down")
    {
        _dir = Vector2f(0,-1);
    }
    else if(name == "restart")
    {
        resetGane();
    }
}

void Snake::handleUpdate(int elapsedTime)
{
    _time += elapsedTime;
    if(_time <  _speed || (_dir.x == 0 && _dir.y == 0))
        return;
    _time = 0;
    Vector2f v(0,0);
    Vector2f tmp(0,0);


    v.x = _snake[0]->x;
    v.y = _snake[0]->y;
    collision();
    if(_pause)
        return;
    _snake[0]->x += _dir.x;
    _snake[0]->y -= _dir.y;
    if(_snake.size() > 1) {
        for (int i = 1; i < _snake.size(); i++) {
            tmp.x = _snake[i]->x;
            tmp.y = _snake[i]->y;
            _snake[i]->x = v.x;
            _snake[i]->y = v.y;
            v.x = tmp.x;
            v.y = tmp.y;
        }
    }
    appleSpawn(elapsedTime);

}

void Snake::handleRender(IGraphicRenderer &renderer)
{
    renderer.clearScreen();
    Rect r;
    _texts["score"]->setText(std::to_string(score));
    _texts["highScore"]->setText(std::to_string(highScore));
    renderer.drawText(*_texts.at("name"));
    renderer.drawText(*_texts.at("score"));
    renderer.drawText(*_texts.at("highScore"));
    float size = 60 / _map[0].size();
    float startX = 48.5 - ((_map[0].size() / 2) * (size + 1));
    float startY = 48.5 - ((_map.size() / 2) * (size + 1));

    for(int y = 0; y < _map.size(); y++)
    {
        for(int x = 0; x < _map[y].size(); x++)
        {
            if(_map[y][x] == 'x')
            {
                r = Rect(Vector2f(startX + (x * (size + 1)),startY + (y * (size + 1))), Vector2f(size,size), Color(255, 0, 255, 255));
                renderer.drawRect(r);
            }
            if(_map[y][x] == 'o')
            {
                r = Rect(Vector2f(startX + (x * (size + 1)),startY + (y * (size + 1))), Vector2f(size,size), Color(255, 0, 0, 255));
                renderer.drawRect(r);
            }
        }
    }
    for(int i = 1; i < _snake.size(); i++)
    {
        r = Rect(Vector2f(startX + (_snake[i]->x * (size + 1)),startY + (_snake[i]->y * (size + 1))), Vector2f(size,size), Color(0, 0, 255, 255));
        renderer.drawRect(r);
    }
    r = Rect(Vector2f(startX + (_snake[0]->x * (size + 1)),startY + (_snake[0]->y * (size + 1))), Vector2f(size,size), Color(255, 0, 255, 255));
    renderer.drawRect(r);
    renderer.drawScreen();
}

std::map<std::string, std::string> Snake::getGameData()
{
    return std::map<std::string, std::string>();
}

void Snake::setGameData(std::map<std::string, std::string> &data)
{
    _data = data;
    if (data.find( "name") != data.end())
    {
        std::string name;
        name += "Your name: " + _data["name"];
        _texts["name"]->setText(name);
    }
    _save = new SaveManager("resources/save/" + _data["name"], "snake");
    if (data.find( "score") != data.end())
        score = std::atoi(data["score"].c_str());
    loadSave();
}

Snake::Snake(): _dir(Vector2f(0,0))
{
    srand(time(NULL));
    resetGane();
    std::cout << "Snake game has been loaded" << std::endl;
}

void Snake::setMap(std::string filepath) {
    std::string line;
    std::ifstream myfile (filepath);
    _map.clear();
    if (myfile.is_open())
        while ( getline (myfile,line) )
            _map.push_back(line);
    myfile.close();
    for(int i = 0; i < _map.size(); i++)
    {
        appleOnMap += std::count(_map[i].begin(), _map[i].end(), 'o');
    }
}

void Snake::setupSnake() {
    int i = 0;
    int j = 0;
    for(int y = 0; y < _map.size(); y++)
    {
        for(int x = 0; x < _map[y].size(); x++)
        {
            if (_map[y][x] == 'p')
            {
                j = x;
                i = y;
            }
        }
    }
    _snake.clear();
    _snake.push_back(std::make_shared<Vector2f>(Vector2f(j,i)));
    _snake.push_back(std::make_shared<Vector2f>(Vector2f(j-1,i)));
    _snake.push_back(std::make_shared<Vector2f>(Vector2f(j-2,i)));
    _snake.push_back(std::make_shared<Vector2f>(Vector2f(j-3,i)));
}

void Snake::collision() {

    if(_map[_snake[0]->y - _dir.y][_snake[0]->x + _dir.x] == 'o')
    {
        float x = _snake[_snake.size() - 1]->x - _snake[_snake.size() - 2]->x;
        float y = _snake[_snake.size() - 1]->y - _snake[_snake.size() - 2]->y;
        _snake.push_back(std::make_shared<Vector2f>(Vector2f(x,y)));
        _map[_snake[0]->y - _dir.y][_snake[0]->x + _dir.x] = ' ';
        score++;
        if (score > highScore)
            highScore = score;
        if(_speed >= 300)
            _speed -= 100;
        if(_speed >= 200)
            _speed -= 50;
        if(dropRate >= 4000)
            dropRate -= 200;
        appleOnMap--;
    }
    if(_map[_snake[0]->y - _dir.y][_snake[0]->x + _dir.x] == 'x') {
        _pause = true;
        _dir.x = 0;
        _dir.y = 0;
    }
    for(int i = 1; i < _snake.size(); i++)
    {
        if(_snake[0]->y - _dir.y == _snake[i]->y && _snake[0]->x + _dir.x == _snake[i]->x)
        {
            _pause = true;
            _dir.x = 0;
            _dir.y = 0;
        }
    }
}

void Snake::resetGane() {
    _pause = false;
    if(score > highScore)
    {
        highScore = score;
    }
    appleOnMap = 0;
    _speed = 500;
    _time = 0;
    score = 0;
    dropRate = 6000;
    _dir = Vector2f(0,0);
    setMap("./resources/map/mapSnake.txt");
    setupSnake();
    std::string name;
    name += "Your name: " + _data["name"];
    _texts["name"] = std::make_shared<Text>(name, Vector2f(2, 1), Vector2f(3,20), Color(0, 255, 0,255));
    _texts["score"] = std::make_shared<Text>(_data["score"], Vector2f(90, 30), Vector2f(3,20), Color(0, 255, 0,255));
    _texts["highScore"] = std::make_shared<Text>(std::to_string(highScore), Vector2f(90, 35), Vector2f(3,20), Color(0, 255, 0,255));
}

void Snake::appleSpawn(int elapsedTime) {
    if (_dir.x == 0 && _dir.y == 0)
        return;
    int y = 0;
    int x = 0;
    bool loop = true;

    if(appleOnMap <= 0)
    {
        while(loop) {
            y = rand() % ((_map.size() - 2) - 1 + 1) + 1;
            x = rand() % ((_map[0].size() - 2) - 1 + 1) + 1;
            for (int i = 0; i < _snake.size(); i++) {
                if ((x == _snake[i]->x && y == _snake[i]->y) || _map[y][x] == 'x' )
                    continue;
                appleOnMap++;
                _map[y][x] = 'o';
                loop = false;
                break;
            }
        }
    }
}

void Snake::save() {
    _save->save(std::to_string(highScore));
}

Snake::~Snake() {
    save();
}

void Snake::loadSave()
{
    highScore = _save->loadSave();
}


extern "C" {
IGame *entry() {
    return new Snake();
}
}

