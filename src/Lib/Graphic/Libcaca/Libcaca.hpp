//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_LIBCACA_HPP
#define OOP_ARCADE_2019_LIBCACA_HPP


#include "../IGraphic.hpp"
#include <caca.h>
#include <map>

std::map<uint32_t , std::string> keyEvent {
        {' ', "space"},
        {'z', "up"},
        {'q', "left"},
        {'s', "down"},
        {'d', "right"},
        {CACA_KEY_RIGHT, "right"},
        {CACA_KEY_LEFT, "left"},
        {CACA_KEY_DOWN, "down"},
        {CACA_KEY_UP, "up"},
        {99, "prev_game"},
        {101, "next_game"},
        {114, "restart"},
        {97, "next_graphic"},
        {119, "prev_graphic"},
        {13, "enter"},
        {127, "quit"},
        {27, "menu"}
};

class Libcaca : public IGraphic {
public:
    Libcaca();
    ~Libcaca() final override;

    void drawScreen() override;
    void clearScreen() override;

    std::string handleEvent() override;

    void drawRect(Rect &rect) override;
    void drawCircle(Circle &circle) override;
    void drawSprite(Sprite &sprite) override;
    void drawText(Text &text) override;
    bool isOperational() override;

private:
    int x(float x);
    int y(float y);
    caca_color convertColor(Color color);
    caca_canvas_t *_cv;
    caca_display_t *_dp;
    caca_event_t _ev;
    bool _operationnal = true;
};


#endif //OOP_ARCADE_2019_LIBCACA_HPP
