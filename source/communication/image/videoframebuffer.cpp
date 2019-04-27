#include "videoframebuffer.h"

VideoFrameBuffer::VideoFrameBuffer(QObject *parent) : QObject(parent)
{

}

void VideoFrameBuffer::start()
{
    openglPainter = new videoframebuffer_openglwidget();
    openglPainter->start();
}

void VideoFrameBuffer::appendFrame(QVideoFrame VideoFrame)
{
    openglPainter->splitFrame(VideoFrame);
}

QImage VideoFrameBuffer::frame(){ return openglPainter->frame(); }
