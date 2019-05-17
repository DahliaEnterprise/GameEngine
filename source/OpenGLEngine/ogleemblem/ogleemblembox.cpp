#include "ogleemblembox.h"

ogleEmblemBox::ogleEmblemBox(QObject *parent) : QObject(parent)
{
    prerendered_available = false;
}

void ogleEmblemBox::defineEveryCharacteristic(QColor setborder, QColor setfill, int settop, int setleft, int setwidth, int setheight){border=setborder;fill=setfill;top=settop;left=setleft;width=setwidth;height=setheight;}

void ogleEmblemBox::selectiveCharacteristicUpdate(characteristic property, QVariant value)
{
    if(characteristic::CharacteristicLeft == property){int newLeft=value.toInt();left=newLeft;}
    else if(characteristic::CharacteristicTop == property){int newTop=value.toInt();top=newTop;}
}

QVariant ogleEmblemBox::getCharacteristic(characteristic property)
{
    QVariant output;
    if(CharacteristicTop == property){output=QVariant(top);
    }else if(CharacteristicLeft == property){output=QVariant(left);
    }else if(CharacteristicWidth == property){output=QVariant(width);
    }else if(CharacteristicHeight == property){output=QVariant(height);}
    return output;
}

QColor ogleEmblemBox::getBorderColor(){return border;}
QColor ogleEmblemBox::getFillColor(){return fill;}

//
void ogleEmblemBox::incomingPrerender(QImage updatedPrerender){prerendered_available=true;
                                                               prendered=updatedPrerender.copy(0,0,updatedPrerender.width(), updatedPrerender.height());}
QImage ogleEmblemBox::getPrerendered(){ return prendered;}
bool ogleEmblemBox::prerenderedAvailable(){return prerendered_available;}
