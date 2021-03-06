#include "aipaddle.h"

aiPaddle::aiPaddle(QObject *parent) : QObject(parent)
{

}

void aiPaddle::initialize(int setScreenWidth, int setScreenHeight)
{
    paddleX=0;paddleY=0;paddleWidth=100;paddleHeight=10;
    screenWidth=setScreenWidth;screenHeight=setScreenHeight;
    emblemBox = new ogleEmblemBox();emblemBox->defineEveryCharacteristic(QColor(100,100,100,255), QColor(100,100,100,255), screenHeight-20,100,paddleWidth,paddleHeight);
    emblem = new ogleEmblem();emblem->start(emblemBox);
}

ogleEmblem* aiPaddle::determine_frame(){return emblem;}


void aiPaddle::cycleLogic()
{
    //todo: hand-eye-coordination experience
    //todo: move paddle according to awareness determined by hand eye coordination
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::CharacteristicLeft, tokenVelocity->currentPosition().x());
}

void aiPaddle::tokenAwareness(ogleEmblemVelocity* setTokenVelocity)
{
    tokenVelocity = setTokenVelocity;
}
