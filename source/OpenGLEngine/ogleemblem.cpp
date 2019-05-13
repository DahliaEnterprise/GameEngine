#include "ogleemblem.h"

ogleEmblem::ogleEmblem(QObject *parent) : QObject(parent)
{

}

void ogleEmblem::determine_frame()
{

}

void ogleEmblem::start(ogleEmblemBox* setBox){emblemDatatype=EmblemType::TypeBox;box=setBox;}
ogleEmblemBox* ogleEmblem::getEmblemBox(){ return box;}

ogleEmblem::EmblemType ogleEmblem::getEmblemType(){return emblemDatatype;}

