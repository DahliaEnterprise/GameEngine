#ifndef VIDEOFRAMEBUFFER_H
#define VIDEOFRAMEBUFFER_H

#include <QObject>
#include <QVideoFrame>
#include <QDebug>
#include <QPainter>
#include <QDateTime>
#include "communication/image/videoframebuffer_openglwidget.h"
class VideoFrameBuffer : public QObject
{
    Q_OBJECT
public:
    explicit VideoFrameBuffer(QObject *parent = nullptr);
    void start();
    QImage frame();

private:
    videoframebuffer_openglwidget* openglPainter;

signals:

public slots:
    void appendFrame(QVideoFrame frame);
};

#endif // VIDEOFRAMEBUFFER_H
