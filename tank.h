#ifndef TANK_H
#define TANK_H

#include "movingobject.h"

class Tank : public MovingObject
{
public:
    Tank(double x, double y, double startAngle, double startCannonAngle);
    void increaseHP(int hitPoints);
    void increaseScore(int scorePoints);
    void increaseHeavyBullets(int bullets);
    void setCannonAngle(double cAngle);

    int getHitPoints();
    int getScore();
    double getCannonAngle();
    bool isDead();
private:
    int hp;
    int score;
    double cannonAngle;
    int heavyBullets;
    bool dead;
};

#endif // TANK_H
