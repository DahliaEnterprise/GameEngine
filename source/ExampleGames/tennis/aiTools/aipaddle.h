#ifndef AIPADDLE_H
#define AIPADDLE_H

#include <QObject>
#include "OpenGLEngine/ogleemblem.h"
#include "OpenGLEngine/ogleemblem/ogleemblembox.h"
#include "OpenGLEngine/ogleemblem/ogleemblemvelocity.h"
#include <QTimer>
#include <QDebug>
class aiPaddle : public QObject
{
    Q_OBJECT
public:
    explicit aiPaddle(QObject *parent = nullptr);
    void initialize(int setScreenWidth, int setScreenHeight);
    ogleEmblem* determine_frame();
    void tokenAwareness(ogleEmblemVelocity* setTokenVelocity);

private:
    QTimer* timer;
    ogleEmblem* emblem;
    ogleEmblemBox* emblemBox;

    int screenWidth;
    int screenHeight;

    int paddleWidth;
    int paddleHeight;
    int paddleX;
    int paddleY;

    //Physics Awareness
    ogleEmblemVelocity* tokenVelocity;

signals:

public slots:
    void cycleAI();
};

#endif // AIPADDLE_H
