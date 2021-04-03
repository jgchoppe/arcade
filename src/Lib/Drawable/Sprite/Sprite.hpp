//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_SPRITE_HPP
#define OOP_ARCADE_2019_SPRITE_HPP

#include <functional>
#include <string>
#include "../Size/Size.hpp"
#include "../Position/Position.hpp"

class Sprite: public ASize, public APosition {
public:
    Sprite (const std::string &name, Vector2f pos = Vector2f(0,0), Vector2f size = Vector2f(0,0)):
            _name(name), APosition(pos), ASize(size) {};
    ~Sprite() = default;
    const std::string &getTextureName() const { return _name; }

    bool operator==(Sprite const &s) const
    { return _name == s._name; }
    bool operator<(Sprite const &s) const
    { return _name < s._name; }

private:
    std::string _name;
};

#endif //OOP_ARCADE_2019_SPRITE_HPP
