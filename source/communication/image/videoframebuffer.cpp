#include "videoframebuffer.h"

VideoFrameBuffer::VideoFrameBuffer(QObject *parent) : QObject(parent)
{

}

void VideoFrameBuffer::start()
{
    openglPainter = new videoframebuffer_openglwidget();
    openglPainter->start();
    bufferedFrame = QImage(1280,720, QImage::Format_RGB32);
}

void VideoFrameBuffer::appendFrame(QVideoFrame VideoFrame)
{
    bufferedFrame = openglPainter->splitFrame(VideoFrame);


    ////// POSSIBLY DEPRECATED WAY
    /*
    VideoFrame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(VideoFrame.pixelFormat());
    QImage VideoFrameAsImage = QImage(VideoFrame.bits(), VideoFrame.width(), VideoFrame.height(), VideoFrame.bytesPerLine(), imageFormat);
    bufferedFrame = QImage(1280,720, QImage::Format_RGB32);
    QPainter painter(&bufferedFrame);

    //Low Quality frame
    int currentX = 0;
    int currentY = 0;
    int lowSquareWidthHeight = 8;
    bool keep_looping = true;
    /*
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(bufferedFrame.pixel(currentX,currentY));
        painter.setPen(pen);
        painter.fillRect(currentX,currentY,lowSquareWidthHeight,lowSquareWidthHeight,bufferedFrame.pixel(currentX,currentY));

        currentX += lowSquareWidthHeight;
        if(currentX > VideoFrameAsImage.width() - 1)
        {
            currentX = 0;
            currentY += lowSquareWidthHeight;
        }

        if(currentY > VideoFrameAsImage.height() - 1)
        {
            keep_looping = false;
        }
    }


    //Medium Quality Frame
    currentX = 0; currentY = 0;
    int medSquareWidthHeight = 4;
    keep_looping = true;
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(bufferedFrame.pixel(currentX,currentY));
        painter.setPen(pen);
        painter.fillRect(currentX,currentY,medSquareWidthHeight,medSquareWidthHeight,bufferedFrame.pixel(currentX,currentY));

        currentX += medSquareWidthHeight;
        if(currentX > VideoFrameAsImage.width() - 1)
        {
            currentX = 0;
            currentY += medSquareWidthHeight;
        }

        if(currentY > VideoFrameAsImage.height() - 1)
        {
            keep_looping = false;
        }
    }
    */

    //High quality frame -- every character must manualy be coded for this frame.

}

QImage VideoFrameBuffer::frame()
{
    return bufferedFrame;
}
