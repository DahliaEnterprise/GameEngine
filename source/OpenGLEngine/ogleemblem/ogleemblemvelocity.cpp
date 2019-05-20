#include "ogleemblemvelocity.h"

ogleEmblemVelocity::ogleEmblemVelocity(QObject *parent) : QObject(parent)
{

}

void ogleEmblemVelocity::start(QPoint point1, QPoint point2){angle = QLine(point1, point2);}
qreal ogleEmblemVelocity::direction(){return angle.angle();}
qreal ogleEmblemVelocity::speed(){return angle.length();}
QPointF ogleEmblemVelocity::currentPosition(){return angle.p1();}
void ogleEmblemVelocity::setVelocity(QPoint point1, QPoint point2){angle = QLine(point1, point2);}
