#include "card_creature.h"

card_creature::card_creature(QObject *parent) : QObject(parent)
{

}

void card_creature::start(QString imageUrl)
{
    isHighlighted = false;

    creatureCardSourceImage = QImage(imageUrl);
    creatureCardImage = QImage(612,792,QImage::Format_ARGB32);
    QPainter painter(&creatureCardImage);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setOpacity(0.9);
    painter.drawImage(QRectF(0,0,612,792), creatureCardSourceImage, QRectF(0,0,612,792));

    creatureCardGameObject = new gameobject();
    creatureCardGameObject->start(creatureCardImage);

    //Repaint image to have a "highlighted" surrounding.
    creatureCardHighlightedImage = QImage(612,792,QImage::Format_ARGB32);
    QPainter painter2(&creatureCardHighlightedImage);
    painter2.setRenderHint(QPainter::HighQualityAntialiasing);
    painter2.drawImage(QRectF(0,0,612,792), creatureCardSourceImage, QRectF(0,0,612,792));
    painter2.setOpacity(0.9);
    QPen green;
    green.setColor(QColor(Qt::green));
    green.setStyle(Qt::SolidLine);
    green.setWidth(30);
    painter2.setPen(green);
    painter2.drawRoundedRect(QRectF(0,0,612,792), 20, 20, Qt::AbsoluteSize);

}


gameobject* card_creature::gameObject(){ return creatureCardGameObject; }

void card_creature::highlighted(bool setIsHighlighted)
{
    isHighlighted = setIsHighlighted;
    if(isHighlighted== true){ creatureCardGameObject->start(creatureCardHighlightedImage);
    }else if(isHighlighted == false){ creatureCardGameObject->start(creatureCardImage); }
}

void card_creature::updateImageSpecifications(double x, double y, double width, double height, qreal opacity){ creatureCardGameObject->updateImageSpecifications(x, y, width, height, opacity); }

QMap<QString, double> card_creature::dimensions()
{
    return creatureCardGameObject->dimensions();
}
