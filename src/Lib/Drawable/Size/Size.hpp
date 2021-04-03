//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_SIZE_HPP
#define OOP_ARCADE_2019_SIZE_HPP

#include "../Vector/Vector2f.hpp"

class ASize {
public:
    explicit ASize(const Vector2f &size)
    : _size(Vector2f(size.x, size.y)) {};

    // setter
    void setSize(const Vector2f &size) { _size = size; };
    void setSizeX(float sizeX) { _size.x = sizeX; };
    void setSizeY(float sizeY) { _size.y = sizeY; };

    // getter
    Vector2f getSize(void) const { return _size; };
    float getSizeX(void) const { return _size.x; };
    float getSizeY(void) const { return _size.y; };

protected:
    Vector2f _size;
};

#endif //OOP_ARCADE_2019_SIZE_HPP
