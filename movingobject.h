#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "vector2.h"
#include "gameobject.h"

class MovingObject : public GameObject
{
public:
    MovingObject(double x, double y, double a);
    double getMaxSpeed();
    double getSpeed();
    void setSpeed(double speed);
    double getSpeedAngle();
    void setSpeedAngle(double sangle);
    Vector2 getVelocity();

protected:
    double maxSpeed;
    double speed;
    double speedAngle;
    Vector2 v;
};

#endif // MOVINGOBJECT_H
