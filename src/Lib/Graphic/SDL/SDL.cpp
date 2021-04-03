//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
#include <iostream>
#include <cmath>
#include "../../../Utils/Error.hpp"
#include "SDL.hpp"

void SDL::set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(rend, r,g,b,a);
    SDL_RenderDrawPoint(rend, x, y);
    SDL_SetRenderDrawColor(rend, 0,0,0,255);
}

void SDL::drawScreen() {
    SDL_RenderPresent(_renderer);
}

void SDL::clearScreen() {
    SDL_RenderClear(_renderer);
}

void SDL::drawRect(Rect &rect) {
    for(float i = 0; i <  y(rect.getSizeY()); i+= 1.0)
        for(float j = 0; j < x(rect.getSizeX()); j+=1.0)
            set_pixel(_renderer, x(rect.getPositionX()) + j,y(rect.getPositionY()) + i,rect.getColorRed(),rect.getColorGreen(), rect.getColorBlue(), rect.getColorAlpha());
}

void SDL::drawSprite(Sprite &sprite) {
    int w = 0;
    int h = 0;
    // check if the thexture is already loaded
    std::string filepath = sprite.getTextureName() + ".png";
    // get the texture size;
    SDL_Texture *text = IMG_LoadTexture(_renderer, filepath.c_str());
    SDL_QueryTexture(text, NULL, NULL, &w, &h);
    SDL_Rect texr;
    // set rect size and position
    texr.x = x(sprite.getPositionX());
    texr.y = y(sprite.getPositionY());
    texr.w = x(sprite.getSizeX()) ;
    texr.h =  y(sprite.getSizeY()) ;


    // add the texture to the renderer (will be displayed at the next refresh)
    SDL_RenderCopy(_renderer, text, NULL, &texr);
    SDL_DestroyTexture(text);

}
void SDL::drawText(Text &text) {
    int texW = 0;
    int texH = 0;
    TTF_Font * ft = TTF_OpenFont("./resources/font/font1.ttf", x(text.getSizeX()));
    SDL_Color color = { text.getColorRed(), text.getColorGreen(), text.getColorBlue() };
    SDL_Surface * surface = TTF_RenderText_Solid(ft,text.getText().c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(_renderer, surface);
    // get text size
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    // set rect size and postion
    SDL_Rect dstrect = { static_cast<int>(x(text.getPositionX())), static_cast<int>(y(text.getPositionY())), texW, texH };
    // add the text to the renderer (will be displayed at the next refresh)
    SDL_RenderCopy(_renderer, texture, NULL, &dstrect);
    // destroy tmp element
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(ft);
}

bool SDL::isOperational() {
    return operational;
}


void SDL::drawCircle(Circle &circle)
{
    int startX = x(circle.getPositionX());
    int startY = y(circle.getPositionY());
    uint8_t r = circle.getColorRed();
    uint8_t g = circle.getColorGreen();
    uint8_t b = circle.getColorBlue();
    uint8_t a = circle.getColorAlpha();
    for (int dy = 1; dy <= x(circle.getSizeX() / 2);dy++) {
        int dx = floor(sqrt((2.0 * x(circle.getSizeX() / 2) * dy) - (dy * dy)));
        SDL_SetRenderDrawColor(_renderer, r, g, b, a);
        SDL_RenderDrawLine(_renderer, startX - dx, startY + dy - x(circle.getSizeX() / 2), startX + dx, startY + dy - x(circle.getSizeX() / 2));
        SDL_RenderDrawLine(_renderer, startX - dx, startY - dy + x(circle.getSizeX() / 2), startX + dx, startY - dy + x(circle.getSizeX() / 2));
    }
    SDL_SetRenderDrawColor(_renderer, 0,0,0,255);

}

SDL::SDL() {
    SDL_Init( SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    TTF_Init();
    _window = SDL_CreateWindow( "arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 900, SDL_WINDOW_ALLOW_HIGHDPI );
    _renderer = SDL_CreateRenderer(_window, 0,0);
    if ( NULL == _window ) {
        throw Error("SDL: cannot create window " + std::string(SDL_GetError()));
    }
    std::cout << "SDL Library has been loaded" << std::endl;
}

SDL::~SDL() {
    close();
}

std::string SDL::handleEvent() {
    std::string res;
    if (SDL_PollEvent(&windowEvent)) {
        if (SDL_QUIT == windowEvent.type || (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_DELETE))
        {
            close();
            return("quit");
        }
        if(windowEvent.type == SDL_KEYDOWN)
        {
            for (auto const &x : keyEvent)
                if (x.first == windowEvent.key.keysym.sym)
                {
                    return (x.second);
                }
        }
    }
    return "";
}

void SDL::close() {
    if(operational) {
        operational = false;
        if (_window)
        {
            SDL_DestroyWindow(_window);
        }
        TTF_Quit();
        SDL_Quit();
    }
}

// entry point for SDL2 Library to load it
extern "C" {
IGraphic *entry() {
    return new SDL();
    }
}
