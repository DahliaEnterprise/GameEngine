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
    QObject::connect(scriptKeepalive, SIGNAL(timeout()), this, SLOT(wakeupScript()));

    ///Begin keep alive timer
    scriptKeepalive->start(100);
}
void tennis_script::wakeupScript(){QTimer::singleShot(6, this, SLOT(cycleLogic()));}

void tennis_script::cycleLogic()
{
    //TODO:track score

    QTimer::singleShot(5, //5 ms or higher for resource cool down time
                       this, SLOT(cycleLogic()));
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
