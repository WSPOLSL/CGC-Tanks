#ifndef GLTEST_H
#define GLTEST_H

#include <QGLWidget>
#include <QStringList>

#include "world.h"
#include "gameobject.h"

#define TEX_COUNT 7

class GlTest : public QGLWidget
{
    Q_OBJECT
    
public:
    GlTest(QWidget *parent = 0);
    ~GlTest();

private:
    int timerId;
    GLuint textures[TEX_COUNT];
    QStringList texturesList;
    World* world;
    void quit();
    double radToDeg(double rad);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *ev);
};

#endif // GLTEST_H
