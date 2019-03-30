#include "card_moduspraecptum.h"

card_moduspraecptum::card_moduspraecptum(QObject *parent) : QObject(parent)
{

}

void card_moduspraecptum::start(QString imageUrl, QStringList moduspraecptum_list)
{
    moduspraecptumCardSourceImage = QImage(imageUrl);
    moduspraecptumCardImage = QImage(792, 612, QImage::Format_ARGB32);
    QPainter painter(&moduspraecptumCardImage);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setOpacity(1);
    painter.drawImage(QRectF(0,0,792,612), moduspraecptumCardSourceImage);

    moduspraecptumGO = new gameobject();
    moduspraecptumGO->start(moduspraecptumCardImage);

    //Repaint image to have a "highlighted" surrounding.
    moduspraecptumCardHighlightedImage = QImage(792, 612, QImage::Format_ARGB32);
    QPainter painter2(&moduspraecptumCardHighlightedImage);
    painter2.setRenderHint(QPainter::HighQualityAntialiasing);
    painter2.drawImage(QRect(0,0,792,612), moduspraecptumCardSourceImage);
    painter2.setOpacity(0.6);
    QPen green;
    green.setColor(QColor(Qt::green));
    green.setStyle(Qt::SolidLine);
    green.setWidth(30);
    painter2.setPen(green);
    painter2.drawRoundedRect(QRectF(0,0,792,612), 20, 20, Qt::AbsoluteSize);
}

gameobject* card_moduspraecptum::gameObject(){ return moduspraecptumGO; }

void card_moduspraecptum::updateImageSpecification(double x, double y, double width, double height, double opacity){ moduspraecptumGO->updateImageSpecifications(x,y,width,height,opacity); }
