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

    //Low Quality frame
    QImage lowQualityFrameImage = QImage(1280, 720, QImage::Format_RGB32);
    lowQualityFrameImage = this->lowQuality(lowQualityFrameImage, VideoFrameAsImage);


    //Medium Quality Frame
    QImage medQualityFrameImage = QImage(1280, 720, QImage::Format_ARGB32);
    QPainter painter2(&medQualityFrameImage);
    QPen transparentPen; transparentPen.setStyle(Qt::SolidLine); transparentPen.setColor(QColor(0,0,0,0));
    painter2.setPen(transparentPen);
    painter2.fillRect(0,0,1280,720,QColor(0,0,0,0));



    return this->temp_mergeframes(lowQualityFrameImage, medQualityFrameImage);
}

QImage videoframebuffer_openglwidget::lowQuality(QImage blank, QImage details)
{
    QPainter painter(&blank);
    int currentX = 0;
    int currentY = 0;
    int lowSquareWidthHeight = 16;
    bool keep_looping = true;
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(details.pixel(currentX,currentY));
        painter.setPen(pen);
        painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));

        currentX += lowSquareWidthHeight;
        if(currentX > details.width() - 1)
        {
            currentX = 0;
            currentY += lowSquareWidthHeight;
        }

        if(currentY > details.height() - 1)
        {
            keep_looping = false;
        }
    }

    return blank;
}


QImage videoframebuffer_openglwidget::temp_mergeframes(QImage lowQuality, QImage medQuality)
{
    QImage output = lowQuality;

    QPainter painter(&output);
    painter.drawImage(0,0,medQuality);


    return output;
}
