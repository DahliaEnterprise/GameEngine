#ifndef PADDLE_H
#define PADDLE_H

#include <QObject>
#include <QDebug>
#include "OpenGLEngine/oglewindowmouseposition.h"
#include "OpenGLEngine/ogleemblem.h"
#include "OpenGLEngine/ogleemblem/ogleemblembox.h"
class paddle : public QObject
{
    Q_OBJECT
public:
    explicit paddle(QObject *parent = nullptr);
    void start(int setScreenWidth, int setScreenHeight);
    ogleEmblem* determine_frame();
    void updatedMousePosition(ogleWindowMousePosition* newMousePosition);

private:
    ogleEmblem* emblem;
    ogleEmblemBox* emblemBox;

    int screenWidth;
    int screenHeight;
    int mouseX;
    int mouseY;

signals:

public slots:
};

#endif // PADDLE_H