#include "gltest.h"
#include "vector2.h"

#include <time.h>
#include <cmath>
#include <QKeyEvent>
#include <QApplication>
#include <QtOpenGL>
#include <QImage>
#include <QFont>
#include <QList>

GlTest::GlTest(QWidget *parent)
    : QGLWidget(parent)
{
    qsrand(time(NULL));
    texturesList << QString("bg.png") << QString("tank_body.png")
                 << QString("tank_cannon.png") << QString("bonus.png") << QString("bullet.png")
                    << QString("rocket.png") << QString("tank_body_dead.png");
    world = new World(width(), height(), 4000);
    timerId = startTimer(10);
}

GlTest::~GlTest()
{
    
}

void GlTest::initializeGL()
{
    for(int i = 0; i < TEX_COUNT; i++)
    {
        textures[i] = bindTexture(QPixmap(QString(":/textures/" + texturesList[i])), GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }

    glEnable(GL_TEXTURE_2D);
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
    glShadeModel(GL_SMOOTH);// включает режим сглаживания цветов
    glEnable(GL_CULL_FACE);// устанавливаем режим, когда строятся только внешние поверхности
}

void GlTest::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
    glLoadIdentity();            // присваивает проекционной матрице единичную матрицу
    // мировое окно
   // glOrtho(-w/2.0, w/2.0, -h/2.0, h/2.0, -100.0, 100.0);     // параметры видимости ортогональной проекции
    // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)
    glOrtho(-w/2, w/2, -h/2, h/2, -1.0, 1.0);
    //glFrustum(-w/2.0, w/2.0, -h/2.0, h/2.0, -5.0, 5.0); // параметры видимости перспективной проекции
    // плоскости отсечения: (левая, правая, верхняя, нижняя, ближняя, дальняя)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h); // устанавливает видовое окно с размерами равными окну виджета
    world->setWidth(w);
    world->setHeight(h);
}

