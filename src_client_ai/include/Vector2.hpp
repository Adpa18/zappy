//
// Created by gaspar_q on 6/11/16.
//

#ifndef PSU_2015_ZAPPY_VECTOR2_HPP
#define PSU_2015_ZAPPY_VECTOR2_HPP

#include <stddef.h>
#include <iostream>

class Vector2
{
public:
    static const Vector2    Zero;
    static const Vector2    Up;
    static const Vector2    Down;
    static const Vector2    Left;
    static const Vector2    Right;
    static const Vector2    Directions[4];
    enum DIR : int
    {
        UP = 0,
        RIGHT,
        DOWN,
        LEFT
    };

public:
    Vector2(int x = 0, int y = 0);
    Vector2(Vector2 const &ref);
    ~Vector2();
    Vector2 &operator=(Vector2 const &ref);

public:
    Vector2 operator+(Vector2 const &ref) const;
    Vector2 operator-(Vector2 const &ref) const;
    Vector2 operator*(int fact) const;
    Vector2 &operator+=(Vector2 const &ref);
    Vector2 &operator-=(Vector2 const &ref);
    Vector2 &operator*=(int fact);
    bool    operator==(Vector2 const &ref) const;
    bool    operator!=(Vector2 const &ref) const;
    bool    operator<(Vector2 const &ref) const;
    bool    operator>(Vector2 const &ref) const;
    bool    operator<=(Vector2 const &ref) const;
    bool    operator>=(Vector2 const &ref) const;

public:
    Vector2 &limit(Vector2 const &min, Vector2 const &max);
    size_t length(void) const;

public:
    int x;
    int y;
};

std::ostream    &operator<<(std::ostream &output, Vector2 const &ref);

#endif //PSU_2015_ZAPPY_VECTOR2_HPP
