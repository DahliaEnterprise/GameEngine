#include "videoframebuffer_openglwidget.h"

videoframebuffer_openglwidget::videoframebuffer_openglwidget()
{

}

void videoframebuffer_openglwidget::start()
{
    this->setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);
}

QImage videoframebuffer_openglwidget::splitFrame(QVideoFrame VideoFrame)
{
    VideoFrame.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(VideoFrame.pixelFormat());
    QImage VideoFrameAsImage = QImage(VideoFrame.bits(), VideoFrame.width(), VideoFrame.height(), VideoFrame.bytesPerLine(), imageFormat);
    QImage lowQualityFrameImage = QImage(1280, 720, imageFormat);
    QPainter painter(&lowQualityFrameImage);

    //Low Quality frame
    int currentX = 0;
    int currentY = 0;
    int lowSquareWidthHeight = 8;
    bool keep_looping = true;
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(VideoFrameAsImage.pixel(currentX,currentY));
        painter.setPen(pen);
        painter.fillRect(currentX,currentY,8,8,VideoFrameAsImage.pixel(currentX,currentY));

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

    return lowQualityFrameImage;
}
