#include "oglewindowmouseposition.h"

ogleWindowMousePosition::ogleWindowMousePosition(QObject *parent) : QObject(parent)
{
    mouseX = 0;
    mouseY = 0;
}

void ogleWindowMousePosition::setMousePosition(int setMouseX, int setMouseY)
{
    mouseX=setMouseX;
    mouseY=setMouseY;
}

int ogleWindowMousePosition::getMouseX(){return mouseX;}
int ogleWindowMousePosition::getMouseY(){return mouseY;}
