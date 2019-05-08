#include "ogleMasterController.h"

ogleMasterController::ogleMasterController(QObject *parent) : QObject(parent)
{

}

void ogleMasterController::start()
{
    ///Display
    window = new OGLEWindow();
    window->start();
    window->resize(QSize(1280, 720));
    window->show();
}
