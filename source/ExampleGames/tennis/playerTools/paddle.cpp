#include "paddle.h"

paddle::paddle(QObject *parent) : QObject(parent)
{
}

void paddle::start(int setScreenWidth, int setScreenHeight)
{
    paddleX = 0;paddleY = 0;paddleWidth=100;paddleHeight=10;
    screenWidth=setScreenWidth;screenHeight=setScreenHeight;
    correctedMousePosition = new predictiveMousePosition();
    emblemBox = new ogleEmblemBox();emblemBox->defineEveryCharacteristic(QColor(100,100,100,255), QColor(100,100,100,255), 10,100,paddleWidth,paddleHeight);
    emblem = new ogleEmblem();emblem->start(emblemBox);

}

ogleEmblem* paddle::determine_frame(){return emblem;}

void paddle::updatedMousePosition(ogleWindowMousePosition* newMousePosition)
{
    //reduces mouse input lag by predicting mouse position based on velocity
    correctedMousePosition->determineCorrection(mouseX, newMousePosition->getMouseX(), mouseY, newMousePosition->getMouseY());
    correctedX=correctedMousePosition->getCorrectedX();correctedY=correctedMousePosition->getCorrectedY();

    //determine paddle x and paddle y
    paddleX = correctedX - (paddleWidth / 2);
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::characteristic::CharacteristicLeft, paddleX);

    //update current mouse x and mouse y positions
    mouseX=newMousePosition->getMouseX();mouseY=newMousePosition->getMouseY();
}
