#ifndef ROCKET_H
#define ROCKET_H

#include "projectile.h"
#include "tank.h"

class Rocket : public Projectile
{
public:
    Rocket(double x, double y, double startSpeedAngle, Tank* owner);
};

#endif // ROCKET_H
