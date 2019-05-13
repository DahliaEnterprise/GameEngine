#include "tennis_script.h"

tennis_script::tennis_script(QObject *parent) : QObject(parent){}
void tennis_script::start(){objectsInitialized = false;scriptKeepalive = new QTimer();QObject::connect(scriptKeepalive, SIGNAL(timeout()), this, SLOT(wakeupScript()));scriptKeepalive->start(100);playerOneEmblem=new ogleEmblem();playerOnePaddle=new paddle();playerOnePaddle->start(1280,720);}
void tennis_script::wakeupScript(){QTimer::singleShot(6, this, SLOT(cycleLogic()));}

void tennis_script::cycleLogic()
{

    QTimer::singleShot(5, //5 ms or higher for resource cool down time
                       this, SLOT(cycleLogic()));
}


QVector<ogleEmblem*> tennis_script::determine_frame()
{
    QVector<ogleEmblem*> output;
    output.append(playerOnePaddle->determine_frame());
    return output;
}

void tennis_script::updatedMousePosition(ogleWindowMousePosition* newMousePosition){playerOnePaddle->updatedMousePosition(newMousePosition);}
