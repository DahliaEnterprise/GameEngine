#include "camerasplitbyquality.h"

cameraSplitByQuality::cameraSplitByQuality(QObject *parent) : QObject(parent)
{

}

void cameraSplitByQuality::start()
{
    timer = new QTimer();
    timer->start(30);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(splitQuality()), Qt::QueuedConnection);
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
        qint64 timestart = QDateTime::currentMSecsSinceEpoch();
        QVector<QColor> lowQFrame;
        QVideoFrame vFrame = framesAwaitingToBeSplit.first();
        vFrame.map(QAbstractVideoBuffer::ReadOnly);
        QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(vFrame.pixelFormat());
        QImage VideoFrameAsImage = QImage(vFrame.bits(), vFrame.width(), vFrame.height(), vFrame.bytesPerLine(), imageFormat);

        if(vFrame.width() > 0 && vFrame.height() > 0)
        {
            QVector<QColor> lowQualityFrame;
            uchar* bits = vFrame.bits();
            for(qint64 i = 0; i < vFrame.mappedBytes(); i += 4)
            {

                std::string red( reinterpret_cast< char const* >(bits[i]) );
                qWarning() << QString::fromStdString(red);
                //TODO convert bits to integer
                QColor color = QColor::fromRgb(bits[i], bits[i+1], bits[i+2], bits[i+3]);
                //qWarning() << bits[i] << " " << bits[i+1] << " " << bits[i+2] << " " << bits[i+3] << " " << bits[i+4];
                lowQualityFrame.append(color);
            }

            //todo create a class that groups qualities of frames

            emit renderedSplitQualities(lowQualityFrame);
        }

        qWarning() << (QDateTime::currentMSecsSinceEpoch() - timestart);
        framesAwaitingToBeSplit.removeFirst();
    }
}
