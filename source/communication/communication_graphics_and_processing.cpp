#include "communication_graphics_and_processing.h"

communication_graphics_and_processing::communication_graphics_and_processing(QObject *parent) : QObject(parent)
{

}

void communication_graphics_and_processing::start()
{
    currentFrame = QImage(1280,720,QImage::Format_ARGB32);
    bufferedFrame = QImage(1280,720,QImage::Format_ARGB32);
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
    videostream_go->updateImageSpecifications(0,0,1280,720,1);
    goList.append(videostream_go);

    return goList;
}

void communication_graphics_and_processing::videoFrameImage(QVideoFrame VideoFrameAsImage)
{
    VideoFrameAsImage.map(QAbstractVideoBuffer::ReadOnly);
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(VideoFrameAsImage.pixelFormat());
    bufferedFrame = QImage(VideoFrameAsImage.bits(), VideoFrameAsImage.width(), VideoFrameAsImage.height(), VideoFrameAsImage.bytesPerLine(), imageFormat);

    QPainter painter(&currentFrame);

    //Low Quality frame
    int currentX = 0; int currentY = 0; int horizontalInterval = 64;
    bool keep_looping = true;
    while(keep_looping == true)
    {
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setColor(bufferedFrame.pixel(currentX,currentY));
        painter.setPen(pen);
        painter.fillRect(currentX,currentY,horizontalInterval,horizontalInterval,bufferedFrame.pixel(currentX,currentY));

        currentX += horizontalInterval;
        if(currentX > VideoFrameAsImage.width() - 1)
        {
            currentX = 0;
            currentY += horizontalInterval;
        }

        if(currentY > VideoFrameAsImage.height() - 1)
        {
            keep_looping = false;
        }
    }

    //Medium Quality Frame
    int centerSize = 32;
    //todo:process of square quality of center of low quality frame.
    keep_looping = true;
    while(keep_looping == true)
    {

    }
}
