#include "gameobject.h"

gameobject::gameobject(QObject *parent) : QObject(parent)
{

}

void gameobject::start(QImage setImage)
{
    image = setImage;
}

void gameobject::updateImageSpecifications(double setx, double sety, double setwidth, double setheight)
{
    x = setx;
    y = sety;
    width = setwidth;
    height = setheight;
}

void gameobject::paint(QPainter* painter)
{
    painter->drawImage(QRectF(x, y, width, height), image);
}
