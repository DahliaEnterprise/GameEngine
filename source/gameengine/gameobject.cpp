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

QMap<QString, double> gameobject::dimensions()
{
    QMap<QString, double> output;

    output.insert(QString("x"), x);
    output.insert(QString("y"), y);
    output.insert(QString("w"), width);
    output.insert(QString("h"), height);
    output.insert(QString("o"), opacity);

    return output;
}
