#include "communication_graphics_and_processing.h"

communication_graphics_and_processing::communication_graphics_and_processing(QObject *parent) : QObject(parent)
{

}

void communication_graphics_and_processing::start()
{

    currentFrame = QImage(500,500,QImage::Format_ARGB32);
    //Initialize video frame game object
    cameraimage = new cameraImage();
    videostream_go = new gameobject();
    videostream_go->start(QImage(QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png")));


    //Initailize networking
    net = new network();

    //Initialize webcam stream
    camera = new QCamera();
    cameraViewfinder = new QCameraViewfinder();
    camera->setViewfinder(cameraViewfinder);
    camera->setCaptureMode(QCamera::CaptureVideo);

    videoProbe = new QVideoProbe();
    if(videoProbe->setSource(camera))
    {
        QObject::connect(videoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(videoFrameImage(QVideoFrame)));
    }

    camera->start();
}

/*
void communication_graphics_and_processing::processVideoFrame(QVideoFrame videoFrame)
{
    splitQualityByThree->appendVideoFrame(videoFrame);
    //deprecated:clientCamera_framesBuffered.append(videoFrame);
    //QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat());
    //videoFrame.map(QAbstractVideoBuffer::ReadOnly);//required to be called before calling ".bits()"
    //QImage image(videoFrame.bits(), videoFrame.width(), videoFrame.height(), videoFrame.bytesPerLine(), imageFormat);
    //videostream_go->start(image);

    bufferAwareFrame* bufferawareFrame = new bufferAwareFrame();
    bufferawareFrame->start(image);
    bufferAwareframes_list.append(bufferawareFrame);
    //bufferAwareframes_list.removeFirst();

}
*/


QList<gameobject*> communication_graphics_and_processing::frame()
{
    goList.clear();
    videostream_go->start(currentFrame);
    videostream_go->updateImageSpecifications(0,0,500,500,1);
    goList.append(videostream_go);

    return goList;
}

void communication_graphics_and_processing::videoFrameImage(QVideoFrame VideoFrameAsImage)
{
    VideoFrameAsImage.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(VideoFrameAsImage.pixelFormat());
    bufferedFrame = QImage(VideoFrameAsImage.bits(), VideoFrameAsImage.width(), VideoFrameAsImage.height(), VideoFrameAsImage.bytesPerLine(), imageFormat);
    QPainter painter(&currentFrame);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(QColor(100,153,238,255));
    painter.setPen(pen);
    painter.drawRect(0,0,100,100);
}
