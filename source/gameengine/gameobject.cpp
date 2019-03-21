#include "gameobject.h"

gameobject::gameobject(QObject *parent) : QObject(parent)
{

}

gameobject::~gameobject()
{

}

void gameobject::start(QImage setImage)
{
    image = QImage(setImage);
}

void gameobject::updateImageSpecifications(double setx, double sety, double setwidth, double setheight, qreal setopacity)
{
    x = setx;
    y = sety;
    width = setwidth;
    height = setheight;
    opacity = setopacity;
}

void gameobject::paint(QPainter* painter)
{
    painter->setOpacity(opacity);
    painter->drawImage(QRectF(x, y, width, height), image);
    painter->setOpacity(1);
}
