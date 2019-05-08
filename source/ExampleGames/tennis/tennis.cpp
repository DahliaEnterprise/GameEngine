#include "tennis.h"

tennis::tennis(QObject *parent) : QObject(parent){}
void tennis::start()
{
    //TODO: check for master controller is set before continuing start function


}
void tennis::setOpenGLMasterController(ogleMasterController* setOgle){ogle = setOgle;}
