//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_CIRCLE_HPP
#define OOP_ARCADE_2019_CIRCLE_HPP

#include "../Color/Color.hpp"
#include "../Size/Size.hpp"
#include "../Position/Position.hpp"

class Circle: public AColor, public ASize, public APosition {
public:
    explicit Circle(Vector2f pos = Vector2f(0,0), Vector2f size = Vector2f(0,0), Color color = Color(0,0,0,0))
    : APosition(pos), ASize(size), AColor(color) {};
    ~Circle() = default;

    bool operator==(Circle const &c) const
    { return _size == c._size; }
        bool operator<(Circle const &c) const
    { return _size < c._size; }
};

#endif //OOP_ARCADE_2019_CIRCLE_HPP
