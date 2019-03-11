#include <QApplication>
#include "gameengine.h"
#include "examplegame/gameloop.h"
#include <QThread>
#include "head.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    head h;
    h.start();

    return a.exec();
}
