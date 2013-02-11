#include "bonus.h"

Bonus::Bonus(double x, double y, double a, int lifeTime)
    : GameObject(x, y, a), remainingLifeTime(lifeTime)
{
    radius = 20.0;
}

int Bonus::getRemainingLifeTime()
{
    return remainingLifeTime;
}

bool Bonus::decLifeTime()
{
    if(!remainingLifeTime) return false;
    remainingLifeTime--;
    return true;
}
