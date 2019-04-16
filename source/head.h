#ifndef HEAD_H
#define HEAD_H


#include <QObject>
#include "gameengine.h"
#include "gameengine/opengl.h"
#include <QThread>
#include <QTimer>
#include "modules/keyboardMouseInput/keyboardmouseinput.h"
#include "communication/communication.h"

class head : public QObject
{
    Q_OBJECT
public:
    explicit head(QObject *parent = nullptr);
    void start();

private:
    int startupAppType;
    keyboardMouseInput* keyboardmouse_input;
    gameloop* game;
    communication* comms;
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
