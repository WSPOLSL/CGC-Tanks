#include <cmath>

#include "vector2.h"


Vector2::Vector2(double x, double y)
    : x(x), y(y)
{
}

Vector2 Vector2::operator +(Vector2 &v2)
{
    return Vector2(x + v2.x, y + v2.y);
}

Vector2 Vector2::operator -()
{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator -(Vector2 &v2)
{
    return Vector2(x - v2.x, y - v2.y);
}

double Vector2::operator *(Vector2 &v2)
{
    return x*v2.x + y*v2.y;
}

double Vector2::getX(){ return x;}

void Vector2::setX(double x)
{
    this->x = x;
}

double Vector2::getY(){ return y;}

void Vector2::setY(double y)
{
    this->y = y;
}

double Vector2::norm()
{
    return sqrt(x*x + y*y);
}

double Vector2::angleBetween(Vector2 &v1, Vector2 &v2)
{
    return acos(v1*v2/(v1.norm()*v2.norm()));
}

Vector2 Vector2::unitX() {return Vector2(1.0, 0.0);}
Vector2 Vector2::unitY() {return Vector2(0.0, 1.0);}
