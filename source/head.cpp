#include "head.h"

head::head(QObject *parent) : QObject(parent)
{

}

void head::start()
{
    frameTimer = new QTimer();
    frameTimer->setInterval(10);

    //Game Logic Management.
    //QThread* threadGameLogic = new QThread();
    game = new gameloop();
    game->start();
    //game->moveToThread(threadGameLogic);
    //threadGameLogic->start();


    //Graphics Processing Unit.
    QThread* threadGpu = new QThread();
    engine = new gameengine();
    engine->start();
    engine->moveToThread(threadGpu);
    threadGpu->start();

    QObject::connect(frameTimer, SIGNAL(timeout()), this, SLOT(frameTimeout()));

    frameTimer->start();

}

void head::frameTimeout()
{
    engine->frame(game->frame());
}
