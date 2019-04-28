#include "videoframebuffer_openglwidget.h"

videoframebuffer_openglwidget::videoframebuffer_openglwidget()
{

}

void videoframebuffer_openglwidget::start()
{
    this->setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);
    this->setFixedSize(1920, 1080);
    this->move(0, 0);
    this->setWindowFlag(Qt::SubWindow);//This configuration hides window from taskbar and user.
    this->show();

    videoFrameWaitingToBeSplit = QVideoFrame();
    bufferedFrame = QImage(1920, 1080, QImage::Format_RGB32);
}

void videoframebuffer_openglwidget::paintEvent(QPaintEvent* event)
{
    //Copy video frame to QImage
    QVideoFrame VideoFrame = videoFrameWaitingToBeSplit;
    if(VideoFrame.width() > 0 && VideoFrame.height() > 0)
    {
        VideoFrame.map(QAbstractVideoBuffer::ReadOnly);
        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(VideoFrame.pixelFormat());
        QImage VideoFrameAsImage = QImage(VideoFrame.bits(), VideoFrame.width(), VideoFrame.height(), VideoFrame.bytesPerLine(), imageFormat);

        QImage tile = QImage(VideoFrame.width(), VideoFrame.height(), QImage::Format_RGB32);
        QPainter painter(&tile);
        painter.setCompositionMode(QPainter::CompositionMode_Source);

        int currentX = 0; int currentY = 0;
        bool keep_looping = true;
        while(keep_looping == true)
        {
            /** Low quality **/
            int pixelEX = currentX + 4;
            int pixelEY = currentY + 0;

            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            pixelEX = currentX + 4;
            pixelEY = currentY + 4;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            /** Medium Quality **/
            pixelEX = currentX + 8;
            pixelEY = currentY + 0;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            pixelEX = currentX + 8;
            pixelEY = currentY + 4;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            /** High Quality **/
            pixelEX = currentX + 2;
            pixelEY = currentY + 0;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            pixelEX = currentX + 6;
            pixelEY = currentY + 0;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            //next horizontal level
            pixelEX = currentX + 2;
            pixelEY = currentY + 2;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            pixelEX = currentX + 4;
            pixelEY = currentY + 2;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            pixelEX = currentX + 6;
            pixelEY = currentY + 2;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            pixelEX = currentX + 8;
            pixelEY = currentY + 2;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            //next horizontal level
            pixelEX = currentX + 6;
            pixelEY = currentY + 4;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);

            /** Sharp Quality **/
            pixelEX = currentX + 2;
            pixelEY = currentY + 4;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 3;
            pixelEY = currentY + 4;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 3;
            pixelEY = currentY + 5;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 2;
            pixelEY = currentY + 5;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 4;
            pixelEY = currentY + 5;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 3;
            pixelEY = currentY + 6;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);


            /** Next tile **/
            if(currentX < VideoFrameAsImage.width() - 1)
            {
                currentX += 8;
            }else
            {
                currentX = 0;
                currentY += 6;
            }

            if(currentY >= VideoFrameAsImage.height() - 1)
            {
              keep_looping = false;
            }
        }

        bufferedFrame = tile;
        painter.end();
    }
}

QImage videoframebuffer_openglwidget::frame(){ return bufferedFrame; }

void videoframebuffer_openglwidget::splitFrame(QVideoFrame VideoFrame)
{
    videoFrameWaitingToBeSplit = VideoFrame;
    this->update();
}

bool videoframebuffer_openglwidget::paintPixel(int x, int y, int stretchX, int stretchY, QImage sourceImage, QPainter *painter)
{
    bool output = false;
    if(x < sourceImage.width() - 1)
    {
        if(y < sourceImage.height() - 1)
        {
            painter->fillRect(x, y, stretchX, stretchY, sourceImage.pixel(x,y));
            output = true;
        }
    }
    return output;
}

QImage videoframebuffer_openglwidget::highQuality(QImage blank, QImage details, bool renderWithStretching)
{
    //NEEDS TO SKIP EVERY FOUR AND EIGHT
    QPainter painter(&blank);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    int currentX = 0;
    int currentY = 0;
    bool keep_looping = true;
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(details.pixel(currentX,currentY));
        painter.setPen(pen);

        if(renderWithStretching == true)
        {
            //currentX += 3;
            if(currentX < details.width()){ painter.fillRect(currentX+1,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX+1,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX+1,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX+= 2;//move to 5th pixel placement

            if(currentX < details.width()){ painter.fillRect(currentX+1,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX+1,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX+1,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX+= 2;//move to 9th pixel placement

        }else if(renderWithStretching == false)
        {
            if(currentX < details.width()){ painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX+= 2;//move to 5th pixel placement

            if(currentX < details.width()){ painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX++;
            if(currentX < details.width()){ painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY)); }
            currentX+= 2;//move to 9th pixel placement
        }

        if(currentX > details.width() - 1)
        {
            currentX = 0;
            currentY += 5;
        }

        if(currentY > details.height() - 1)
        {
            keep_looping = false;
        }
    }
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
            painter2.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));
        }else if(renderWithStretching == false)
        {
             painter2.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));
        }

        currentX += medInterval + medInterval + medInterval;//move 4, lands on 8, move 4

        if(currentX > details.width() - 1)
        {
            currentX = 0;
            currentY += medInterval + medInterval + medInterval;//move 4, lands on 8, move 4
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
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(details.pixel(currentX,currentY));
        painter.setPen(pen);
        if(renderWithStretching == true)
        {
            painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));
        }else if(renderWithStretching == false)
        {
            painter.fillRect(currentX,currentY,1,1,details.pixel(currentX,currentY));
        }

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


    int changeQualityNumber = QRandomGenerator::global()->bounded(100);
    if(changeQualityNumber < 30)
    {
        tQuality = QRandomGenerator::global()->bounded(2);
    }
    tQuality = 1;
    if(tQuality == 0)
    {
        QPainter painter(&output);
        painter.setOpacity(0.4);
        painter.drawImage(0,0,medQuality);
    }else if(tQuality == 1)
    {
        QPainter painter(&output);
        painter.setOpacity(0.9);
        painter.drawImage(0,0,highQuality);
        painter.setOpacity(0.5);
        painter.drawImage(0,0,medQuality);
        painter.setOpacity(0.5);
        painter.drawImage(0,0,lowQuality);
    }

    return output;
}


