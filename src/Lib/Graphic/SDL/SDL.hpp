//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_SDL_HPP
#define OOP_ARCADE_2019_SDL_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
#include "../../../Utils/Using.hpp"
#include "../IGraphic.hpp"

std::map<uint32_t , std::string> keyEvent {
        {SDLK_SPACE, "space"},
        {SDLK_z, "up"},
        {SDLK_q, "left"},
        {SDLK_s, "down"},
        {SDLK_d, "right"},
        {SDLK_RIGHT, "right"},
        {SDLK_LEFT, "left"},
        {SDLK_DOWN, "down"},
        {SDLK_UP, "up"},
        {SDLK_c, "prev_game"},
        {SDLK_e, "next_game"},
        {SDLK_r, "restart"},
        {SDLK_a, "next_graphic"},
        {SDLK_w, "prev_graphic"},
        {SDLK_RETURN, "enter"},
        {SDLK_DELETE, "quit"},
        {SDLK_ESCAPE, "menu"}
};

class SDL : public IGraphic {
public:
    // Constructor & Destructor
    SDL();

    std::string handleEvent() override;

    virtual ~SDL() final override;

    // Methods

    // Draw
    void drawScreen() override;

    void clearScreen() override;

    void drawRect(Rect &rect) override;

    void drawCircle(Circle &circle) override;

    void drawSprite(Sprite &sprite) override;

    void drawText(Text &text) override;

    // Used
    bool isOperational() override;

    // attribut
    SDL_Event windowEvent;
    bool operational = true;
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    // method
    void close();
    void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    // private methods for percent value according to the size of the window
    float x(float value) const { return value * (float)SDL_GetWindowSurface(_window)->w / 100; }
    float y(float value) const { return value * (float)SDL_GetWindowSurface(_window)->h / 100; }
};


#endif //OOP_ARCADE_2019_SDL_HPP
