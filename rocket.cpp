#include "rocket.h"

Rocket::Rocket(double x, double y, double startSpeedAngle, Tank *owner)
    : Projectile(x, y, startSpeedAngle, owner)
{
    damage = 20;
    speed = 15.0;
    radius = 15.0;
}
