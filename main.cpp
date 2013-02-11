#include <QtGui/QApplication>
#include "gltest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlTest w;
    //w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::SubWindow);
    w.showFullScreen();
    //w.show();
    
    return a.exec();
}
