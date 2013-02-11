#ifndef BULLET_H
#define BULLET_H

#include "projectile.h"

class Bullet : public Projectile
{
public:
    Bullet(double x, double y, double startSpeedAngle, Tank* owner);
};

#endif // BULLET_H
