//
// Created by alexis on 03/03/2020.
//

#ifndef EX06_IGRAPH_HPP
#define EX06_IGRAPH_HPP

#include "../Drawable/Drawable.hpp"

class IGraphicRenderer {
public:
    virtual ~IGraphicRenderer() = default;

    virtual void drawScreen() = 0;

    virtual void clearScreen() = 0;

    virtual void drawRect(Rect &rect) = 0;

    virtual void drawCircle(Circle &circle) = 0;

    virtual void drawSprite(Sprite &sprite) = 0;

    virtual void drawText(Text &text) = 0;

    IGraphicRenderer &operator=(const IGraphicRenderer &) = delete;
};

class IGraphic: public IGraphicRenderer {
public:
    IGraphic() = default;

    IGraphic(const IGraphic &) = delete;

    virtual ~IGraphic() = default;

    virtual bool isOperational() = 0;

    virtual std::string handleEvent() = 0;
};

#endif //EX06_IGRAPH_HPP
