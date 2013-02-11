#include "tank.h"

Tank::Tank(double x, double y, double startAngle, double startCannonAngle)
    : MovingObject(x, y, startAngle), cannonAngle(startCannonAngle)
{
    radius = 35.0;
    v = Vector2();
    hp = 100;
    score = 0;
    heavyBullets = 0;
    dead = false;
}

void Tank::increaseHP(int hitPoints)
{
    hp += hitPoints;
    if (hp <= 0) dead = true;
}

void Tank::increaseScore(int scorePoints)
{
    score += scorePoints;
}

void Tank::increaseHeavyBullets(int bullets)
{
    heavyBullets += bullets;
}

void Tank::setCannonAngle(double cAngle)
{
    cannonAngle = cAngle;
}

int Tank::getHitPoints()
{
    return hp;
}

int Tank::getScore()
{
    return score;
}

double Tank::getCannonAngle()
{
    return cannonAngle;
}

bool Tank::isDead()
{
    return dead;
}
