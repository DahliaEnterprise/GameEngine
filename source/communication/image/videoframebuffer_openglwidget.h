#ifndef VIDEOFRAMEBUFFER_OPENGLWIDGET_H
#define VIDEOFRAMEBUFFER_OPENGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QVideoFrame>
#include <QPainter>
#include <QDebug>
#include <QImage>
class videoframebuffer_openglwidget : public QOpenGLWidget
{
public:
    videoframebuffer_openglwidget();
    void start();
    QImage splitFrame(QVideoFrame VideoFrame);
    QImage temp_mergeframes(QImage lowQuality, QImage medQuality);

private:
    QImage lowQuality(QImage blank, QImage details);

};

#endif // VIDEOFRAMEBUFFER_OPENGLWIDGET_H
