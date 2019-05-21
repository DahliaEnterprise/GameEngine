#include "OpenGLEngine/oglemastercontroller.h"

ogleMasterController::ogleMasterController(QObject *parent) : QObject(parent){}
void ogleMasterController::start()
{
    ///Show Window rendering data from OpenGL Engine
    window = new OGLEWindow(QOpenGLWindow::PartialUpdateBlit);window->start();window->resize(QSize(1280, 720));window->show();QObject::connect(window, SIGNAL(frameRenderFinished()), this, SLOT(frameRenderFinished()));
    ///Startup Game Script
    t = new tennis();t->start();
    mousePositionUpdateTimer = new QTimer();
    QObject::connect(mousePositionUpdateTimer, SIGNAL(timeout()), this, SLOT(updatedMousePosition()));
    mousePositionUpdateTimer->start(15);
}
//OGLEWindow* ogleMasterController::getWindow(){return window;}
void ogleMasterController::frameRenderFinished()
{
    window->nextFrame(t->determine_frame());
}
void ogleMasterController::updatedMousePosition(){t->updatedMousePosition(window->getMousePosition());}
