#include <QApplication>
#include "gameengine.h"
#include "examplegame/gameloop.h"
#include <QThread>
#include "head.h"

#include "OpenGLEngine/oglemastercontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     qRegisterMetaType<QVector<QColor>>();

    //head h;
    //h.start();

    ogleMasterController* ogle = new ogleMasterController();
    ogle->start();

    return a.exec();
}
