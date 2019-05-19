#ifndef AIPADDLE_H
#define AIPADDLE_H

#include <QObject>
#include "OpenGLEngine/ogleemblem.h"
#include "OpenGLEngine/ogleemblem/ogleemblembox.h"
#include <QTimer>
class aiPaddle : public QObject
{
    Q_OBJECT
public:
    explicit aiPaddle(QObject *parent = nullptr);
    void initialize(int setScreenWidth, int setScreenHeight);
    ogleEmblem* determine_frame();

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

signals:

public slots:
    void cycleAI();
};

#endif // AIPADDLE_H
