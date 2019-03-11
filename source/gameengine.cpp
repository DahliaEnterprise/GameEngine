#include "gameengine.h"

gameengine::gameengine(QObject *parent) : QObject(parent)
{

}


void gameengine::start(keyboardMouseInput* setKeyboardMouse_input)
{
    keyboardmouse_input = setKeyboardMouse_input;

    openglCanvas = new opengl_canvas();
    openglCanvas->start();
    opengGl = new opengl(openglCanvas);
    opengGl->setStyleSheet(QString("QOpenGLWidget{margin:0;padding:0;}"));
    opengGl->start(keyboardmouse_input);
    opengGl->show();
}

opengl_canvas* gameengine::canvas(){ return openglCanvas; }
          void gameengine::frame(QList<gameobject*> goList){ openglCanvas->paintObjects(goList); opengGl->gpu_update(); }
          void gameengine::closeWindow(){ opengGl->hide(); }
