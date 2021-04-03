//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_RECT_HPP
#define OOP_ARCADE_2019_RECT_HPP

#include "../Vector/Vector2f.hpp"
#include "../Color/Color.hpp"
#include "../Size/Size.hpp"
#include "../Position/Position.hpp"

class Rect : public AColor, public ASize, public APosition {
public:
    explicit Rect (Vector2f pos = Vector2f(0,0), Vector2f size = Vector2f(0,0), Color color = Color(0,0,0,0))
    : APosition(pos), ASize(size), AColor(color) {};
    ~Rect() = default;

    bool operator==(Rect const &r) const { return _size.x == r._size.x; }
    bool operator<(Rect const &r) const { return _size.x < r._size.x; }
};

#endif //OOP_ARCADE_2019_RECT_HPP