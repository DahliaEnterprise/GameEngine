#include "communicationscontroller.h"

CommunicationsController::CommunicationsController(QObject *parent) : QObject(parent)
{

}


void CommunicationsController::start()
{
    ///Initialize Modules Required to Communicate
    videoFrame.reserve(1023);
    cameraController = new QCameraController();

    ///Begin Processor
    processorKeepAlive = new QTimer();
    processorKeepAlive->start(100);
    QObject::connect(processorKeepAlive, SIGNAL(timeout()), this, SLOT(processor()));
}

void CommunicationsController::offscreenWork(){}//change offscreenwork to emit offscreenwork to ogle

void CommunicationsController::onscreenWork(){}//change onscreenwork to emit onscreenwork to ogle

void CommunicationsController::processor()
{
    //todo: offscreenWork(gpuWork*)
    //Todo: screenVideoFrame(videoFrame*);

    /** DEPRECATED
    //Emit onscreenwork to show a "loading" text.
    videoFrame.clear();

    videoFrameInstruction* loadingText = new videoFrameInstruction();
    loadingText->text(QString("Detecting Camera"));
    videoFrame.append(loadingText);

    emit videoFrameInstructions(videoFrame);
    **/
    ///Run processor again
    QTimer::singleShot(5, this, SLOT(processor()));
}
