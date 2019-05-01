#include "oglemastercontroller.h"

ogleMasterController::ogleMasterController(QObject *parent) : QObject(parent)
{

}

void ogleMasterController::start()
{

    window = new OGLEWindow();


    communicationsControl = new CommunicationsController();
    window->defineCommunicationsController(communicationsControl);

    window->show();
}
