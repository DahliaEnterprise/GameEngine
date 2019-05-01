#include "videoframebuffer.h"

VideoFrameBuffer::VideoFrameBuffer(QObject *parent) : QObject(parent)
{

}

void VideoFrameBuffer::start()
{
    timestampLastFrame = QDateTime::currentMSecsSinceEpoch();
    openglPainter = new videoframebuffer_openglwidget();
    openglPainter->start();
}

void VideoFrameBuffer::appendFrame(QVideoFrame VideoFrame)
{
    qint64 msSinceLastFrame = QDateTime::currentMSecsSinceEpoch() - timestampLastFrame;
    //if(msSinceLastFrame > 1)
    //{
        openglPainter->splitFrame(VideoFrame);
        emit splitFrame(openglPainter->frame());
        timestampLastFrame = QDateTime::currentMSecsSinceEpoch();
    //}
}

QImage VideoFrameBuffer::frame(){ return openglPainter->frame(); }
