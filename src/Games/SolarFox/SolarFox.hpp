//
// Created by jean-gael on 30/03/2020.
//

#ifndef OOP_ARCADE_2019_SOLARFOX_HPP
#define OOP_ARCADE_2019_SOLARFOX_HPP

#include "../SaveManager.hpp"
#include "../../Utils/OpenFolder.hpp"
#include "../../Utils/Using.hpp"
#include "../../Lib/Graphic/IGraphic.hpp"
#include "../../Lib/Game/IGame.hpp"
#include <vector>
#include <string>
#include <map>

#define abs(x) (x < 0 ? x * -1 : x)

class Projectiles {
public:
    enum Direction {
        Right = 0,
        Left,
        Up,
        Down,
        NoChange
    };


    Projectiles(int d, float s)
    : _circle(), _direction(Direction(d)), _speed(s), _basePos(0, 0), _cellSize(0, 0) {};
    ~Projectiles() = default;

    void drawProjectile(IGraphicRenderer &r) {
        r.drawCircle(_circle); };

    Circle &getCircle() { return _circle; }

    void setCircle(Circle &c, Vector2f cellSize) {
        _circle.setPosition(c.getPosition());
        _basePos = c.getPosition();
        _circle.setSize(c.getSize());
        _circle.setColor(c.getColor());
        _cellSize = cellSize;
    }
    
    bool collide(Rect &r) {
        if (_circle.getPositionX() > r.getPositionX()
        && _circle.getPositionX() < r.getPositionX() + r.getSizeX()
        && _circle.getPositionY() > r.getPositionY()
        && _circle.getPositionY() < r.getPositionY() + r.getSizeY()) {
            return true;
        }
        return false;
    }

    virtual bool move(int delta) {
        Vector2f v(0, 0);
        v = _direction == Right ? Vector2f(1, 0) : _direction == Left ? Vector2f(-1, 0)
        : _direction == Up ? Vector2f(0, -1) : _direction == Down ? Vector2f(0, 1) : Vector2f(0, 0);
        _circle.move(Vector2f(v.x * _speed * delta, v.y * _speed * delta));
        if (abs(_circle.getPositionX()) > abs(_basePos.x) + 3 * abs(_cellSize.x)
        || abs(_circle.getPositionY()) > abs(_basePos.y) + 3 * abs(_cellSize.y)) {
            return true;
        } else if ((v == Vector2f(0, -1) || v == Vector2f(-1, 0))
        && (_circle.getPositionX() < _basePos.x - 3 * _cellSize.x
        || _circle.getPositionY() < _basePos.y - 3 * _cellSize.y)) {
            return true;
        }
        return false;
    }

protected:

    float _speed = 0;
    Direction _direction;
    Vector2f _basePos;
    Circle _circle;
    Vector2f _cellSize;
};

class EnemyProjectiles : public Projectiles {
public:
    EnemyProjectiles(int d, float s)
    : Projectiles(d, s) {};

    void setSpeed(float speed) { _speed = speed; };


    bool move(int delta) override {
        Vector2f v(0, 0);
        v = _direction == Up ? Vector2f(0, -1) : _direction == Down ? Vector2f(0, 1) : Vector2f(0, 0);
        _circle.move(Vector2f(v.x * _speed * delta, v.y * _speed * delta));
        if ((_direction == Up && _circle.getPositionY() <= 20) || (_direction == Down && _circle.getPositionY() >= 80)) {
            return true;
        }
        return false;
    }
};

class Enemy {
public:
    enum Direction {
        Right = 0,
        Left,
        Up,
        Down,
        NoChange
    };

    Enemy(int x, int y, Direction d) : _entity(Vector2f(x, y), Vector2f(10, 10), Color(255, 0, 0, 255)), _direction(d) {}

    void drawEnemy(IGraphicRenderer &r) {
        r.drawRect(_entity);
    };

    void move(int delta) {
        Vector2f v(0, 0);
        v.x = _direction == Right ? 1 : -1;
        _entity.moveX(v.x * delta * _speed);
        if (_direction == Right && _entity.getPositionX() >= 80) {
            _direction = Left;
        } else if (_direction == Left && _entity.getPositionX() <= 20) {
            _direction = Right;
        }
    }

    void drawProjectiles(IGraphicRenderer &r) {
        for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it) {
            it->drawProjectile(r);
        }
    }

    void setProjectilesDirection(Direction d) { _pDirection = d; }

    void addProjectile(int delta, int score, int maxScore) {
        _time += delta;
        if (_time >= 1000 && rand() % (maxScore + 2 - score) + 1 == 2) {
            EnemyProjectiles p(_pDirection, _speed * 3);
            Circle c(
                Vector2f(
                    _entity.getPositionX() + _entity.getSize().x / 2,
                    _entity.getPositionY() + _entity.getSize().y / 2
                ),
                Vector2f(_entity.getSize().x / 4, _entity.getSize().y / 4),
                Color(0, 0, 255, 255)
            );
            p.setCircle(c, Vector2f(0, 0));
            _projectiles.push_back(p);
            _time = 0;
        }
    }

    void throwProjectiles(int delta) {
        for (auto it = _projectiles.begin(); it != _projectiles.end();) {
            if (it->move(delta)) {
                it = _projectiles.erase(it);
            } else {
                ++it;
            }
        }
    }

    bool projectilesCollide(Rect &r) {
        for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it) {
            if (it->collide(r)) {
                return true;
            }
        }
        return false;
    }

    Rect &getRect() { return _entity; }
    
