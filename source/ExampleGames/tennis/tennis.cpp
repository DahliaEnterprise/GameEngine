#include "tennis.h"

tennis::tennis(QObject *parent) : QObject(parent){}

void tennis::start(){ logic = new tennis_script();logic->start();mousePosition=new ogleWindowMousePosition();}


QVector<ogleEmblem*> tennis::determine_frame(){return logic->determine_frame();}


void tennis::updatedMousePosition(ogleWindowMousePosition* newMousePosition)
{
    mousePosition=newMousePosition;
    logic->updatedMousePosition(newMousePosition);
}
