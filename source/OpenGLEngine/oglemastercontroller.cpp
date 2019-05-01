#include "oglemastercontroller.h"

ogleMasterController::ogleMasterController(QObject *parent) : QObject(parent)
{

}

void ogleMasterController::start()
{
    window = new OGLEWindow();
    window->show();
}
