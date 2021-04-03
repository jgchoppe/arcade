/*
 ** EPITECH PROJECT, 2020
 ** OOP_arcade_2019
 ** File description:
 ** Drawables
 */
  
 #ifndef DRAWABLES_HPP_
 #define DRAWABLES_HPP_
  
 #include <string>
  
 template <class T>
 struct Vector2
 {
     T x;
     T y;
  
     Vector2(T pX, T pY) : x(pX), y(pY) {}
  
     Vector2 operator +(Vector2 const &with) const { return Vector2(this->x + with.x, this->y + with.y); }
  
     Vector2 &operator +=(Vector2 const &with) { this->x += with.x; this->y += with.y; return *this; }
  
     Vector2 operator -(Vector2 const &with) const { return Vector2(this->x - with.x, this->y - with.y); }
  
     Vector2 &operator -=(Vector2 const &with) { this->x -= with.x; this->y -= with.y; return *this; }
  
     bool operator ==(Vector2 const &with) const { return this->x == with.x && this->y == with.y; }
  
     bool operator !=(Vector2 const &with) const { return !(this->x == with.x && this->y == with.y); }
 };
  
 typedef Vector2<float> Vector2f;
 typedef Vector2<unsigned int> Vector2u;
 typedef Vector2<int> Vector2i;
  
 template <class T>
 struct Vector3
 {
     T x;
     T y;
     T z;
  
     Vector3(T pX, T pY, T pZ) : x(pX), y(pY), z(pZ) {}
  
     Vector3 operator +(Vector3 const &with) const { return Vector3(this->x + with.x, this->y + with.y, this->z + with.z); }
  
     Vector3 &operator +=(Vector3 const &with) { this->x += with.x; this->y += with.y; this->z += with.z; return *this; }
  
     Vector3 operator -(Vector3 const &with) const { return Vector3(this->x - with.x, this->y - with.y, this->z - with.z); }
  
     Vector3 &operator -=(Vector3 const &with) { this->x -= with.x; this->y -= with.y; this->z -= with.z; return *this; }
  
     bool operator ==(Vector3 const &with) const { return this->x == with.x && this->y == with.y && this->z == with.z; }
  
     bool operator !=(Vector3 const &with) const { return !(this->x == with.x && this->y == with.y && this->z == with.z); }
 };
  
 typedef Vector3<float> Vector3f;
 typedef Vector3<unsigned int> Vector3u;
 typedef Vector3<int> Vector3i;
  
 struct Color
 {
     static Color Red() { return Color(255, 0, 0, 255); }
  
     static Color Blue() { return Color(0, 0, 255, 255); }
  
     static Color Green() { return Color(0, 255, 0, 255); }
  
     static Color Black() { return Color(0, 0, 0, 255); }
  
     static Color White() { return Color(255, 255, 255, 255); }
  
     static Color Transparent() { return Color(0, 0, 0, 0); }
  
     unsigned char red;
     unsigned char green;
     unsigned char blue;
     unsigned char alpha;
  
     Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : red(red), green(green), blue(blue), alpha(alpha) {}
  
     bool operator ==(Color const &with) { return this->red == with.red && this->blue == with.blue && this->green == with.green && this->alpha == with.alpha; }
  
     bool operator !=(Color const &with) { return !(this->red == with.red && this->blue == with.blue && this->green == with.green && this->alpha == with.alpha); }
 };
  
 class APosition {
     public:
         APosition(const Vector2f &pos) : _pos(pos) {}
  
         ~APosition() = default;
  
         void setPosition(const Vector2f pos) { this->_pos = pos; }
  
         void setPositionX(float posX) { this->_pos.x = posX; }
  
         void setPositionY(float posY) { this->_pos.y = posY; }
  
         void move(const Vector2f pos) { this->_pos += pos; }
  
         void moveX(float movx) { this->_pos.x += movx; }
  
         void moveY(float movy) { this->_pos.y += movy; }
  
         Vector2f getPosition(void) const { return this->_pos; }
  
         float getPositionX(void) const { return this->_pos.x; }
  
         float getPositionY(void) const { return this->_pos.y; }
  
     protected:
         Vector2f _pos;
 };
  
 class ASize {
     public:
         ASize(const Vector2f &size) : _size(size) {}
  
         ~ASize() = default;
  
         void setSize(const Vector2f &size) { this->_size = size; }
  
         void setSizeX(float sizeX) { this->_size.x = sizeX; }
  
         void setSizeY(float sizeY) { this->_size.y = sizeY; }
  
         Vector2f getSize(void) const { return this->_size; }
  
         float getSizeX(void) const { return this->_size.x; }
  
         float getSizeY(void) const { return this->_size.y; }
  
     protected:
         Vector2f _size;
 };
  
 class AColor {
     public:
         AColor(const Color &color) : _color(color) {}
  
         ~AColor() = default;
  
         void setColor(const Color &color) { this->_color = color; }
  
         void setColorRed(unsigned char red) { this->_color.red = red; }
  
         void setColorGreen(unsigned char green) { this->_color.green = green; }
  
         void setColorBlue(unsigned char blue) { this->_color.blue = blue; }
  
         void setColorAlpha(unsigned char alpha) { this->_color.alpha = alpha; }
  
         Color getColor(void) const { return this->_color; }
  
         unsigned char getColorRed(void) const { return this->_color.red; }
  
         unsigned char getColorGreen(void) const { return this->_color.green; }
  
         unsigned char getColorBlue(void) const { return this->_color.blue; }
  
         unsigned char getColorAlpha(void) const { return this->_color.alpha; }
  
     protected:
         Color _color;
 };
  
 class Rect : public APosition, public ASize, public AColor {
     public:
         Rect(Vector2f pos = Vector2f(0, 0), Vector2f size = Vector2f(0, 0), Color color = Color(0, 0, 0, 0)) : APosition(pos), ASize(size), AColor(color) {}
  
         ~Rect() = default;
 };
  
 class Circle : public APosition, public ASize, public AColor {
     public:
         Circle(Vector2f pos = Vector2f(0, 0), Vector2f size = Vector2f(0, 0), Color color = Color(0, 0, 0, 0)) : APosition(pos), ASize(size), AColor(color) {}
  
         ~Circle() = default;
 };
  
 class Text : public APosition, public ASize, public AColor {
     public:
         Text(const std::string &text, Vector2f pos = Vector2f(0, 0), Vector2f size = Vector2f(0, 0), Color color = Color(0, 0, 0, 0)) : APosition(pos), ASize(size), AColor(color), _text(text) {}
  
         ~Text() = default;
  
         const std::string &getText(void) const { return (this->_text); }
  
         void setText(const std::string &newText) { this->_text = newText; }
     private :
         std::string _text;
 };
  
 class Sprite : public APosition, public ASize {
     public:
         Sprite(const std::string &name, Vector2f pos = Vector2f(0, 0), Vector2f size = Vector2f(0, 0)) : APosition(pos), ASize(size), _textureName(name) {}
  
         ~Sprite() = default;
  
         const std::string &getTextureName(void) const { return (this->_textureName); }
     private :
         std::string _textureName;
 };
  
 #endif /* !DRAWABLES_HPP_ */