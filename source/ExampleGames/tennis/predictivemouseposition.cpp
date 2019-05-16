#include "predictivemouseposition.h"

predictiveMousePosition::predictiveMousePosition(QObject *parent) : QObject(parent)
{
    correctedX=0;
}
//predict beyond the knowledge of two points. Collect more points to determine change in velocity with momentum involved.
//currently going fast, then slowing down will result in a blip-error of shooting ahead of the mouse that has almost slowed to a halt or is beginning to slow to a halt.
void predictiveMousePosition::determineCorrection(int mouseX, int newMouseX, int mouseY, int newMouseY)
{
    int xSpeed = std::abs(std::abs(mouseX)-std::abs(newMouseX));int xDirection = mouseX-newMouseX;
    if(xDirection < 0){correctedX = newMouseX+xSpeed;}else if(xDirection > 0){correctedX = newMouseX-xSpeed;}

    int ySpeed = std::abs(std::abs(mouseY)-std::abs(newMouseY));int yDirection = mouseY-newMouseY;
    if(yDirection < 0){correctedY = newMouseY+ySpeed;}else if(yDirection > 0){correctedY = newMouseY-ySpeed;}
}

int predictiveMousePosition::getCorrectedX(){return correctedX;}
int predictiveMousePosition::getCorrectedY(){return correctedY;}
