#include "camerasplitbyquality.h"

cameraSplitByQuality::cameraSplitByQuality(QObject *parent) : QObject(parent)
{

}

void cameraSplitByQuality::start()
{
    timer = new QTimer();
    timer->start(5);

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(splitQuality()));
}


void cameraSplitByQuality::requestSplitByQuality(QVideoFrame vFrame)
{
    //Append to buffer
    framesAwaitingToBeSplit.append(vFrame);
}


void cameraSplitByQuality::splitQuality()
{
    if(framesAwaitingToBeSplit.isEmpty() == false)
    {
        QVector<QColor> lowQFrame;
        QVideoFrame vFrame = framesAwaitingToBeSplit.first();
        vFrame.map(QAbstractVideoBuffer::ReadOnly);
        //QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(vFrame.pixelFormat());
        //QImage VideoFrameAsImage = QImage(vFrame.bits(), vFrame.width(), vFrame.height(), vFrame.bytesPerLine(), imageFormat);

        if(vFrame.width() > 0 && vFrame.height() > 0)
        {
            QVector<QColor> lowQualityFrame;

            int x = 0; int y = 0;
            bool alternate = false;
            for(int i = 0; i < vFrame.mappedBytes()-1; i+= 4)
            {
                uchar* bits = vFrame.bits();
                QColor color = QColor(bits[i], bits[i+1], bits[i+2], 255);
                if(alternate == false)
                {
                    alternate = true;
                }else if(alternate == true){
                    lowQualityFrame.append(color);
                    alternate = false;
                }

                x += 4;
                if(x >= vFrame.width()-1)
                {
                    x = 0;
                    y++;
                }

                if(y >= vFrame.height()-1)
                {
                    i = vFrame.mappedBytes();
                }
            }

            //todo create a class that groups qualities of frames

            emit renderedSplitQualities(lowQualityFrame);
        }
        framesAwaitingToBeSplit.removeFirst();
    }
}
