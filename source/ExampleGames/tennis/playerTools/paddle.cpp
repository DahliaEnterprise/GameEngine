#include "paddle.h"

paddle::paddle(QObject *parent) : QObject(parent)
{
}

void paddle::start(int setScreenWidth, int setScreenHeight)
{
    screenWidth=setScreenWidth;screenHeight=setScreenHeight;
    correctedMousePosition = new predictiveMousePosition();
    emblemBox = new ogleEmblemBox();
    emblemBox->defineEveryCharacteristic(QColor(100,100,100,255), QColor(100,100,100,255), 0,0,100,50);
    emblem = new ogleEmblem();
    emblem->start(emblemBox);
}

ogleEmblem* paddle::determine_frame()
{
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::characteristic::CharacteristicLeft, correctedX);
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::characteristic::CharacteristicTop, mouseY);
    return emblem;
}

void paddle::updatedMousePosition(ogleWindowMousePosition* newMousePosition)
{
    //estimate mouse x y position
    /*
    int xSpeed = std::abs(std::abs(mouseX)-std::abs(newMousePosition->getMouseX()));
    int xDirection = mouseX-newMousePosition->getMouseX();
    if(xDirection < 0){correctedX = newMousePosition->getMouseX() + xSpeed;
    }else if(xDirection > 0){correctedX = newMousePosition->getMouseX() - xSpeed;}
    */

    //
    correctedMousePosition->determineCorrection(mouseX, newMousePosition->getMouseX()/**todo mouseY, getMouseY()**/);
    correctedX = correctedMousePosition->getCorrectedX();

    //
    mouseX=newMousePosition->getMouseX();mouseY=newMousePosition->getMouseY();
}
