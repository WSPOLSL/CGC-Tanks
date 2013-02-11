#include "movingobject.h"
#include <cmath>

MovingObject::MovingObject(double x, double y, double a)
    : GameObject(x, y, a)
{
    v = Vector2();
    speedAngle = a;
    speed = 0.0;
}

double MovingObject::getMaxSpeed()
{
    return maxSpeed;
}

double MovingObject::getSpeed()
{
    return speed;
}

void MovingObject::setSpeed(double speed)
{
    this->speed = speed;
    //Vector2 newV(v.getX()/v.norm() * speed, v.getY()/v.norm() * speed);
    //v = newV;
}

double MovingObject::getSpeedAngle()
{
    return speedAngle;//atan2(v.getY(), v.getX());
}

void MovingObject::setSpeedAngle(double sangle)
{
    speedAngle = sangle;
    //Vector2 newV(cos(sangle)*v.norm(), sin(sangle)*v.norm());
    //v = newV;
}

Vector2 MovingObject::getVelocity()
{
    return v;
}
