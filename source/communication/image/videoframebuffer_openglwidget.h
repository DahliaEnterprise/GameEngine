#ifndef VIDEOFRAMEBUFFER_OPENGLWIDGET_H
#define VIDEOFRAMEBUFFER_OPENGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QVideoFrame>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QRandomGenerator>
class videoframebuffer_openglwidget : public QOpenGLWidget
{
public:
    videoframebuffer_openglwidget();
    void start();
    QImage splitFrame(QVideoFrame VideoFrame);
    QImage temp_mergeframes(QImage lowQuality, QImage medQuality, QImage highQuality);

private:
    int tempQuality = 0;

    QImage highQuality(QImage blank, QImage details, bool renderWithStretching = true);
    QImage medQuality(QImage blank, QImage details, bool renderWithStretching);
    QImage lowQuality(QImage blank, QImage details, bool renderWithStretching = true);
};

#endif // VIDEOFRAMEBUFFER_OPENGLWIDGET_H
