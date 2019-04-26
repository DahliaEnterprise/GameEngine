#include "videoframebuffer.h"

VideoFrameBuffer::VideoFrameBuffer(QObject *parent) : QObject(parent)
{

}

void VideoFrameBuffer::start()
{
    openglPainter = new videoframebuffer_openglwidget();
    //QObject::connect(open)
    openglPainter->start();
    bufferedFrame = QImage(1280,720, QImage::Format_RGB32);
}

void VideoFrameBuffer::appendFrame(QVideoFrame VideoFrame)
{
    openglPainter->splitFrame(VideoFrame);
}

QImage VideoFrameBuffer::frame()
{
    return openglPainter->frame();
}