private:
    Direction _pDirection = Up;
    Direction _direction = Right;
    float _speed = 0.02;
    Rect _entity;
    float _time = 0;
    std::vector<EnemyProjectiles> _projectiles;
};

class Player {
public:
    enum Direction {
        Right = 0,
        Left,
        Up,
        Down,
        NoChange
    };
    Player(int x, int y, const std::string &name = "Unknown")
    : _player(Vector2f(0, 0), Vector2f(10, 10), Color(255, 0, 0, 255)), _name(name) {
        _moveFct[Right] = &Player::moveRight;
        _moveFct[Left] = &Player::moveLeft;
        _moveFct[Up] = &Player::moveUp;
        _moveFct[Down] = &Player::moveDown;
    };
    ~Player() = default;

    void setScore(int score) { _score = score; }

    std::string getName() const { return _name; };

    int projectilesCollide(std::pair<Rect, char> &pair) {
        int nbCollide = 0;

        for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it) {
            if (it->collide(pair.first)) {
                nbCollide += 1;
                _score += 1;
                pair.second = (char)(pair.second - 1);
            }
        }
        return nbCollide;
    }

    void moveProjectiles(int delta) {
        for (auto it = _projectiles.begin(); it != _projectiles.end();) {
            if (it->move(delta)) {
                it = _projectiles.erase(it);
            } else {
                ++it;
            }
        }
    }
    void addProjectile(Projectiles &p) { _projectiles.push_back(p); }

    Direction getDirection() const { return _direction; }

    void putDirection(Direction d) {
        if (d != _lastDirection) {
            _lastDirection = _direction;
            _direction = d != NoChange ? d : _direction;
        }
    }
    void move(int delta) { if (_moveFct.find(_direction) != _moveFct.end()) { (this->*_moveFct.at(_direction))(delta); }}
    void move(Vector2f &pos) { _player.setPosition(pos); }

    void drawProjectiles(IGraphicRenderer &r) {
        for (auto it = _projectiles.begin(); it != _projectiles.end(); ++it) {
            it->drawProjectile(r);
        }
    };
    void drawPlayer(IGraphicRenderer &r) { r.drawRect(_player); }

    std::vector<Projectiles> getProjectiles() { return _projectiles; };
    int getScore() const { return _score; }
    float getSpeed() const { return _speed; }
    void setSpeed(float speed) {
        _speed = speed;
    }

    void setPlayerName(std::string const &name) { _name = name; };

    Rect &getRect() { return _player; }

private:
    void moveRight(int delta) { _player.moveX(delta * _speed); }
    void moveLeft(int delta) { _player.moveX(-delta * _speed); }
    void moveUp(int delta) { _player.moveY(-delta * _speed); }
    void moveDown(int delta) { _player.moveY(delta * _speed); }

    std::map<Direction, void (Player::*)(int)> _moveFct;
    Direction _direction = Right;
    Direction _lastDirection = Right;
    float _speed = 0.02;
    int _score = 0;
    Rect _player;
    std::string _name;
    std::vector<Projectiles> _projectiles;
};

class SolarFox : public IGame {
public:
    enum Direction {
        Right = 0,
        Left,
        Up,
        Down
    };

    SolarFox();
    ~SolarFox();

    // overrided functions from IGame class
    void handleEvent(std::string &name) override;
    void handleUpdate(int elapsedTime) override;
    void handleRender(IGraphicRenderer &renderer) override;
    std::map<std::string, std::string> getGameData() override ;
    void setGameData(std::map<std::string, std::string> &data) override;

private:
    void save();
    void loadSave();
    void openMap(std::string const &);
    void startGame(std::string const &, int oldScore = 0);
    SaveManager *_save = nullptr;
    int _maxScore = 10000000;
    std::vector<s_ptr<Text> > _texts;
    std::vector<s_ptr<Sprite> > _sprites;
    std::vector<s_ptr<Rect> > _rects;
    std::vector<s_ptr<Circle> > _circles;
    unsigned long int _time = 0;
    Player _player;
    std::vector<std::string> _map;
    std::map<std::pair<int, int>, std::pair<Rect, char>> _maps;
    std::vector<Enemy> _enemies;
    OpenFolder *_mapsFolder;
    int _bestScore = 0;
    int _scoreOnMap = 0;
    int _maxScoreMap = 0;
};

#endif //OOP_ARCADE_2019_SOLARFOX_HPP
