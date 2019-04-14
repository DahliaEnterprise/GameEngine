#include "head.h"

head::head(QObject *parent) : QObject(parent)
{

}

void head::start()
{
    //Keyboard Mouse Input
    keyboardmouse_input = new keyboardMouseInput();
    keyboardmouse_input->start();

    #if gameToRun == 0
        //Game Logic Management.
        game = new gameloop();
        game->start(keyboardmouse_input);
    #endif

    #if gameToRun == 1
        //Communicatoin Logic Management.
        communication = new communicationloop();
        communication->start(keyboardmouse_input):
    #endif

    //Graphics Processing Unit.
    threadGpu = new QThread();
    engine = new gameengine();
    engine->start(keyboardmouse_input);
    engine->moveToThread(threadGpu);
    threadGpu->start();

#if gameToRun == 0
    QObject::connect(game, SIGNAL(playerRequestingCloseGame()), this, SLOT(slotPlayerRequestingCloseGame()));
#endif
#if gameToRun == 1
    QObject::connect(communication, SIGNAL(playerRequestingCloseCommunicationChannel()), this, SLOT(slotPlayerReqestingCloseGame()));
#endif

    //Frame Timer
    frameTimer = new QTimer();
    frameTimer->setInterval(10);
    QObject::connect(frameTimer, SIGNAL(timeout()), this, SLOT(frameTimeout()));

    frameTimer->start();
}

void head::frameTimeout()
{
#if gameToRun == 0
    engine->frame(game->frame());
#endif

#if gameToRun == 1

#endif
}


void head::slotPlayerRequestingCloseGame()
{
    this->deleteLater();
}
