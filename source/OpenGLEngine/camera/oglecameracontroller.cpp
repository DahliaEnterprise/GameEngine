#include "oglecameracontroller.h"

ogleCameraController::ogleCameraController(QObject *parent) : QObject(parent)
{

}

void ogleCameraController::start()
{
    camera = new QCamera();
    cameraViewFinder = new QCameraViewfinder(); camera->setViewfinder(cameraViewFinder);
    QCameraViewfinderSettings viewFinderSettings = camera->viewfinderSettings();
    viewFinderSettings.setResolution(1280,720);
    camera->setViewfinderSettings(viewFinderSettings);
    camera->setCaptureMode(QCamera::CaptureVideo);

    videoProbe = new QVideoProbe();
    if(videoProbe->setSource(camera)){ QObject::connect(videoProbe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(slotUnalteredCameraFrame(QVideoFrame)), Qt::QueuedConnection); }
    camera->start();
}


void ogleCameraController::slotUnalteredCameraFrame(QVideoFrame vFrame){ emit unalteredCameraFrame(vFrame); }
