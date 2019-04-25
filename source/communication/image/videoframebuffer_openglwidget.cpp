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
    lowQualityFrameImage = this->lowQuality(lowQualityFrameImage, VideoFrameAsImage, true);

    //Medium Quality Frame
    QImage medQualityFrameImage = QImage(1280, 720, QImage::Format_ARGB32);
    medQualityFrameImage = this->medQuality(medQualityFrameImage, VideoFrameAsImage, true);

    return this->temp_mergeframes(lowQualityFrameImage, medQualityFrameImage);
}

QImage videoframebuffer_openglwidget::medQuality(QImage blank, QImage details, bool renderWithStretching)
{
    //Initalize and transparent fill image.
    QPainter painter2(&blank);
    QPen transparentPen; transparentPen.setStyle(Qt::SolidLine); transparentPen.setColor(QColor(0,0,0,0));
    painter2.setPen(transparentPen);
    painter2.fillRect(0,0,1280,720,QColor(0,0,0,0));

    //Get med data
    int medInterval = 4;
    int currentX = 0;
    int currentY = 0;
    bool keep_looping = true;
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(details.pixel(currentX,currentY));
        painter2.setPen(pen);

        if(renderWithStretching == true)
        {
            //Centered for stretching
            int tempCurrentX = currentX; int tempCurrentY = currentY;
            tempCurrentX += medInterval/2;
            tempCurrentY += medInterval/2;
            painter2.fillRect(tempCurrentX,
                              tempCurrentY,
                              medInterval,
                              medInterval,details.pixel(currentX,currentY));
        }else if(renderWithStretching == false)
        {
             painter2.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));
            //painter2.fillRect(currentX-2,currentY-2,4,4,details.pixel(currentX,currentY));
        }

        currentX += medInterval/2;

        if(currentX > details.width() - 1)
        {
            currentX = 0;
            currentY += medInterval;
        }

        if(currentY > details.height() - 1)
        {
            keep_looping = false;
        }

    }
    return blank;
}

QImage videoframebuffer_openglwidget::lowQuality(QImage blank, QImage details, bool renderWithStretching)
{
    QPainter painter(&blank);
    int lowSquareWidthHeight = 8;
    int currentX = 0;
    int currentY = 0;
    bool keep_looping = true;
    int pixels = 0;
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(details.pixel(currentX,currentY));
        painter.setPen(pen);
        if(renderWithStretching == true)
        {
            painter.fillRect(currentX,currentY,lowSquareWidthHeight,lowSquareWidthHeight,details.pixel(currentX,currentY));
        }else if(renderWithStretching == false)
        {
            painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));

        }
        pixels++;

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

    QRandomGenerator random;
    int quality = QRandomGenerator::global()->bounded(10);
    if(quality > 0 && quality < 8)
    {
        QPainter painter(&output);
        painter.drawImage(0,0,medQuality);

    }

    return output;
}
