#include "communication_graphics_and_processing.h"

communication_graphics_and_processing::communication_graphics_and_processing(QObject *parent) : QObject(parent)
{

}

void communication_graphics_and_processing::start()
{
    //Initialize video frame game object
    cameraimage = new cameraImage();
    videostream_go = new gameobject();
    videostream_go->start(QImage());


    //Initailize networking
    net = new network();

    //Initailize frame to display


    //Initialize webcam stream
    camera = new QCamera();
    cameraViewfinder = new QCameraViewfinder();
    camera->setViewfinder(cameraViewfinder);
    camera->setCaptureMode(QCamera::CaptureVideo);

    videoProbe = new QVideoProbe();
    if(videoProbe->setSource(camera)){ QObject::connect(videoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processVideoFrame(QVideoFrame))); }

    camera->start();
}

void communication_graphics_and_processing::processVideoFrame(QVideoFrame videoFrame)
{
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat());
    videoFrame.map(QAbstractVideoBuffer::ReadOnly);//required to be called before calling ".bits()"
    QImage image(videoFrame.bits(), videoFrame.width(), videoFrame.height(), videoFrame.bytesPerLine(), imageFormat);
    videostream_go->start(image);
    x++;
    videostream_go->updateImageSpecifications(x,0,500,500,1);
    cameraimage->incomingFrame(image);
    qWarning() << x;
}



QList<gameobject*> communication_graphics_and_processing::frame()
{
    goList.clear();
    goList.append(videostream_go);

    return goList;
}
