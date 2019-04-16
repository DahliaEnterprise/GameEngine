#include "communication.h"

communication::communication(QObject *parent) : QObject(parent)
{

}

void communication::start()
{
    //Graphical and Processing Manager
    graphicsandprocessing = new communication_graphics_and_processing();
    graphicsandprocessing->start();
}

QList<gameobject*> communication::frame(){ return QList<gameobject*>();}
