//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_COLOR_HPP
#define OOP_ARCADE_2019_COLOR_HPP

class Color {
public:
    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
    : red(red), blue(blue), green(green), alpha(alpha) {};

    static Color Red() { return Color(255, 0, 0, 255); };
    static Color Blue() { return Color(0, 0, 255, 255); };
    static Color Green() { return Color(0, 255, 0, 255); };
    static Color Black() { return Color(0, 0, 0, 255); };
    static Color White() { return Color(255, 255, 255, 255); };
    static Color Transparent() { return Color(0, 0, 0, 0); };
    unsigned char red;
    unsigned char blue;
    unsigned char green;
    unsigned char alpha;
};

class AColor {
public:
    explicit AColor(const Color &color)
    : _col(Color(color.red, color.green, color.blue, color.alpha)) {};

    // setters
    void setColor(const Color &color) { _col = color; };
    void setColorRed(unsigned char red) { _col.red = red; };
    void setColorGreen(unsigned char green) { _col.green = green; };
    void setColorBlue(unsigned char blue) { _col.blue = blue; };
    void setColorAlpha(unsigned char alpha) { _col.alpha = alpha; };

    // getters
    Color getColor(void) const { return _col; };
    unsigned char getColorRed(void) const { return _col.red; };
    unsigned char getColorBlue(void) const { return _col.blue; };
    unsigned char getColorGreen(void) const { return _col.green; };
    unsigned char getColorAlpha(void) const { return _col.alpha; };

protected:
    Color _col;
};

#endif //OOP_ARCADE_2019_COLOR_HPP
