#include "communicationscontroller.h"

CommunicationsController::CommunicationsController(QObject *parent) : QObject(parent)
{

}


void CommunicationsController::start()
{
    ///Initialize Modules Required to Communicate
    cameraController = new QCameraController();

    ///Begin Processor
    processorKeepAlive = new QTimer();
    processorKeepAlive->start(100);
    QObject::connect(processorKeepAlive, SIGNAL(timeout()), this, SLOT(processor()));
}

void CommunicationsController::processor()
{
    //Emit video frame instructions
    videoFrame* vFrame = new videoFrame();
    videoFrameInstruction* loadingText = new videoFrameInstruction();
    loadingText->text(QString("Detecting Camera"));
    vFrame->appendVideoFrameInstruction(loadingText);

    emit screenVideoFrame(vFrame);

    ///Run processor again
    QTimer::singleShot(1, this, SLOT(processor()));
}


