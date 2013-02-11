#include "world.h"
#include <cmath>
#include <QDebug>


World::World(int w, int h, int ticks)
    :width(w), height(h), ticks(ticks)
{
    tick = 0;
    for(int i = 0; i < 6; i++)
        tanks.push_back(new Tank(i*90.0, 0.0, i*M_PI/12, 0.0));
}

void World::procesNextTick()
{
    tick++;

    /*************************************
        —оздание бонуса случайным образом. ≈сли врем€ жизни бонуса истекло, то происходит
        удаление бонуса со сцены
    *************************************/
    if(tick % 100 == 0)
    {
        int random = rand() % 2;
        if(random) bonuses.push_back(new Bonus(rand() % width - width/2.0, rand() % height - height/2.0));
    }
    foreach(Bonus* b, bonuses)
    {
        if(!b->decLifeTime()) bonuses.removeOne(b);
    }

    /*************************************
        ѕросчет следующего хода танка: вычисление координат и вектора скорости, обработка случа€
        столкновени€ танка со стенкой.
    *************************************/
    for(int i = 0; i < tanks.size(); i++)
    {
        Tank* tank = tanks[i];
        if(tank->isDead()) continue;
        tank->setSpeed(7.0);
        double posX = tank->getX();
        double posY = tank->getY();
        double angle = tank->getSpeedAngle();
        double speed = tank->getSpeed();
        double radius = tank->getRadius();
        if(posX <= - width/2.0 + radius || posX >= width/2.0 - radius)
        {
            (angle >= 0) ? angle = M_PI - angle : angle = - M_PI - angle;
        }
        if(posY >= height/2.0 - radius || posY <= -height/2.0 + radius)
        {
            angle *= -1;
        }
        tank->setSpeedAngle(angle);
        tank->setAngle(angle);
        tank->setCannonAngle(angle);
        tank->setX(posX + cos(angle) * speed);
        tank->setY(posY + sin(angle) * speed);
    }

    /*************************************
        ѕросчет следующего хода пули.
    *************************************/
    foreach(Bullet *b, bullets)
    {
        double posX = b->getX();
        double posY = b->getY();
        double angle = b->getSpeedAngle();
        double speed = b->getSpeed();
        double radius = b->getRadius();
        if(posX <= - width/2.0 + radius || posX >= width/2.0 - radius ||
            posY >= height/2.0 - radius || posY <= -height/2.0 + radius)
        {
            bullets.removeOne(b);
            continue;
        }
        for(int i = 0; i < tanks.size(); i++)
        {
            if(tanks[i]->isDead()) continue;
            Tank* owner = b->getOwner();
            if(owner == tanks[i]) continue;
            if(b->getDistanceTo((GameObject&)*tanks[i]) < radius + tanks[i]->getRadius())
            {
                tanks[i]->increaseHP(-3);
                b->getOwner()->increaseScore(3);
                bullets.removeOne(b);
                break;
            }
        }
        b->setX(posX + cos(angle) * speed);
        b->setY(posY + sin(angle) * speed);
    }

    /*************************************
        ѕросчет следующего хода ракеты.
    *************************************/
    foreach(Rocket* r, rockets)
    {
        double posX = r->getX();
        double posY = r->getY();
        double angle = r->getSpeedAngle();
        double speed = r->getSpeed();
        double radius = r->getRadius();
        if(posX <= - width/2.0 + radius || posX >= width/2.0 - radius ||
            posY >= height/2.0 - radius || posY <= -height/2.0 + radius)
        {
            rockets.removeOne(r);
            continue;
        }
        for(int i = 0; i < tanks.size(); i++)
        {
            if(tanks[i]->isDead()) continue;
            Tank* owner = r->getOwner();
            if(owner == tanks[i]) continue;
            if(r->getDistanceTo((GameObject&)*tanks[i]) < radius + tanks[i]->getRadius())
            {
                tanks[i]->increaseHP(-10);
                owner->increaseScore(10);
                rockets.removeOne(r);
                break;
            }
        }
        r->setX(posX + cos(angle) * speed);
        r->setY(posY + sin(angle) * speed);
    }

    /*************************************
        ќбработка столкновени€ танка с бонусом: танку - 25HP и ракета, бонус исчезает
    *************************************/
    for(int i = 0; i < tanks.size(); i ++)
        foreach(Bonus* b, bonuses)
        {
            if(tanks[i]->getDistanceTo((GameObject&)*b) < tanks[i]->getRadius() + b->getRadius())
            {
                tanks[i]->increaseHP(25);
                tanks[i]->increaseScore(2);
                tanks[i]->increaseHeavyBullets(1);
                bonuses.removeOne(b);
            }
        }

    /*************************************
        ѕроисходит обработка столкновений: два танка при столкновении обмениваютс€ углами скорости.
        ≈сли второй танк подбит, то первый танк отскакивает от него.
    *************************************/
    for(int i = 0; i < tanks.size(); i++)
        for(int j = i+1; j < tanks.size(); j++)
        {
            if(tanks[i]->getDistanceTo((GameObject&)*tanks[j]) < 2 * tanks[i]->getRadius())
            {
                double tmp = tanks[i]->getSpeedAngle();
                if(tanks[j]->isDead())
                {
                    tanks[i]->setSpeedAngle( M_PI + tmp );
                }
                else
                {
                    tanks[i]->setSpeedAngle(tanks[j]->getSpeedAngle());
                    tanks[j]->setSpeedAngle(tmp);
                }
            }
        }

    calculateSimpleLogic();
}

QList<Tank *> World::getTanks()
{
    return tanks;
}

QList<Bonus *> World::getBonuses()
{
    return bonuses;
}

QList<Bullet *> World::getBullets()
{
    return bullets;
}

QList<Rocket *> World::getRockets()
{
    return rockets;
}

void World::setWidth(int w)
{
    width = w;
}

void World::setHeight(int h)
{
    height = h;
}

int World::getWidth()
{
    return width;
}

int World::getHeight()
{
    return height;
}

int World::getTick()
{
    return tick;
}

void World::calculateSimpleLogic()
{
    /*if (tick % 3 == 0)
    {
        bullets.push_back(new Bullet(tanks[0]->getX(), tanks[0]->getY(), tanks[0]->getCannonAngle(),
                                     tanks[0]));
    }*/

    if(tick % 10 == 0)
    {
        rockets.push_back(new Rocket(tanks[0]->getX(), tanks[0]->getY(), tanks[0]->getCannonAngle(),
                                     tanks[0]));
    }
}
