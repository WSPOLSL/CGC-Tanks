#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "movingobject.h"
#include "tank.h"

class Projectile : public MovingObject
{
public:
    Projectile(double x, double y, double startAngle, Tank* owner);
    int getDamage();
    Tank* getOwner();
protected:
    int damage;
    Tank* owner;
};

#endif // PROJECTILE_H
