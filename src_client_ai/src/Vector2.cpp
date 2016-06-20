//
// Created by gaspar_q on 6/11/16.
//

#include <cmath>
#include "Vector2.hpp"

const Vector2    Vector2::Zero = {0, 0};
const Vector2    Vector2::Up = {0, 1};
const Vector2    Vector2::Down = {0, -1};
const Vector2    Vector2::Left = {-1, 0};
const Vector2    Vector2::Right = {1, 0};
const Vector2    Vector2::Directions[4] = {
        Vector2::Up,
        Vector2::Right,
        Vector2::Down,
        Vector2::Left
};

Vector2::Vector2(int x, int y) :
        x{x},
        y{y}
{

}

Vector2::Vector2(Vector2 const &ref) :
    Vector2(ref.x, ref.y)
{

}

Vector2::~Vector2()
{

}

Vector2 &Vector2::operator=(Vector2 const &ref)
{
    x = ref.x;
    y = ref.y;
    return *this;
}

Vector2 Vector2::operator+(Vector2 const &ref) const
{
    return Vector2(x + ref.x, y + ref.y);
}

Vector2 Vector2::operator-(Vector2 const &ref) const
{
    return Vector2(x - ref.x, y - ref.y);
}

Vector2 Vector2::operator*(int i) const
{
    return Vector2(x * i, y * i);
}

Vector2 &Vector2::operator+=(const Vector2 &ref)
{
    x += ref.x;
    y += ref.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &ref)
{
    x -= ref.x;
    y -= ref.y;
    return *this;
}

Vector2 &Vector2::operator*=(int fact)
{
    x *= fact;
    y *= fact;
    return *this;
}

Vector2 &Vector2::limit(Vector2 const &min, Vector2 const &max)
{
    if (x < min.x)
        x = max.x - 1;
    else if (x >= max.x)
        x = min.x;
    if (y < min.y)
        y = max.y - 1;
    else if (y >= max.y)
        y = min.y;
    return *this;
}

bool Vector2::operator==(Vector2 const &ref) const
{
    return (x == ref.x && y == ref.y);
}

bool Vector2::operator!=(Vector2 const &ref) const
{
    return !(*this == ref);
}

bool Vector2::operator<(Vector2 const &ref) const
{
    return length() < ref.length();
}

bool Vector2::operator>(Vector2 const &ref) const
{
    return length() > ref.length();
}

bool Vector2::operator<=(Vector2 const &ref) const
{
    return length() <= ref.length();
}

bool Vector2::operator>=(Vector2 const &ref) const
{
    return length() >= ref.length();
}

size_t Vector2::length(void) const
{
    return static_cast<size_t >(sqrt(x * x + y * y));
}

std::ostream    &operator<<(std::ostream &output, Vector2 const &ref)
{
    output << "(" << ref.x << ", " << ref.y << ")";
    return output;
}