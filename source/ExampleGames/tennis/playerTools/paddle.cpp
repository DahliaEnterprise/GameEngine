#include "paddle.h"

paddle::paddle(QObject *parent) : QObject(parent)
{
}

void paddle::start(int setScreenWidth, int setScreenHeight)
{
    screenWidth=setScreenWidth;screenHeight=setScreenHeight;
    emblemBox = new ogleEmblemBox();
    emblemBox->defineEveryCharacteristic(QColor(100,100,100,255), QColor(100,100,100,255), 0,0,100,50);
    emblem = new ogleEmblem();
    emblem->start(emblemBox);
}

ogleEmblem* paddle::determine_frame()
{
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::characteristic::CharacteristicLeft, mouseX);
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::characteristic::CharacteristicTop, mouseY);
    return emblem;
}

void paddle::updatedMousePosition(ogleWindowMousePosition* newMousePosition)
{
    mouseX=newMousePosition->getMouseX();mouseY=newMousePosition->getMouseY();
}