void GlTest::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();

    glTranslated(0.0, 0.0, 0.0);
    //drawing enviornment
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_POLYGON);

    glTexCoord2d(0.0, 0.0); glVertex3d(-width()/2, -height()/2,  -0.1);	// Низ лево
    glTexCoord2d(1.0, 0.0); glVertex3d( width()/2, -height()/2,  -0.1);	// Низ право
    glTexCoord2d(1.0, 1.0); glVertex3d( width()/2,  height()/2,  -0.1);	// Верх право
    glTexCoord2d(0.0, 1.0); glVertex3d(-width()/2,  height()/2,  -0.1); // Top left

    glEnd();

    //drawing bonuses
    QList<Bonus*> bonuses = world->getBonuses();
    for(int i = 0; i < bonuses.size(); i++)
    {
        glLoadIdentity();
        glTranslated(bonuses[i]->getX(), bonuses[i]->getY(), 0.1);
        glRotated(radToDeg(bonuses[i]->getAngle()), 0.0, 0.0, 1.0);

        glBindTexture(GL_TEXTURE_2D, textures[3]);
        double r = bonuses[i]->getRadius();
        glBegin(GL_POLYGON);
        glTexCoord2d(0.0, 0.0); glVertex2d(-r, -r);
        glTexCoord2d(1.0, 0.0); glVertex2d(r, -r);
        glTexCoord2d(1.0, 1.0); glVertex2d(r, r);
        glTexCoord2d(0.0, 1.0); glVertex2d(-r, r);
        glEnd();
    }

    //drawing tanks
    QList<Tank*> tanks = world->getTanks();
    for(int i = 0; i < tanks.size(); i++)
    {
        glLoadIdentity();

        //drawing tank body
        glTranslated(tanks[i]->getX(), tanks[i]->getY(), 0.2);
        glRotated(radToDeg(tanks[i]->getAngle()), 0.0, 0.0, 1.0);
        bool isDead = tanks[i]->isDead();
        (!isDead) ? glBindTexture(GL_TEXTURE_2D, textures[1])
                  : glBindTexture(GL_TEXTURE_2D, textures[6]);
        double r = tanks[i]->getRadius();
        glBegin(GL_POLYGON);
        glTexCoord2d(0.0, 0.0); glVertex2d(-r, -r);
        glTexCoord2d(1.0, 0.0); glVertex2d(r, -r);
        glTexCoord2d(1.0, 1.0); glVertex2d(r, r);
        glTexCoord2d(0.0, 1.0); glVertex2d(-r, r);
        glEnd();

        if(isDead) continue;
        //drawing tank cannon
        glLoadIdentity();
        glTranslated(tanks[i]->getX(), tanks[i]->getY(), 0.3);
        glRotated(radToDeg(tanks[i]->getCannonAngle()), 0.0, 0.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glBegin(GL_POLYGON);
        glTexCoord2d(0.0, 0.0); glVertex2d(-r, -r);
        glTexCoord2d(1.0, 0.0); glVertex2d(r, -r);
        glTexCoord2d(1.0, 1.0); glVertex2d(r, r);
        glTexCoord2d(0.0, 1.0); glVertex2d(-r, r);
        glEnd();
    }

    //drawing bullets
    QList<Bullet*> bullets = world->getBullets();
    for(int i = 0; i < bullets.size(); i++)
    {
        glLoadIdentity();
        glTranslated(bullets[i]->getX(), bullets[i]->getY(), 0.3);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glBegin(GL_POLYGON);
        glTexCoord2d(0.0, 0.0); glVertex2d(-5, -5);
        glTexCoord2d(1.0, 0.0); glVertex2d(5, -5);
        glTexCoord2d(1.0, 1.0); glVertex2d(5, 5);
        glTexCoord2d(0.0, 1.0); glVertex2d(-5, 5);
        glEnd();
    }

    //drawing rockets
    QList<Rocket*> rockets = world->getRockets();
    for(int i = 0; i < rockets.size(); i++)
    {
        glLoadIdentity();
        glTranslated(rockets[i]->getX(), rockets[i]->getY(), 0.3);
        glRotated(radToDeg(rockets[i]->getSpeedAngle()), 0.0, 0.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, textures[5]);
        glBegin(GL_POLYGON);
        glTexCoord2d(0.0, 0.0); glVertex2d(-15, -15);
        glTexCoord2d(1.0, 0.0); glVertex2d(15, -15);
        glTexCoord2d(1.0, 1.0); glVertex2d(15, 15);
        glTexCoord2d(0.0, 1.0); glVertex2d(-15, 15);
        glEnd();
    }

    renderText(width() - 100, height() - 50, QString("%1").arg(world->getTick()), QFont("Comic Sans", 20, QFont::Bold));
    for(int i = 0; i < tanks.size(); i++)
        renderText(10, (i+1)*20, QString("%1. Tank %2, %3").arg(i+1).arg(tanks[i]->getHitPoints()).arg(tanks[i]->getScore()), QFont("Comic Sans", 16, QFont::Bold));
}

void GlTest::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            quit();
        break;

    }
}

void GlTest::timerEvent(QTimerEvent *ev)
{
   // tick++;
    //angle += PI/1024.0f;
    /*if(angle > M_PI) angle *= -1.0;
    //startRotTick = 0;

    if(startRotTick)
    {
        angle += r * (PI / 48.0);
        if(tick - startRotTick > 2) startRotTick = 0;
    }
    else if(tick % 30 == 0)
    {
        r = rand() % 3 - 1;
        startRotTick = tick;
        //angle += r * 11.25;
    }
/*/
    world->procesNextTick();
    if(world->getTick() > 4000) killTimer(timerId);
    updateGL();
}

void GlTest::quit()
{
    qApp->quit();
}

double GlTest::radToDeg(double rad)
{
    double ret = (rad * 180.0) / M_PI - 90.0;
    if (ret < 0.0) return 360.0 + ret;
    return ret;
}
