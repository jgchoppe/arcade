//
// Created by jean-gael on 30/03/2020.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include "../../Utils/Error.hpp"
#include "SolarFox.hpp"

SolarFox::SolarFox() : _player(50, 50), _mapsFolder(nullptr) {
    srand(time(NULL));
    std::string filesFolder = "";
    _mapsFolder = new OpenFolder(filesFolder, std::regex(""));
    filesFolder = "./resources/map/solarmap/";
    _mapsFolder->loadSimpleFiles(filesFolder, std::regex("map.*[.]txt"));
    _maxScore = 0;
    _player.setScore(0);
    startGame(_mapsFolder->getFiles().getActualBuffer());
}

void SolarFox::startGame(std::string const &filename, int oldScore) {
    int maxScore = _maxScore;
    if (oldScore > _bestScore)
        _bestScore = oldScore;
    _enemies.clear();
    openMap(filename);
    Enemy firstEnemy(20, 20, Enemy::Direction::Right);
    Enemy secondEnemy(80, 80, Enemy::Direction::Left);
    firstEnemy.getRect().setSize(Vector2f(_player.getRect().getSizeX() * 2, _player.getRect().getSizeY() * 2));
    secondEnemy.getRect().setSize(Vector2f(_player.getRect().getSizeX() * 2, _player.getRect().getSizeY() * 2));
    firstEnemy.getRect().setPositionY(20 - (firstEnemy.getRect().getSizeY() / 2) - 3);
    secondEnemy.getRect().setPositionY(80 - (firstEnemy.getRect().getSizeY() / 2) + 3);
    firstEnemy.setProjectilesDirection(Enemy::Direction::Down);
    secondEnemy.setProjectilesDirection(Enemy::Direction::Up);
    _enemies.push_back(firstEnemy);
    _enemies.push_back(secondEnemy);
    _maxScoreMap = _maxScore - maxScore;
}

void SolarFox::handleEvent(std::string &name) {
    if (name == "restart") {
        _maxScore = 0;
        _mapsFolder->getFiles().setIdx(0);
        startGame(_mapsFolder->getFiles().getActualBuffer(), _player.getScore());
        _player.setScore(0);
    }
    name == "right" ? _player.putDirection(Player::Right)
    : name == "left" ? _player.putDirection(Player::Left)
    : name == "up" ? _player.putDirection(Player::Up)
    : name == "down" ? _player.putDirection(Player::Down) : _player.putDirection(Player::NoChange);
    if (name == "enter" && _player.getSpeed() == 0.02f) {
        _player.setSpeed(0.04);
    } else if (name == "enter" && _player.getSpeed() == 0.04f) {
        _player.setSpeed(0.02);
    }
    if (name == "space" && _player.getProjectiles().size() < 2) {
        Projectiles newProjectile(_player.getDirection(), _player.getSpeed() * 3);
        Circle c(
            Vector2f(
                _player.getRect().getPositionX() + _player.getRect().getSize().x / 2,
                _player.getRect().getPositionY() + _player.getRect().getSize().y / 2
            ),
            Vector2f(_player.getRect().getSize().x / 2, _player.getRect().getSize().y / 2),
            Color(0, 0, 255, 255)
        );
        newProjectile.setCircle(c, _player.getRect().getSize());
        _player.addProjectile(newProjectile);
    }
}

void SolarFox::handleUpdate(int elapsedTime) {
    if (_player.getRect().getPositionX() < 20
    || _player.getRect().getPositionX() > 80
    || _player.getRect().getPositionY() < 20
    || _player.getRect().getPositionY() > 80) {
        _maxScore = 0;
        _mapsFolder->getFiles().setIdx(0);
        startGame(_mapsFolder->getFiles().getActualBuffer(), _player.getScore());
        _player.setScore(0);
    }
    _player.moveProjectiles(elapsedTime);
    for (auto it = _maps.begin(); it != _maps.end(); ++it) {
        if ((it->second.second > '0' && it->second.second <= '9')) {
            if (it->second.second == '3') {
                it->second.first.setColor(Color(255, 255, 0, 255));
            } else if (it->second.second == '2') {
                it->second.first.setColor(Color(0, 255, 255, 255));
            } else if (it->second.second == '1') {
                it->second.first.setColor(Color(255, 0, 255, 255));
            }
            int nbCollide = _player.projectilesCollide(it->second);
            _maxScoreMap -= nbCollide;
        }
    }
    for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
        it->move(elapsedTime);
        it->addProjectile(elapsedTime, _player.getScore(), _maxScore);
        it->throwProjectiles(elapsedTime);
        if (it->projectilesCollide(_player.getRect())) {
            _mapsFolder->getFiles().setIdx(0);
            startGame(_mapsFolder->getFiles().getActualBuffer(), _player.getScore());
            _player.setScore(0);
        }
    }
    if (_maxScoreMap == 0) {
        _mapsFolder->getFiles().next();
        if (_mapsFolder->getFiles().getActualIdx() != 0) {
            startGame(_mapsFolder->getFiles().getActualBuffer(), _player.getScore());
        } else {
            _maxScore = 0;
            startGame(_mapsFolder->getFiles().getActualBuffer(), _player.getScore());
            _player.setScore(0);
        }
    }
    _player.move(elapsedTime);
}

