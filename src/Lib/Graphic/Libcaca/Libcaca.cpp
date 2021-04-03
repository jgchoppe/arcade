//
// Created by Jean-Gaël Choppe on 17/03/2020.
//


//
// canvas c'est en charatcter les dimensions
// display c'est en pixel les dimensions
//


#include <fstream>
#include <caca.h>
#include <cmath>
#include <iostream>
#include "Libcaca.hpp"

Libcaca::Libcaca() {
    _cv = caca_create_canvas(100, 50);
    // si y a des pb genre la window fait pas la meme taille c'est surmenet a cause du 80 et 42 parce que jsp comment
    // bien les set j'ai l.impression c'est base sur la taille des charactere de ton pc
    _dp = caca_create_display(_cv);
    caca_set_display_title(_dp, "This is Libcaca Arcade");
    std::cout << "Libcaca Library has been loaded" << std::endl;
}

Libcaca::~Libcaca() {
    _operationnal = false;
    std::cout << "caca destructeur" << std::endl;
    caca_free_display(_dp);
}

void Libcaca::drawScreen() {
    caca_refresh_display(_dp);
}

void Libcaca::clearScreen() {
    caca_clear_canvas(_cv);
}

void Libcaca::drawRect(Rect &rect) {
    caca_color co = convertColor(rect.getColor());
    caca_set_color_ansi(_cv, co, co);
    caca_fill_box(_cv, x(rect.getPositionX()), y(rect.getPositionY()), x(rect.getSizeX()), y(rect.getSizeY()), 65);
    caca_set_color_ansi(_cv, CACA_WHITE, CACA_BLACK);
    caca_set_attr(_cv, 0);
}

void Libcaca::drawCircle(Circle &circle) {
    //todo: get coordinate
    caca_color co = convertColor(circle.getColor());
    caca_set_color_ansi(_cv, co, co);
    caca_fill_ellipse(_cv, x(circle.getPositionX()),y(circle.getPositionY()),x(circle.getSizeX() / 2),y(circle.getSizeX() / 2),65);
    caca_set_color_ansi(_cv, CACA_WHITE, CACA_BLACK);
}

void Libcaca::drawSprite(Sprite &sprite) {
    std::string path = sprite.getTextureName() + ".utf8";
    if(caca_import_area_from_file(_cv, x(sprite.getPositionX()), y(sprite.getPositionY()), path.c_str(), "utf8") <= 0)
    {
        path = sprite.getTextureName() + ".txt";
        caca_import_area_from_file(_cv, x(sprite.getPositionX()), y(sprite.getPositionY()), path.c_str(), "text");
    }
}

void Libcaca::drawText(Text &text) {
    caca_color co = convertColor(text.getColor());
    caca_set_color_ansi(_cv, co, CACA_BLACK);
    caca_put_str(_cv, x(text.getPositionX()), y(text.getPositionY()), text.getText().c_str());
    caca_set_color_ansi(_cv, CACA_WHITE, CACA_BLACK);
    caca_set_attr(_cv, 0);
}

bool Libcaca::isOperational() {
    return _operationnal;
}

std::string Libcaca::handleEvent() {
    caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, 100000);
    if(_ev.type == CACA_EVENT_KEY_PRESS)
    {
        for (auto const &x : keyEvent) {
            if (x.first == _ev.data.key.ch) {
                return (x.second);
            }
        }
    }
    return "";
}

caca_color Libcaca::convertColor(Color color) {
    if(color.red == 255 && color.green == 0 && color.blue == 0)
        return CACA_RED;
    if(color.red == 0 && color.green == 255 && color.blue == 0)
        return CACA_GREEN;
    if(color.red == 0 && color.green == 0 && color.blue == 255)
        return CACA_BLUE;
    if(color.red == 255 && color.green == 255 && color.blue == 255)
        return CACA_WHITE;
    if(color.red == 0 && color.green == 0 && color.blue == 0)
        return CACA_BLACK;
    if(color.red == 255 && color.green == 255 && color.blue == 0)
        return CACA_YELLOW;
    if(color.red == 0 && color.green == 255 && color.blue == 255)
        return CACA_CYAN;
    if(color.red == 255 && color.green == 0 && color.blue == 255)
        return CACA_MAGENTA;
    if(color.red == 100 && color.green == 100 && color.blue == 100)
        return CACA_LIGHTGRAY;
    return CACA_WHITE;
}

int Libcaca::x(float x) {
    return (int)std::round(x * (float)caca_get_canvas_width(_cv) / 100);
}

int Libcaca::y(float y) {
    return (int)std::round(y * (float)caca_get_canvas_height(_cv) / 100);
}


int main(void)
{

    Libcaca c;
    Circle ci( Vector2f(50,30), Vector2f(5,0), Color(0,0,0,0));
    Rect r( Vector2f(70,10), Vector2f(10,6), Color(0,0,0,0));
    Text t("bonjour", Vector2f(10,10), Vector2f(0,0), Color(0,0,0,0));
    Sprite s("./test", Vector2f(20,20), Vector2f(0,0));
    c.drawSprite(s);
    c.drawCircle(ci);
    c.drawRect(r);
    c.drawText(t);
    c.drawScreen();
    return 0;
}

// entry point for libcaca Library to load it
extern "C" {
IGraphic *entry() {
    return new Libcaca();
}
}