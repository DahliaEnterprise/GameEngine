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
    lowQualityFrameImage = this->lowQuality(lowQualityFrameImage, VideoFrameAsImage, false);

    //Medium Quality Frame
    QImage medQualityFrameImage = QImage(1280, 720, QImage::Format_ARGB32);
    medQualityFrameImage = this->medQuality(medQualityFrameImage, VideoFrameAsImage, false);

    QImage highQualityFrameImage = QImage(1280, 720, QImage::Format_ARGB32);
    //highQualityFrameImage = this->highQuality(highQualityFrameImage, VideoFrameAsImage, false);

    return this->temp_mergeframes(lowQualityFrameImage, medQualityFrameImage, highQualityFrameImage);
}

QImage videoframebuffer_openglwidget::highQuality(QImage blank, QImage details, bool renderWithStretching)
{
    //NEEDS TO SKIP EVERY THREE AND EIGHT
    //HIGH QUALITY STILL NOT SURE WHAT TO GRAB.....
    QPainter painter(&blank);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    int highQualityInterval = 1;
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
        //pixels++;
        if(renderWithStretching == true)
        {
            //Centered for stretching
            int tempCurrentX = currentX; int tempCurrentY = currentY;
            tempCurrentX += highQualityInterval - 1;
            tempCurrentY += highQualityInterval - 1;
            painter.fillRect(currentX,currentY,highQualityInterval,highQualityInterval,details.pixel(currentX,currentY));
        }else if(renderWithStretching == false)
        {
            painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));
        }

        currentX += highQualityInterval;

        if(currentX > details.width() - 1)
        {
            currentX = 0;
            currentY += highQualityInterval;
        }

        if(currentY > details.height() - 1)
        {
            keep_looping = false;
        }
    }
    qWarning() << pixels;
    return blank;
}

QImage videoframebuffer_openglwidget::medQuality(QImage blank, QImage details, bool renderWithStretching)
{
    //Initalize and transparent fill image.
    QPainter painter2(&blank);
    QPen transparentPen; transparentPen.setStyle(Qt::SolidLine); transparentPen.setColor(QColor(0,0,0,0));
    painter2.setPen(transparentPen);
    painter2.fillRect(0,0,1280,720,QColor(0,0,0,0));

    //Get med data
    int medInterval = 3;
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
            tempCurrentX -= 1;
            tempCurrentY -= 1;
            painter2.fillRect(tempCurrentX,
                              tempCurrentY,
                              medInterval,
                              medInterval,details.pixel(currentX,currentY));
        }else if(renderWithStretching == false)
        {
             painter2.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));
            //painter2.fillRect(currentX-2,currentY-2,4,4,details.pixel(currentX,currentY));
        }

        currentX += medInterval;

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


QImage videoframebuffer_openglwidget::temp_mergeframes(QImage lowQuality, QImage medQuality, QImage highQuality)
{
    QImage output = lowQuality;

    int quality = QRandomGenerator::global()->bounded(100);
    quality = 31;
    if(quality > 0 && quality < 30)
    {
        QPainter painter(&output);
        painter.drawImage(0,0,medQuality);


    }else if(quality >= 30)
    {
        QPainter painter(&output);
        painter.drawImage(0,0,medQuality);
        painter.drawImage(0,0,highQuality);
    }


    return output;

}
