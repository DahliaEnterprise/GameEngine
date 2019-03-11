#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QObject>
#include "gameengine/opengl_canvas.h"
#include "examplegame/mainmenu/mainmenu.h"
#include <QTimer>
#include <QList>
#include "gameengine/gameobject.h"
#include "examplegame/keyboardMouseInput/keyboardmouseinput.h"

class gameloop : public QObject
{
    Q_OBJECT
public:
    explicit gameloop(QObject *parent = nullptr);
    void setCanvas(opengl_canvas* incomingCanvas);
    void start(keyboardMouseInput* setKeyboardMouseInput);
    QList<gameobject*> frame();

private:
    keyboardMouseInput* keyboardmouseInput;
    mainmenu* gui_mainmenu;

signals:
    void playerRequestingCloseGame();

public slots:
};

#endif // GAMELOOP_H
