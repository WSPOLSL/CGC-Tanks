#ifndef WORLD_H
#define WORLD_H

#include <QVector>
#include "gameobject.h"
#include "bonus.h"
#include "movingobject.h"
#include "tank.h"
#include "bullet.h"
#include "rocket.h"

class World
{
public:
    World(int w, int h, int ticks);
    void procesNextTick();
    //QVector<GameObject*> getGameObjets();
    QList<Tank*> getTanks();
    QList<Bonus*> getBonuses();
    QList<Bullet*> getBullets();
    QList<Rocket*> getRockets();
    void setWidth(int w);
    void setHeight(int h);
    int getWidth();
    int getHeight();
    int getTick();

private:
    //QVector<GameObject*> objects;
    QList<Tank*> tanks;
    QList<Bonus*> bonuses;
    QList<Bullet*> bullets;
    QList<Rocket*> rockets;
    int tick;
    int width;
    int height;
    int ticks;
    void calculateSimpleLogic();
};

#endif // WORLD_H
