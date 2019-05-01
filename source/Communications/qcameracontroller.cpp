#include "qcameracontroller.h"

QCameraController::QCameraController(QObject *parent) : QObject(parent)
{

}

void QCameraController::start()
{
    camera = new QCamera();
    viewFinderSettings = new QCameraViewfinderSettings();

}

QCamera* QCameraController::getCamera(){ return camera; }
