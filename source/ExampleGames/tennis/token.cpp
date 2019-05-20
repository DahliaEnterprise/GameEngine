#include "token.h"

token::token(QObject *parent) : QObject(parent)
{

}

void token::initialize(int setScreenWidth, int setScreenHeight)
{
    screenWidth = setScreenWidth;screenHeight = setScreenHeight;
    currentX = setScreenWidth/2;currentY = setScreenHeight/2;
    velocityX += 2;velocityY += 2;
    emblemBox = new ogleEmblemBox();emblemBox->defineEveryCharacteristic(QColor(100,100,100,255), QColor(100,100,100,255), 10,100,20,20);
    emblem = new ogleEmblem();emblem->start(emblemBox);
    emblemVelocity = new ogleEmblemVelocity();emblemVelocity->start(QPoint(currentX, currentY), QPoint(currentX+2, currentY+2));
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
    QPoint point1 = QPoint(currentX, currentY);
    currentX += velocityX;
    currentY += velocityY;

    //TODO:"register" ability to rotate and aim toward token

    //bounce off edges of screen

    if(currentX >= screenWidth)
    {
        velocityX = -2;
        currentX += velocityX;
        //TODO: determine new direction using velocity
        //emblemVelocity->surfaceAngle(QPointF(screenWidth,0), QPointF(screenWidth,screenHeight));
    }

    if(currentY >= screenHeight)
    {
        velocityY = -2;
        currentY += velocityY;
    }

    if(currentY <= 0)
    {
        velocityY = 2;
        currentY += velocityY;
    }

    if(currentX <= 0)
    {
        velocityX = 2;
        currentX += velocityX;
    }
    QPoint point2 = QPoint(currentX, currentY);
    emblemVelocity->setVelocity(point1, point2);
}

ogleEmblemVelocity* token::getVelocity(){return emblemVelocity;}
