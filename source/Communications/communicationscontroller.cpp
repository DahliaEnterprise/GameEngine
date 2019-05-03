#include "communicationscontroller.h"

CommunicationsController::CommunicationsController(QObject *parent) : QObject(parent)
{

}


void CommunicationsController::start()
{
    targetVFIrate = 120;
    timebetweenFrames = 1000 / targetVFIrate;

    ///Begin Processor
    processorKeepAlive = new QTimer();
    processorKeepAlive->start(1000);
    QObject::connect(processorKeepAlive, SIGNAL(timeout()), this, SLOT(processor()));
}

void CommunicationsController::processor()
{
    //Emit video frame instructions
    videoFrame* vFrameOnScreen = new videoFrame();



        /*videoFrameInstruction* unalteredCameraFrame = new videoFrameInstruction();
        unalteredCameraFrame->unalteredCameraVideo(1, 60, 0,0,1280,720);
        vFrame->appendVideoFrameInstruction(unalteredCameraFrame);

        videoFrameInstruction* loadingText = new videoFrameInstruction();
        loadingText->text(QString("Detecting Camera"));
        vFrame->appendVideoFrameInstruction(loadingText);*/

        videoFrameInstruction* splitQualititesCameraFrame = new videoFrameInstruction();
        splitQualititesCameraFrame->splitQualitiesCameraVideo(2, 60, 0,0,1280,720);
        vFrameOnScreen->appendVideoFrameInstruction(splitQualititesCameraFrame);

    emit screenVideoFrame(vFrameOnScreen);
/*
    //Emit offscreen video frame instructions
    videoFrame* vFrameOffScreen = new videoFrame();

        videoFrameInstruction* splitQualititesCameraFrame = new videoFrameInstruction();
        splitQualititesCameraFrame->splitQualitiesCameraVideo(2, 60, 0,0,1280,720);
        vFrameOffScreen->appendVideoFrameInstruction(splitQualititesCameraFrame);

    //emit offScreenVideoFrame(vFrameOffScreen);
*/
    ///Run processor again
    QTimer::singleShot(timebetweenFrames, this, SLOT(processor()));
}


