//
// Created by Jean-Gaël Choppe on 17/03/2020.
//

#ifndef OOP_ARCADE_2019_VECTOR2F_HPP
#define OOP_ARCADE_2019_VECTOR2F_HPP

#include <iostream>

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
    bool operator <(Vector2 const &with) const { return (this->x < with.x && this->y < with.y); }
    bool operator >(Vector2 const &with) const { return (this->x > with.x && this->y > with.y); }
    bool operator <=(Vector2 const &with) const { return (this->x <= with.x && this->y <= with.y); }
    bool operator >=(Vector2 const &with) const { return (this->x >= with.x && this->y >= with.y); }
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
    bool operator <(Vector3 const &with) const { return (this->x < with.x && this->y < with.y && this->z < with.z); }
    bool operator >(Vector3 const &with) const { return (this->x > with.x && this->y > with.y && this->z > with.z); }
    bool operator <=(Vector3 const &with) const { return (this->x <= with.x && this->y <= with.y && this->z <= with.z); }
    bool operator >=(Vector3 const &with) const { return (this->x >= with.x && this->y >= with.y && this->z >= with.z); }
};

typedef Vector3<float> Vector3f;
typedef Vector3<unsigned int> Vector3u;
typedef Vector3<int> Vector3i;

#endif //OOP_ARCADE_2019_VECTOR2F_HPP
