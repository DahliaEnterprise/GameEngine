#include "tennis.h"

tennis::tennis(QObject *parent) : QObject(parent){}

bool tennis::start()
{
    bool output = false;

    logic = new tennis_script();
    logic->start();

    return output;
}


void tennis::determine_frame()
{
    //TODO: if frame instructions are available, push frame
    logic->determine_frame();
    //ogle->getWindow()->incomingNextFrame();
}


void tennis::updatedMousePosition(ogleWindowMousePosition* newMousePosition)
{
    mousePosition=newMousePosition;
    qWarning() << mousePosition->getMouseX();
}
