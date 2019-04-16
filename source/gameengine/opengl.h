#ifndef OPENGL_H
#define OPENGL_H

#include <QObject>
#include <QOpenGLWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QPaintEvent>
#include "gameengine/opengl_canvas.h"
#include <QPainter>
#include <QDebug>
#include "modules/keyboardMouseInput/keyboardmouseinput.h"

class opengl : public QOpenGLWidget
{
    Q_OBJECT
public:
    opengl(opengl_canvas* setCanvas);
    void start(keyboardMouseInput* setKeyboardMouseInput);
    void gpu_update();

private:
    //Global Scope
    opengl_canvas* canvas;
    keyboardMouseInput* keyboardmouse_input;

protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    //void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
};

#endif // OPENGL_H
