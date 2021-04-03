//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_POSITION_HPP
#define OOP_ARCADE_2019_POSITION_HPP

#include "../Vector/Vector2f.hpp"

class APosition {
public:
    explicit APosition(const Vector2f &pos)
    : _pos(Vector2f(pos.x, pos.y)) {};

    // setters
    void setPosition(const Vector2f pos) { _pos = pos; };
    void setPositionX(float posX) { _pos.x = posX; };
    void setPositionY(float posY) { _pos.y = posY; };

    void move(const Vector2f pos) { _pos += pos; };
    void moveX(float movex) { _pos.x += movex; };
    void moveY(float movey) { _pos.y += movey; };

    // getters
    Vector2f getPosition(void) const { return _pos; };
    float getPositionX(void) const { return _pos.x; };
    float getPositionY(void) const { return _pos.y; };

protected:
    Vector2f _pos;
};

#endif //OOP_ARCADE_2019_POSITION_HPP
