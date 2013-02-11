#include "projectile.h"
#include "tank.h"

Projectile::Projectile(double x, double y, double startAngle, Tank *owner)
    : MovingObject(x, y, startAngle), owner(owner)
{

}

int Projectile::getDamage()
{
    return damage;
}

Tank *Projectile::getOwner()
{
    return owner;
}
