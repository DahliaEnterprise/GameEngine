#include "token.h"

token::token(QObject *parent) : QObject(parent)
{

}

void token::start(int setScreenWidth, int setScreenHeight)
{
    currentX = setScreenWidth/2;
    currentY = setScreenHeight/2;
    velocityX += 2;
    velocityY += 2;
    emblemBox = new ogleEmblemBox();emblemBox->defineEveryCharacteristic(QColor(100,100,100,255), QColor(100,100,100,255), 10,100,20,20);
    emblem = new ogleEmblem();emblem->start(emblemBox);
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(cyclePhysics()));
    timer->start(5);
}

ogleEmblem* token::determine_frame()
{
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::CharacteristicTop, currentY);
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::CharacteristicLeft, currentX);
    return emblem;
}

void token::cyclePhysics()
{
    currentX += velocityX;
    currentY += velocityY;
}
