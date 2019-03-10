#include "head.h"

head::head(QObject *parent) : QObject(parent)
{

}

void head::start()
{
    //Game Logic Management.
    game = new gameloop();
    game->start();

    //Graphics Processing Unit.
    QThread* threadGpu = new QThread();
    engine = new gameengine();
    engine->start();
    engine->moveToThread(threadGpu);
    threadGpu->start();

    //Frame Timer
    frameTimer = new QTimer();
    frameTimer->setInterval(100);
    QObject::connect(frameTimer, SIGNAL(timeout()), this, SLOT(frameTimeout()));
    frameTimer->start();
}

void head::frameTimeout()
{
    engine->frame(game->frame());
}
