#include "tennis_script.h"

tennis_script::tennis_script(QObject *parent) : QObject(parent)
{

}
void tennis_script::start(){objectsInitialized = false;scriptKeepalive = new QTimer();QObject::connect(scriptKeepalive, SIGNAL(timeout()), this, SLOT(wakeupScript()));scriptKeepalive->start(100);}
void tennis_script::wakeupScript(){QTimer::singleShot(6, this, SLOT(cycleLogic()));}

void tennis_script::cycleLogic()
{
    //Initialize game objects(if nessecary)
    if(objectsInitialized == false){objectsInitialized = true;playerOneEmblem=new ogleEmblem();playerOnePaddle=new paddle();}

    QTimer::singleShot(5, //5 ms or higher for resource cool down time
                       this, SLOT(cycleLogic()));
}


void tennis_script::determine_frame()
{
    playerOnePaddle->determine_frame();
}
