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
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(cycleAI()));
    timer->start(5);
}

ogleEmblem* aiPaddle::determine_frame()
{
    return emblem;
}


void aiPaddle::cycleAI()
{
    //todo: hand-eye-coordination experience
    //todo: move paddle according to awareness determined by hand eye coordination
    //temp move accordint to x of token
    //emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::CharacteristicLeft, )
    qWarning() << tokenVelocity->currentX();
}

void aiPaddle::tokenAwareness(ogleEmblemVelocity* setTokenVelocity)
{
    tokenVelocity = setTokenVelocity;
}
