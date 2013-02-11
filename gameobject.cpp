#include "gameobject.h"
#include <cmath>

GameObject::GameObject(double x, double y, double a)
    : x(x), y(y), angle(a)
{
}

double GameObject::getX()
{
    return x;
}

void GameObject::setX(double x)
{
    this->x = x;
}

double GameObject::getY()
{
    return y;
}

void GameObject::setY(double y)
{
    this->y = y;
}

double GameObject::getRadius()
{
    return radius;
}

double GameObject::getAngle()
{
    return angle;
}

void GameObject::setAngle(double angle)
{
    this->angle = angle;
}

double GameObject::getAngleTo(double x, double y)
{
    return atan2(x - this->x, y - this->y);
}

double GameObject::getAngleTo(GameObject &obj)
{
    return getAngleTo(obj.x, obj.y);
}

double GameObject::getDistanceTo(double x, double y)
{
    return sqrt((x - this->x)*(x - this->x) + (y - this->y)*(y - this->y));
}

double GameObject::getDistanceTo(GameObject &obj)
{
    return getDistanceTo(obj.x, obj.y);
}
