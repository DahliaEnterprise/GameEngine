#include "communicationscontroller.h"

CommunicationsController::CommunicationsController(QObject *parent) : QObject(parent)
{

}


void CommunicationsController::start()
{
    targetVFIrate = 60;
    timebetweenFrames = 1000 / targetVFIrate;

    ///Begin Processor
    processorKeepAlive = new QTimer();
    processorKeepAlive->start(1000);
    QObject::connect(processorKeepAlive, SIGNAL(timeout()), this, SLOT(processor()));
}

void CommunicationsController::processor()
{
    //Emit video frame instructions
    videoFrame* vFrame = new videoFrame();
        videoFrameInstruction* loadingText = new videoFrameInstruction();
        loadingText->text(QString("Detecting Camera"));
        vFrame->appendVideoFrameInstruction(loadingText);

        videoFrameInstruction* unalteredCameraFrame = new videoFrameInstruction();
        unalteredCameraFrame->unalteredCameraVideo(1, 60, 0,0,1280,720);
        vFrame->appendVideoFrameInstruction(unalteredCameraFrame);

    emit screenVideoFrame(vFrame);

    ///Run processor again
    QTimer::singleShot(timebetweenFrames, this, SLOT(processor()));
}


