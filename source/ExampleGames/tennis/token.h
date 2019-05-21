#ifndef TOKEN_H
#define TOKEN_H

#include <QObject>
#include "OpenGLEngine/ogleemblem.h"
#include "OpenGLEngine/ogleemblem/ogleemblembox.h"
#include <QTimer>
#include "OpenGLEngine/ogleemblem/ogleemblemvelocity.h"
#include <QDebug>
class token : public QObject
{
    Q_OBJECT
public:
    explicit token(QObject *parent = nullptr);
    void initialize(int setScreenWidth, int setScreenHeight);
    ogleEmblem* determine_frame();
    ogleEmblemVelocity* getVelocity();
    void cycleLogic();

private:
    QTimer* timer;
    ogleEmblem* emblem;
    ogleEmblemBox* emblemBox;
    ogleEmblemVelocity* emblemVelocity;

    int screenWidth;
    int screenHeight;

    int currentX;
    int currentY;

    int velocityX;
    int velocityY;

signals:

public slots:

private slots:
};

#endif // TOKEN_H
