#include "OpenGLEngine/oglemastercontroller.h"

ogleMasterController::ogleMasterController(QObject *parent) : QObject(parent)
{

}

void ogleMasterController::start()
{
    ///Show Window rendering data from OpenGL Engine
    window = new OGLEWindow(QOpenGLWindow::PartialUpdateBlit);window->start();window->resize(QSize(1280, 720));window->show();
}


OGLEWindow* ogleMasterController::getWindow(){return window;}
