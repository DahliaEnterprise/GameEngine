#include "opengl_canvas.h"

//Note: might need a buffer in place of a mutex lock.
opengl_canvas::opengl_canvas(QObject *parent) : QObject(parent)
{

}

void opengl_canvas::stop()
{

}

void opengl_canvas::start()
{
    ObjectsToSustainOnScreen = QList<gameobject*>();
}

void opengl_canvas::paint(QPainter* painter, QPaintEvent* event)
{
    QList<gameobject*>::const_iterator iterator = ObjectsToSustainOnScreen.constBegin();
    while(iterator != ObjectsToSustainOnScreen.constEnd())
    {
        gameobject* object_to_draw = *iterator;
        object_to_draw->paint(painter);

        iterator++;
    }
}

void opengl_canvas::paintObjects(QList<gameobject*> listOfGameObjects)
{
    ObjectsToSustainOnScreen.clear();
    QList<gameobject*>::const_iterator iterator = listOfGameObjects.constBegin();
    while(iterator != listOfGameObjects.constEnd())
    {
        gameobject* objectToDraw = *iterator;
        ObjectsToSustainOnScreen.append(objectToDraw);
        iterator++;
    }
}
