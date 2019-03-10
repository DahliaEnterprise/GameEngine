#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QObject>
#include "gameengine/opengl_canvas.h"
#include "examplegame/mainmenu/mainmenu.h"
#include <QTimer>
#include <QList>
#include "gameengine/gameobject.h"
class gameloop : public QObject
{
    Q_OBJECT
public:
    explicit gameloop(QObject *parent = nullptr);
    void setCanvas(opengl_canvas* incomingCanvas);
    void start();
    QList<gameobject*> frame();

private:
    mainmenu* gui_mainmenu;
    QTimer* cycleTimer;

    //Global Scope
    opengl_canvas* canvas;

signals:

public slots:

};

#endif // GAMELOOP_H
