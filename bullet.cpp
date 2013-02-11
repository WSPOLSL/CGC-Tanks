#include "bullet.h"

Bullet::Bullet(double x, double y, double startSpeedAngle, Tank *owner)
    : Projectile(x, y, startSpeedAngle, owner)
{
    damage = 5;
    speed = 20.0;
    radius = 5.0;
}
