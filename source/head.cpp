#include "head.h"

head::head(QObject *parent) : QObject(parent)
{

}

void head::start()
{
    //Keyboard Mouse Input
    keyboardmouse_input = new keyboardMouseInput();
    keyboardmouse_input->start();

    //Game Logic Management.
    game = new gameloop();
    game->start(keyboardmouse_input);

    //Graphics Processing Unit.
    threadGpu = new QThread();
    engine = new gameengine();
    engine->start(keyboardmouse_input);
    engine->moveToThread(threadGpu);
    threadGpu->start();
    QObject::connect(game, SIGNAL(playerRequestingCloseGame()), this, SLOT(slotPlayerRequestingCloseGame()));

    //Frame Timer
    frameTimer = new QTimer();
    frameTimer->setInterval(10);
    QObject::connect(frameTimer, SIGNAL(timeout()), this, SLOT(frameTimeout()));

    frameTimer->start();
}

void head::frameTimeout()
{
    engine->frame(game->frame());
}


void head::slotPlayerRequestingCloseGame()
{
    this->deleteLater();
}
