#include "communication_graphics_and_processing.h"

communication_graphics_and_processing::communication_graphics_and_processing(QObject *parent) : QObject(parent)
{

}

void communication_graphics_and_processing::start()
{
    //Initialize incoming video feed as video frame buffer
    Thread_videoFrameBuffer = new QThread();
    videoFrameBuffer = new VideoFrameBuffer();
    videoFrameBuffer->start();
    videoFrameBuffer->moveToThread(Thread_videoFrameBuffer);
    Thread_videoFrameBuffer->start();
    QObject::connect(this, SIGNAL(videoFrameBuffer_Frame(QVideoFrame)), videoFrameBuffer, SLOT(appendFrame(QVideoFrame)));
    QObject::connect(videoFrameBuffer, SIGNAL(splitFrame(QImage)), this, SLOT(updateBufferedFrame(QImage)));
    currentFrame = QImage(1280,720,QImage::Format_ARGB32);
    bufferedFrame = QImage(1280,720,QImage::Format_ARGB32);

    //Initialize video frame game object
    videostream_go = new gameobject();
    videostream_go->start(QImage(QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png")));


    //Initailize networking
    net = new network();
    net->start();

    //Initialize webcam stream
    camera = new QCamera();

    cameraViewfinder = new QCameraViewfinder();
    camera->setViewfinder(cameraViewfinder);
    QCameraViewfinderSettings viewFinderSettings = camera->viewfinderSettings();
    viewFinderSettings.setResolution(1280,720);

    camera->setViewfinderSettings(viewFinderSettings);
    camera->setCaptureMode(QCamera::CaptureVideo);

    videoProbe = new QVideoProbe();
    if(videoProbe->setSource(camera))
    {
        QObject::connect(videoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(videoFrameImage(QVideoFrame)));
    }

    camera->start();
}

QList<gameobject*> communication_graphics_and_processing::frame()
{
    goList.clear();
    videostream_go->start(bufferedFrame /*videoFrameBuffer->frame()*/);
    videostream_go->updateImageSpecifications(0,0,1280,720,1);
    goList.append(videostream_go);

    return goList;
}

void communication_graphics_and_processing::videoFrameImage(QVideoFrame VideoFrameAsImage)
{
    //VideoFrameAsImage(Client Camera) To VideoFrameBuffer(Split into three qualities)
    emit videoFrameBuffer_Frame(VideoFrameAsImage);
}

void communication_graphics_and_processing::updateBufferedFrame(QImage image)
{
    QImage image2 = image.scaled(1280,720, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    bufferedFrame = image2;
}



