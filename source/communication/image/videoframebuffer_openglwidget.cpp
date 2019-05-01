#include "videoframebuffer_openglwidget.h"

videoframebuffer_openglwidget::videoframebuffer_openglwidget()
{

}

void videoframebuffer_openglwidget::start()
{
    this->setWindowTitle(QString("GPU ACCESS"));
    this->setUpdateBehavior(QOpenGLWidget::PartialUpdate);
    this->setFixedSize(1280, 720);
    this->move(0, 0);
    this->setWindowFlag(Qt::SubWindow);//This configuration hides window from taskbar and user.
    this->show();

    videoFrameWaitingToBeSplit = QVideoFrame();
    bufferedFrame = QImage(1280, 720, QImage::Format_ARGB32_Premultiplied);
    timestamp_sincelastsecond = QDateTime::currentMSecsSinceEpoch();
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

        QImage tile = QImage(VideoFrame.width(), VideoFrame.height(), QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&tile);
        painter.setOpacity(1);
        painter.setCompositionMode(QPainter::CompositionMode_Source);

        lowQualityTiles.clear();

        int currentX = 0; int currentY = 0;
        bool keep_looping = true;
        while(keep_looping == true)
        {
            QVector<QRgb> lowQualityTile_pixelColorList;

            /** Low quality **/
            int pixelEX = currentX + 4;
            int pixelEY = currentY + 0;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);
            if(this->paintLowQualityPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter) == true){ lowQualityTile_pixelColorList.append(VideoFrameAsImage.pixel(pixelEX,pixelEY)); }

            pixelEX = currentX + 4;
            pixelEY = currentY + 4;
            this->paintPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter);
            if(this->paintLowQualityPixel(pixelEX, pixelEY, 2, 2, VideoFrameAsImage, &painter) == true){ lowQualityTile_pixelColorList.append(VideoFrameAsImage.pixel(pixelEX,pixelEY)); }

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
            //this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 3;
            pixelEY = currentY + 5;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 2;
            pixelEY = currentY + 5;
            //this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 4;
            pixelEY = currentY + 5;
            //this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 3;
            pixelEY = currentY + 6;
            //this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            /** Ultra Quality **/
            pixelEX = currentX + 0;
            pixelEY = currentY + 0;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 0;
            pixelEY = currentY + 2;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 0;
            pixelEY = currentY + 4;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 1;
            pixelEY = currentY + 1;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 3;
            pixelEY = currentY + 1;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 5;
            pixelEY = currentY + 1;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 7;
            pixelEY = currentY + 1;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 1;
            pixelEY = currentY + 3;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 1;
            pixelEY = currentY + 5;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 3;
            pixelEY = currentY + 3;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 5;
            pixelEY = currentY + 3;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 7;
            pixelEY = currentY + 3;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);


            pixelEX = currentX + 5;
            pixelEY = currentY + 5;
            this->paintPixel(pixelEX, pixelEY, 1, 1, VideoFrameAsImage, &painter);

            pixelEX = currentX + 7;
            pixelEY = currentY + 5;
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

    frames++;
    qint64 currentTimestamp = QDateTime::currentMSecsSinceEpoch();
    if((currentTimestamp - timestamp_sincelastsecond) >= 1000)
    {
        qWarning() << frames << "frames per second.";
        frames = 0;
        timestamp_sincelastsecond = currentTimestamp;
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
            painter->fillRect(x, y, 2, 2, sourceImage.pixel(x,y));
            output = true;
        }
    }
    return output;
}

bool videoframebuffer_openglwidget::paintLowQualityPixel(int x, int y, int stretchX, int stretchY, QImage sourceImage, QPainter *painter)
{//networking and painting -- todo finish
    bool output = false;
    if(x < sourceImage.width() - 1)
    {
        if(y < sourceImage.height() - 1)
        {
            //painter->fillRect(x, y, 1, 1, sourceImage.pixel(x,y));
            output = true;
        }
    }
    return output;
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


