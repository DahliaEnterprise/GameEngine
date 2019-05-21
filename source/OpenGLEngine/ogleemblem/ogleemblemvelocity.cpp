#include "ogleemblemvelocity.h"

ogleEmblemVelocity::ogleEmblemVelocity(QObject *parent) : QObject(parent)
{

}

void ogleEmblemVelocity::start(QPointF point1, QPointF point2){angle = QLineF(point1, point2);}
qreal ogleEmblemVelocity::direction(){return angle.angle();}
qreal ogleEmblemVelocity::speed(){return angle.length();}
QPointF ogleEmblemVelocity::currentPosition(){return angle.p1();}
QPointF ogleEmblemVelocity::nextPosition(){return angle.p2();}
void ogleEmblemVelocity::setVelocity(QPointF point1, QPointF point2){angle = QLineF(point1, point2);}
