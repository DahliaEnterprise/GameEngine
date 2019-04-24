#include "bufferawareframe.h"

bufferAwareFrame::bufferAwareFrame(QObject *parent) : QObject(parent)
{

}

void bufferAwareFrame::start(QImage setimage)
{
    wholeImage = setimage;

    //Pull one pixel every 16 pixels
    lowQualityNthPixel = 16;
    QList<QRgb> lowQuality;
    int currentPixelX = 0; int currentPixelY = 0; width = wholeImage.width(); height = wholeImage.height(); bool keep_looping = true;
    while(keep_looping == true)
    {
        int digitalWidthLimit = width - 1;
        if(currentPixelX <= digitalWidthLimit)
        {
            QRgb color = wholeImage.pixel(currentPixelX,currentPixelY);
            lowQuality.append(color);

            currentPixelX += lowQualityNthPixel;
        }


        if(currentPixelX > digitalWidthLimit)
        {
            currentPixelX = 0;
            currentPixelY++;
        }

        int digitalHeightLimit = height-1;
        if(currentPixelY > digitalHeightLimit)
        {
            keep_looping = 0;
        }
    }
}

void bufferAwareFrame::defineLowQualityWholeFrame(QList<QRgb> setlowQualityWholeFrame, int seteveryNthPixel){ lowQualityWholeFrame = setlowQualityWholeFrame; lowQualityNthPixel = seteveryNthPixel; }

QImage bufferAwareFrame::lowQualityImage()
{
    QImage lowQImage(width, height, wholeImage.format());
    QPainter painter(&lowQImage);

    int lowQualityWholeFrameIndex = 0;
    int currentPixelX = 0;
    int currentPixelY = 0;
    while(lowQualityWholeFrameIndex < lowQualityWholeFrame.length())
    {
        QBrush brush;
        //brush.setColor(QColor(lowQualityWholeFrame.at(lowQualityWholeFrameIndex)));
        brush.setColor(QColor(100,100,100,255));
        brush.setStyle(Qt::SolidPattern);
        painter.setBrush(brush);
        painter.drawRect(currentPixelX,currentPixelY,16,16);

        currentPixelX += lowQualityNthPixel;
        int digitalWidthLimit = width - 1;
        if(currentPixelX > digitalWidthLimit)
        {
            currentPixelX = 0;
            currentPixelY += lowQualityNthPixel;
        }
        lowQualityWholeFrameIndex++;
    }
    //return lowQImage;
    return wholeImage;
}
