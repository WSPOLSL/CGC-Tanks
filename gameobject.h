#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vector2.h"

class GameObject
{
public:
    GameObject(double x, double y, double a);
    double getX();
    void setX(double x);
    double getY();
    void setY(double y);
    double getRadius();
    double getAngle();
    void setAngle(double angle);
    double getAngleTo(double x, double y);
    double getAngleTo(GameObject &obj);
    double getDistanceTo(double x, double y);
    double getDistanceTo(GameObject &obj);
protected:
    double radius;
    double x;
    double y;
    double angle;

};

#endif // GAMEOBJECT_H
