#include "head.h"

head::head(QObject *parent) : QObject(parent)
{

}

void head::start()
{
    startupAppType = 2;

    //Keyboard Mouse Input
    keyboardmouse_input = new keyboardMouseInput();
    keyboardmouse_input->start();

    //Game Logic Management.
    if(startupAppType == 1)
    {
        game = new gameloop();
        game->start(keyboardmouse_input);
    }else if(startupAppType == 2)
    {
        comms = new communication();
        comms->start();
    }


    //Graphics Processing Unit.
    threadGpu = new QThread();
    engine = new gameengine();
    engine->start(keyboardmouse_input);
    engine->moveToThread(threadGpu);
    threadGpu->start();

    if(startupAppType == 1){ QObject::connect(game, SIGNAL(playerRequestingCloseGame()), this, SLOT(slotPlayerRequestingCloseGame()));
    }else if(startupAppType == 2){ QObject::connect(comms, SIGNAL(userRequestingCloseApp()), this, SLOT(slotPlayerRequestingCloseGame())); }


    //Frame Timer
    frameTimer = new QTimer();
    frameTimer->setInterval(10);
    QObject::connect(frameTimer, SIGNAL(timeout()), this, SLOT(frameTimeout()));

    frameTimer->start();
}

void head::frameTimeout()
{
    if(startupAppType == 1){ engine->frame(game->frame()); }
    else if(startupAppType == 2){ engine->frame(comms->frame());}
}


void head::slotPlayerRequestingCloseGame()
{
    frameTimer->stop();
    delete frameTimer;
    this->deleteLater();
}
