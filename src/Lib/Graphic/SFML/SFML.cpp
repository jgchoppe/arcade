//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#include <iostream>
#include "../../../Utils/Error.hpp"
#include "SFML.hpp"

std::map<sf::Keyboard::Key, std::string> events {
    {sf::Keyboard::Key::Z, "up"},
    {sf::Keyboard::Key::Q, "left"},
    {sf::Keyboard::Key::S, "down"},
    {sf::Keyboard::Key::D, "right"},
    {sf::Keyboard::Key::Left, "left"},
    {sf::Keyboard::Key::Right, "right"},
    {sf::Keyboard::Key::Down, "down"},
    {sf::Keyboard::Key::Up, "up"},
    {sf::Keyboard::Key::Space, "space"},
    {sf::Keyboard::Key::C, "prev_game"},
    {sf::Keyboard::Key::E, "next_game"},
    {sf::Keyboard::Key::R, "restart"},
    {sf::Keyboard::Key::A, "next_graphic"},
    {sf::Keyboard::Key::W, "prev_graphic"},
    {sf::Keyboard::Key::Escape, "menu"},
    {sf::Keyboard::Key::Return, "enter"},
    {sf::Keyboard::Key::Delete, "quit"}
};

// constructor for SFML Library
SFML::SFML() : _window(sf::VideoMode(900, 900), "Arcade",sf::Style::Titlebar | sf::Style::Close) {
    std::cout << "SFML Library has been loaded" << std::endl;
}

// destructor for SFML Library
SFML::~SFML() {
    if(_window.isOpen())
        _window.close();
}

// display sfml window
void SFML::drawScreen() {
    _window.display();
}

// clear sfml window
void SFML::clearScreen() {
    _window.clear();
}

// draw sfml rect
void SFML::drawRect(Rect &rect) {
    sf::RectangleShape r((sf::Vector2f){
        x(rect.getSizeX()),
        y(rect.getSizeY())
    });

    // set color
    r.setFillColor((sf::Color){
        rect.getColor().red,
        rect.getColor().green,
        rect.getColor().blue,
        rect.getColor().alpha
    });

    // update position and rect size
    r.setSize((sf::Vector2f){x(rect.getSizeX()), y(rect.getSizeY())});
    r.setPosition(x(rect.getPositionX()), y(rect.getPositionY()));
    
    // draw rect
    _window.draw(r);
}


// draw circle rect
void SFML::drawCircle(Circle &circle) {
    sf::CircleShape *c = new sf::CircleShape(
        x(circle.getSizeX())
    );
    
    // set color to the rect
    c->setFillColor((sf::Color){
        circle.getColor().red,
        circle.getColor().green,
        circle.getColor().blue,
        circle.getColor().alpha
    });
    
    // update position and circle size
    c->setOrigin(x(circle.getSize().x / 2), y(circle.getSize().x / 2));
    c->setRadius(x(circle.getSizeX() / 2));
    c->setPosition(x(circle.getPositionX()), y(circle.getPositionY()));
    
    // draw circle
    _window.draw(*c);
    delete c;
}


// draw sfml sprite
void SFML::drawSprite(Sprite &sprite) {
    sf::Texture *t = new sf::Texture();
    if (!t->loadFromFile(sprite.getTextureName() + ".png"))
        throw Error("SFML: cannot create new texture");
    sf::Sprite *s = new sf::Sprite(*t);
    
    // update position and sprite size
    s->setPosition(x(sprite.getPositionX()), y(sprite.getPositionY()));

    sf::Vector2<unsigned int> tSize = t->getSize();
    sf::Vector2f sSize;
    sSize.x = x(sprite.getSizeX());
    sSize.y = y(sprite.getSizeY());
    s->setScale(
            sf::Vector2f(
                    sSize.x / tSize.x,
                    sSize.y / tSize.y
            )
    );
    // draw sprite
    _window.draw(*s);
    delete s;
    delete t;
}


// draw sfml text
void SFML::drawText(Text &text) {
    sf::Font font;
    if (!font.loadFromFile("./resources/font/font1.ttf"))
        throw Error("SFML: cannot create font");
    sf::Text *t = new sf::Text(
        text.getText(),
        font,
        17
    );
    
    // set color
    t->setFillColor((sf::Color){
        text.getColor().red,
        text.getColor().green,
        text.getColor().blue,
        text.getColor().alpha
    });
    
    // update position and text size
    t->setPosition(x(text.getPositionX()), y(text.getPositionY()));
    if(text.getSizeX() != 0)
        t->setCharacterSize(x(text.getSizeX()));
    
    // draw
    _window.draw(*t);
    delete t;
}


// check is sfml window is open by return a bool
bool SFML::isOperational() {
    return _window.isOpen();
}

std::string SFML::handleEvent() {
    sf::Event e;

    while (_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
        	_window.close();
            return "quit";
        }
        if (e.type == sf::Event::KeyPressed) {
            if (events.find(e.key.code) != events.end()) {
                if (events[e.key.code] == "quit")
                    _window.close();
                return events[e.key.code];
            }
        }
    }
    return "";
}

// entry point for SFML Library to load it
extern "C" {
    IGraphic *entry() {
        return new SFML();
    }
}

