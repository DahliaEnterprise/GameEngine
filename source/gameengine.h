#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include "gameengine/opengl.h"
#include "gameengine/opengl_canvas.h"
#include <QTimer>
#include "examplegame/gameloop.h"
class gameengine : public QObject
{
    Q_OBJECT

public:
    explicit gameengine(QObject *parent = nullptr);
    void start();
    opengl_canvas* canvas();

private:
    opengl* opengGl;
    opengl_canvas* openglCanvas;

signals:

public slots:
    void frame(QList<gameobject*> goList);

private slots:
};

#endif // GAMEENGINE_H
