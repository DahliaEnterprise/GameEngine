#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <QObject>
#include "gameengine/opengl_canvas.h"
#include "examplegame/quickgame/quickgame.h"
#include <QTimer>
#include <QList>
#include "gameengine/gameobject.h"
#include "examplegame/keyboardMouseInput/keyboardmouseinput.h"

class gameloop : public QObject
{
    Q_OBJECT
public:
    explicit gameloop(QObject *parent = nullptr);
    ~gameloop();
    void setCanvas(opengl_canvas* incomingCanvas);
    void start(keyboardMouseInput* setKeyboardMouseInput);
    QList<gameobject*> frame();
    void stop();

private:
    keyboardMouseInput* keyboardmouseInput;
    quickgame* quickGame;

signals:
    void playerRequestingCloseGame();

public slots:
};

#endif // GAMELOOP_H
