#include "tennis_script.h"

tennis_script::tennis_script(QObject *parent) : QObject(parent){}
void tennis_script::start()
{
    ///Initialize Tennis Game Objects.
    scriptKeepalive = new QTimer();
    playerOnePaddle=new paddle();playerOnePaddle->initialize(1280,720);
    playerAiPaddle=new aiPaddle();playerAiPaddle->initialize(1280,720);
    ball=new token();ball->initialize(1280,720);

    ///Register awareness of game objects
    playerAiPaddle->tokenAwareness(ball->getVelocity());

    ///Signals and Slot Connections
    QObject::connect(scriptKeepalive, SIGNAL(timeout()), this, SLOT(cycleLogic()));

    ///Begin keep alive timer
    scriptKeepalive->start(5);
}

void tennis_script::cycleLogic()
{
    playerOnePaddle->cycleLogic();
    playerAiPaddle->cycleLogic();
    ball->cycleLogic();
}


QVector<ogleEmblem*> tennis_script::determine_frame()
{
    QVector<ogleEmblem*> output;
    //TODO: allow layer order to be modified
    output.append(playerOnePaddle->determine_frame());
    output.append(playerAiPaddle->determine_frame());
    output.append(ball->determine_frame());
    return output;
}

void tennis_script::updatedMousePosition(ogleWindowMousePosition* newMousePosition){playerOnePaddle->updatedMousePosition(newMousePosition);}
