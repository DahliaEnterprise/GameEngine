#include "splitwholeimageintothreequalities.h"

splitWholeImageIntoThreeQualities::splitWholeImageIntoThreeQualities(QObject *parent) : QObject(parent)
{

}

void splitWholeImageIntoThreeQualities::appendVideoFrame(QVideoFrame videoFrame)
{
    //todo: videoFrames.append(videoFrame);
    //for now...
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat());
    videoFrame.map(QAbstractVideoBuffer::ReadOnly);//required to be called before calling ".bits()"
    QImage image(videoFrame.bits(), videoFrame.width(), videoFrame.height(), videoFrame.bytesPerLine(), imageFormat);
    emit videoFrameImage(image);
}
