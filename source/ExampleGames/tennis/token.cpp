#include "token.h"

token::token(QObject *parent) : QObject(parent)
{
    screenWidth = 0;screenHeight = 0;currentX = 0;currentY = 0;velocityX = 0;velocityY = 0;
}

void token::initialize(int setScreenWidth, int setScreenHeight)
{
    screenWidth=setScreenWidth;screenHeight=setScreenHeight;
    currentX = 500;currentY = 500;
    velocityX = currentX + 2;velocityY = currentX + 2;
    emblemVelocity = new ogleEmblemVelocity();
    emblemVelocity->start(QPoint(currentX, currentY), QPoint(currentX+2, currentY+2));
    emblemBox = new ogleEmblemBox();
    emblemBox->defineEveryCharacteristic(QColor(100,100,100,255), QColor(100,100,100,255), currentX,currentY,20,20);
    emblem = new ogleEmblem();emblem->start(emblemBox);
    qWarning() << currentX << " " << currentY;

}

ogleEmblem* token::determine_frame()
{
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::CharacteristicTop, currentY);
    emblemBox->selectiveCharacteristicUpdate(ogleEmblemBox::CharacteristicLeft, currentX);
    return emblem;
}

void token::cycleLogic()
{
    QPointF currentPosition = emblemVelocity->currentPosition();
    QPointF nextPosition = emblemVelocity->nextPosition();
    bool nextPositionStillValid = true;
    qWarning() << currentPosition << " " << nextPosition;
    //Bounce off screen edges
    if(currentPosition.x() >= screenWidth)
    {
        QPointF newPosition = QPointF(currentPosition.x()-1, currentPosition.y());
        emblemVelocity->setVelocity(currentPosition, newPosition);
        nextPositionStillValid = false;
    }

    if(currentPosition.y() >= screenHeight)
    {
        QPointF newPosition = QPointF(currentPosition.x(), currentPosition.y()-1);
        emblemVelocity->setVelocity(currentPosition, newPosition);
        nextPositionStillValid = false;
    }

    if(currentPosition.y() <= 0)
    {
        QPointF newPosition = QPointF(currentPosition.x(), currentPosition.y()+1);
        emblemVelocity->setVelocity(currentPosition, newPosition);
        nextPositionStillValid = false;
    }

    if(currentPosition.x() <= 0)
    {
        QPointF newPosition = QPointF(currentPosition.x()+1, currentPosition.y());
        emblemVelocity->setVelocity(currentPosition, newPosition);
        nextPositionStillValid = false;
    }

    //Bounce off paddle
    //TODO: get velocity of token, get velocity of paddle
    //TODO: determine reflective angle

    if(nextPositionStillValid == true)
    {
        qreal xVelocity = nextPosition.x() - currentPosition.x();
        qreal yVelocity = nextPosition.y() - currentPosition.y();
        QPointF newVelocity = QPointF(nextPosition.x() + xVelocity, nextPosition.y() + yVelocity);
        emblemVelocity->setVelocity(nextPosition, newVelocity);
    }

    /*
qWarning() << currentX << " " << currentY;
    currentX += velocityX;
    currentY += velocityY;
    QPoint point1 = QPoint(currentX, currentY);
qWarning() << currentX << " " << currentY;
    //TODO:"register" ability to rotate and aim toward token

    //bounce off edges of screen

    if(currentX >= screenWidth)
    {
        velocityX = -1;
        currentX += velocityX;
        //TODO: determine new direction using velocity
        //emblemVelocity->surfaceAngle(QPointF(screenWidth,0), QPointF(screenWidth,screenHeight));
        //emblemVelocity->setVelocity(QPoint(emblemVelocity->currentPosition().x(), emblemVelocity->currentPosition().y()), QPoint(0,0));
    }

    if(currentY >= screenHeight)
    {
        velocityY = -1;
        currentY += velocityY;
    }

    if(currentY <= 0)
    {
        velocityY = 1;
        currentY += velocityY;
    }

    if(currentX <= 0)
    {
        velocityX = 1;
        currentX += velocityX;
    }
    QPoint point2 = QPoint(currentX, currentY);
    qWarning() << currentX << " " << currentY;
    emblemVelocity->setVelocity(point1, point2);
    */
}

ogleEmblemVelocity* token::getVelocity(){return emblemVelocity;}