void SolarFox::handleRender(IGraphicRenderer &r) {
    r.clearScreen();
    Text name(_player.getName(), Vector2f(2, 2), Vector2f(5, 0), Color(0, 0, 255, 255));
    Text score(std::to_string(_player.getScore()), Vector2f(90, 40), Vector2f(5, 0), Color(0, 0, 255, 255));
    Text score2(std::to_string(_bestScore), Vector2f(90, 60), Vector2f(5, 0), Color(0, 0, 255, 255));

    r.drawText(name);
    r.drawText(score);
    r.drawText(score2);
    Rect map(Vector2f(20, 20), Vector2f(60, 60), Color(255, 255, 255, 255));

    r.drawRect(map);
    auto it = _maps.begin();
    while (it != _maps.end()) {
        if (it->second.second > '0' && it->second.second <= '9') {
            r.drawRect(it->second.first);
        }
        ++it;
    }
    _player.drawProjectiles(r);
    _player.drawPlayer(r);
    for (auto it = _enemies.begin(); it != _enemies.end(); ++it) {
        it->drawProjectiles(r);
        it->drawEnemy(r);
    }
    r.drawScreen();
}

std::map<std::string, std::string> SolarFox::getGameData() {
    std::map<std::string, std::string> data;
    data["score"] = std::to_string(_player.getScore());
    data["name"] = _player.getName();
    return data;
}

void SolarFox::setGameData(std::map<std::string, std::string> &data) {
    if (data.find("name") != data.end())
        _player.setPlayerName(data["name"]);
    _save = new SaveManager("resources/save/" + data["name"], "solarfox");
    loadSave();
}

void SolarFox::openMap(std::string const &path) {
    std::string line;
    std::ifstream mapFile(path);

    _map.clear();
    if (mapFile.is_open()) {
        size_t j = 0;
        size_t i = 0;
        while ( getline (mapFile,line) ) {
            _map.push_back(line);
            for (i = 0; line[i]; ++i) {
                if ((line[i] > '0' && line[i] <= '9') || line[i] == 'P') {
                    auto pair = std::make_pair(i, j);
                    _maps[pair] = std::make_pair(Rect(Vector2f(i, j)), line[i]);
                    if (line[i] != 'P')
                        _maxScore += (int)(line[i] - 48);
                }
            }
            ++j;
        }
        if (_maps.empty())
            return;
        auto it = _maps.begin();
        std::pair<int, int> keyPlayer;
        while (it != _maps.end()) {
            if (it->second.second != 'P') {
                it->second.first.setSize(Vector2f(60 / i, 60 / i));
                it->second.first.setPosition(
                    Vector2f(
                        (48.5 - ((i / 2) * (60 / i))) + ((60 / i) * it->second.first.getPositionX()),
                        (48.5 - ((j / 2) * (60 / i))) + (60 / i) * it->second.first.getPositionY()
                    )
                );
                if (it->second.second == '3') {
                    it->second.first.setColor(Color(255, 255, 0, 255));
                } else if (it->second.second == '2') {
                    it->second.first.setColor(Color(0, 255, 255, 255));
                } else if (it->second.second == '1') {
                    it->second.first.setColor(Color(255, 0, 255, 255));
                }
            } else {
                _player.getRect().setSize(Vector2f(60 / i, 60 / i));
                _player.getRect().setColor(Color(0, 0, 255, 255));
                _player.getRect().setPosition(
                        Vector2f(
                            (48.5 - ((i / 2) * (60 / i))) + ((60 / i)  * it->second.first.getPositionX()),
                            (48.5 - ((j / 2) * (60 / i))) + (60 / i) * it->second.first.getPositionY()
                        )
                );
                keyPlayer = it->first;
            }
            ++it;
        }
        _maps.erase(keyPlayer);
        mapFile.close();
    } else {
        throw Error("SolarFox: map not found");
    }
}

extern "C" {
    IGame *entry() {
        return new SolarFox();
    }
}

void SolarFox::loadSave() {
     _bestScore = _save->loadSave();
}


void SolarFox::save() {
    _save->save(std::to_string(_bestScore));
}

SolarFox::~SolarFox() {
    save();
}
