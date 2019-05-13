#include "predictivemouseposition.h"

predictiveMousePosition::predictiveMousePosition(QObject *parent) : QObject(parent)
{
    correctedX=0;
}

void predictiveMousePosition::determineCorrection(int mouseX, int newMouseX)
{
    int xSpeed = std::abs(std::abs(mouseX)-std::abs(newMouseX));
    int xDirection = mouseX-newMouseX;
    if(xDirection < 0){
        correctedX = newMouseX+xSpeed;
    }else if(xDirection > 0){
        correctedX = newMouseX-xSpeed;
    }
}

int predictiveMousePosition::getCorrectedX(){return correctedX;}
