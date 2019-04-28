#ifndef VIDEOFRAMEBUFFER_OPENGLWIDGET_H
#define VIDEOFRAMEBUFFER_OPENGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QVideoFrame>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QRandomGenerator>
#include <QPaintEvent>
class videoframebuffer_openglwidget : public QOpenGLWidget
{
public:
    videoframebuffer_openglwidget();
    void start();
    void splitFrame(QVideoFrame VideoFrame);
    QImage temp_mergeframes(QImage lowQuality, QImage medQuality, QImage highQuality);
    QImage frame();

private:
    bool paintPixel(int x, int y, int stretchX, int stretchY, QImage sourceImage, QPainter* painter);

    QVideoFrame videoFrameWaitingToBeSplit;
    QImage bufferedFrame;

    int tQuality = 0;

protected:
    void paintEvent(QPaintEvent* event);


};

#endif // VIDEOFRAMEBUFFER_OPENGLWIDGET_H
