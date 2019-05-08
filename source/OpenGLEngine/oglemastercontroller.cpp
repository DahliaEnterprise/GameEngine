#include "OpenGLEngine/oglemastercontroller.h"

ogleMasterController::ogleMasterController(QObject *parent) : QObject(parent)
{

}

void ogleMasterController::start()
{
    ///Show Window rendering data from OpenGL Engine
    window = new OGLEWindow();window->start();window->resize(QSize(1280, 720));window->show();
}
