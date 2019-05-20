#include "ogleemblemvelocity.h"

ogleEmblemVelocity::ogleEmblemVelocity(QObject *parent) : QObject(parent)
{

}

void ogleEmblemVelocity::start(QPoint point1, QPoint point2){angle = QLine(point1, point2);}


int ogleEmblemVelocity::currentX(){ return 1;}

qreal ogleEmblemVelocity::direction(){angle.angle();}
qreal ogleEmblemVelocity::speed(){return angle.length();}
