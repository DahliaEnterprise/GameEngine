#ifndef HEAD_H
#define HEAD_H


#include <QObject>
#include "gameengine.h"
#include "gameengine/opengl.h"
#include <QThread>
#include <QTimer>
#include "examplegame/keyboardMouseInput/keyboardmouseinput.h"


class head : public QObject
{
    Q_OBJECT
public:
    explicit head(QObject *parent = nullptr);
    void start();

private:
    keyboardMouseInput* keyboardmouse_input;
    gameloop* game;
    gameengine* engine;
    QTimer* frameTimer;
    QThread* threadGpu;

signals:

public slots:

private slots:
    void frameTimeout();
    void slotPlayerRequestingCloseGame();
};

#endif // HEAD_H
