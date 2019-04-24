#include "communication_graphics_and_processing.h"

communication_graphics_and_processing::communication_graphics_and_processing(QObject *parent) : QObject(parent)
{

}

void communication_graphics_and_processing::start()
{
    threadSplitQualityByThree = new QThread();
    splitQualityByThree = new splitWholeImageIntoThreeQualities();
    splitQualityByThree->moveToThread(threadSplitQualityByThree);
    threadSplitQualityByThree->start();

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
    if(videoProbe->setSource(camera)){ QObject::connect(videoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), splitQualityByThree, SLOT(appendVideoFrame(QVideoFrame))); }

    camera->start();

    QObject::connect(splitQualityByThree, SIGNAL(videoFrameImage(QImage)), this, SLOT(videoFrameImage(QImage)));
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
    //videostream_go->start(QImage(QString(":/examplegame/quickgame/image/card/creature/creature_stallion.png")));
    //videostream_go->updateImageSpecifications(0,0,500,500,1);
    goList.append(videostream_go);

    return goList;
}

void communication_graphics_and_processing::videoFrameImage(QImage image)
{
    videostream_go->start(image);
    videostream_go->updateImageSpecifications(0,0,500,500,1);
}
