#ifndef OPENGL_CANVAS_H
#define OPENGL_CANVAS_H

#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QList>
#include "gameengine/gameobject.h"
class opengl_canvas : public QObject
{
    Q_OBJECT
public:
    explicit opengl_canvas(QObject *parent = nullptr);
    void start();
    void paint(QPainter* painter, QPaintEvent* event);
    void paintObjects(QList<gameobject*> listOfGameObjects);

private:
    QList<gameobject*> ObjectsToSustainOnScreen;

signals:

public slots:
};

#endif // OPENGL_CANVAS_H
