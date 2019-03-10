#include "gameengine.h"

gameengine::gameengine(QObject *parent) : QObject(parent)
{

}


void gameengine::start()
{
    openglCanvas = new opengl_canvas();
    openglCanvas->start();
    opengGl = new opengl(openglCanvas);
    opengGl->setStyleSheet(QString("QOpenGLWidget{margin:0;padding:0;}"));
    opengGl->start();
    opengGl->show();
}

opengl_canvas* gameengine::canvas(){ return openglCanvas; }
          void gameengine::frame(QList<gameobject*> goList){ openglCanvas->paintObjects(goList); opengGl->gpu_update(); }
