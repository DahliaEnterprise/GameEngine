#include "card_turnactivatedcard.h"

card_turnactivatedcard::card_turnactivatedcard(QObject *parent) : QObject(parent)
{

}


void card_turnactivatedcard::start(QString imageUrl, QStringList setturnactivatedcard_list)
{
    QStringList::const_iterator iterator = setturnactivatedcard_list.constBegin();
    while(iterator != setturnactivatedcard_list.constEnd()){ turnactivatedcard_list.append(*iterator); iterator++; }
    isHighlighted = true;
    turnactivatedcardSourceImage = QImage(imageUrl);
    turnactivatedcardImage = QImage(612, 792, QImage::Format_ARGB32);
    QPainter painter(&turnactivatedcardImage);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setOpacity(1);
    painter.drawImage(QRectF(0,0,612,792), turnactivatedcardSourceImage);
    turnactivatedcardGo = new gameobject();
    turnactivatedcardGo->start(turnactivatedcardImage);

    //Repaint image to have a "highlighted" surrounding.
    turnactivatedcardHighlightedImage = QImage(612,792,QImage::Format_ARGB32);
    QPainter painter2(&turnactivatedcardHighlightedImage);
    painter2.setRenderHint(QPainter::HighQualityAntialiasing);
    painter2.drawImage(QRectF(0,0,612,792), turnactivatedcardSourceImage, QRectF(0,0,612,792));
    painter2.setOpacity(0.9);
    QPen green;
    green.setColor(QColor(Qt::green));
    green.setStyle(Qt::SolidLine);
    green.setWidth(20);
    painter2.setPen(green);
    painter2.drawRoundedRect(QRectF(0,0,612,792), 20, 20, Qt::AbsoluteSize);

}

gameobject* card_turnactivatedcard::gameObject(){ return turnactivatedcardGo; }

void card_turnactivatedcard::highlighted(bool setIsHighlighted)
{
    isHighlighted = setIsHighlighted;
    if(isHighlighted == true){ turnactivatedcardGo->start(turnactivatedcardHighlightedImage); }
    else if(isHighlighted == false){ turnactivatedcardGo->start(turnactivatedcardImage); }
}

void card_turnactivatedcard::updateImageSpecifications(double x, double y, double width, double height, double opacity){ turnactivatedcardGo->updateImageSpecifications(x,y,width,height,opacity); }

QStringList card_turnactivatedcard::card_actions(){ return turnactivatedcard_list; }
