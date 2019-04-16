#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include "gameengine/opengl.h"
#include "gameengine/opengl_canvas.h"
#include <QTimer>
#include "examplegame/gameloop.h"
#include "modules/keyboardMouseInput/keyboardmouseinput.h"

class gameengine : public QObject
{
    Q_OBJECT

public:
    explicit gameengine(QObject *parent = nullptr);
    ~gameengine();
    void stop();
    void start(keyboardMouseInput* setKeyboardMouse_input);
    opengl_canvas* canvas();
    void closeWindow();

private:
    opengl* opengGl;
    opengl_canvas* openglCanvas;

    //Global Scope
    keyboardMouseInput* keyboardmouse_input;

signals:

public slots:
    void frame(QList<gameobject*> goList);

private slots:
};

#endif // GAMEENGINE_H
