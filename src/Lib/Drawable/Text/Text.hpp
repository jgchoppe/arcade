//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_TEXT_HPP
#define OOP_ARCADE_2019_TEXT_HPP

#include <string>
#include "../Color/Color.hpp"
#include "../Size//Size.hpp"
#include "../Position/Position.hpp"

class Text: public AColor, public ASize, public APosition{
public:
    Text(const std::string &str, Vector2f pos = Vector2f(0,0), Vector2f size = Vector2f(0,0), Color color = Color(0,0,0,0)):
            _text(str), APosition(pos), ASize(size), AColor(color) {};
    ~Text() = default;

    // getter
    const std::string &getText() const { return _text; };

    // setter
    void setText(const std::string &newText) { _text = newText; };

    // overload  operators
    bool operator==(Text const &t) const { return _text == t._text; }
    bool operator<(Text const &t) const { return _text < t._text; }

private:
    // todo: add _text
    std::string _text;
};

#endif //OOP_ARCADE_2019_TEXT_HPP
