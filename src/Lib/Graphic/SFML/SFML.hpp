//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_SFML_HPP
#define OOP_ARCADE_2019_SFML_HPP

#include <map>
#include <SFML/Graphics.hpp>
#include "../IGraphic.hpp"

class SFML : public IGraphic {
public:
    // constructor & destructor
    SFML();
    virtual ~SFML() final override;

    // clear function for sfml
    void clearScreen() override;

    // draw functions for sfml
    void drawScreen() override;
    void drawRect(Rect &rect) override;
    void drawCircle(Circle &circle) override;
    void drawSprite(Sprite &sprite) override;
    void drawText(Text &text) override;

    // check if operational for sfml
    bool isOperational() override;

    // handle with SFML Event
    std::string handleEvent() override;

    private:

        // private methods for percent value according to the size of the window
        float x(float value) const { return value * _window.getSize().x / 100; }
        float y(float value) const { return value * _window.getSize().y / 100; }

        // data variables for SFML Library
        sf::RenderWindow _window;
        /*std::map<std::string, s_ptr<sf::Texture> > _textures;
        std::map<std::string, s_ptr<sf::Font> > _fonts;
        std::map<Sprite, s_ptr<sf::Sprite> > _sprites;
        std::map<Text, s_ptr<sf::Text> > _texts;
        std::map<Circle, s_ptr<sf::CircleShape> > _circles;
        std::map<Rect, s_ptr<sf::RectangleShape> > _rects;*/
};


#endif //OOP_ARCADE_2019_SFML_HPP
