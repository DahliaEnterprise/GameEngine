#include "tennis.h"

tennis::tennis(QObject *parent) : QObject(parent){}

void tennis::setOpenGLMasterController(ogleMasterController* setOgle){ogle = setOgle;OGLEMasterController_isSet=true;}

bool tennis::start()
{
    bool output = false;
    bool tennisIsReady = true;
    if(OGLEMasterController_isSet == true){QObject::connect(ogle, SIGNAL(frameRenderFinished()), this, SLOT(ogleAvailableForNextFrame())); }else{tennisIsReady = false; }

    return output;
}


void tennis::ogleAvailableForNextFrame()
{
    //TODO: if frame instructions are available, push frame
    // ogle->getWindow()->incomingNextFrame();
}
