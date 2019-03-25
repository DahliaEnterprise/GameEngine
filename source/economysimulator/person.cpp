#include "person.h"

person::person(QObject *parent) : QObject(parent)
{

}

void person::start()
{
    image = QImage(50, 50, QImage::Format_RGB32);
    QPainter painter(&image);
    QPen green;
    green.setColor(QColor(Qt::green));
    green.setStyle(Qt::SolidLine);
    green.setWidth(5);
    painter.setPen(green);
    painter.drawEllipse(QRectF(0,0,50,50));
    go = new gameobject();
    go->start(image);
}


gameobject* person::gameObject(){ return go; }


void person::updateImageSpecification(double x, double y, double width, double height, qreal opacity){ go->updateImageSpecifications(x,y,width,height,opacity); }

