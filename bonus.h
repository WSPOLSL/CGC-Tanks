#ifndef BONUS_H
#define BONUS_H

#include "gameobject.h"

class Bonus : public GameObject
{
public:
    Bonus(double x, double y, double a = 0.0, int lifeTime = 350);
    int getRemainingLifeTime();
    bool decLifeTime();
private:
    int remainingLifeTime;

};

#endif // BONUS_H
