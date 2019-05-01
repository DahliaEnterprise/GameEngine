#ifndef VIDEOFRAMEBUFFER_OPENGLWIDGET_H
#define VIDEOFRAMEBUFFER_OPENGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVideoFrame>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QRandomGenerator>
#include <QPaintEvent>
#include <QDateTime>
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
    bool paintLowQualityPixel(int x, int y, int stretchX, int stretchY, QImage sourceImage, QPainter *painter);

    QVideoFrame videoFrameWaitingToBeSplit;
    QImage bufferedFrame;

    QVector<QVector<QRgb>> lowQualityTiles;

    int tQuality = 0;

    int frames = 0;
    qint64 timestamp_sincelastsecond;

protected:
    void paintEvent(QPaintEvent* event);


};

#endif // VIDEOFRAMEBUFFER_OPENGLWIDGET_H
