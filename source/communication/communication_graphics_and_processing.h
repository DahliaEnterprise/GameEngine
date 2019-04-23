#ifndef COMMUNICATION_GRAPHICS_AND_PROCESSING_H
#define COMMUNICATION_GRAPHICS_AND_PROCESSING_H

#include <QObject>
#include "communication/network/network.h"
#include <QFile>
#include <QCamera>
#include <QCameraViewfinder>
#include <QVideoProbe>
#include <QDebug>
#include <QDir>
#include "gameengine/gameobject.h"
#include <QList>
#include "communication/camera/cameraimage.h"
#include "communication/image/bufferawareframe.h"
#include <QThread>
#include "communication/image/splitwholeimageintothreequalities.h"
class communication_graphics_and_processing : public QObject
{
    Q_OBJECT
public:
    explicit communication_graphics_and_processing(QObject *parent = nullptr);
    void start();
    QList<gameobject*> frame();

private:
    network* net;

    QCamera* camera;
    QCameraViewfinder* cameraViewfinder;
    QVideoProbe* videoProbe;
    QList<gameobject*> goList;

    cameraImage* cameraimage;
    gameobject* videostream_go;
    QList<bufferAwareFrame*> bufferAwareframes_list;
    QList<QVideoFrame> clientCamera_framesBuffered;

    QThread* threadSplitQualityByThree;
    splitWholeImageIntoThreeQualities* splitQualityByThree;

signals:

public slots:

private slots:
    void videoFrameImage(QImage image);
};

#endif // COMMUNICATION_GRAPHICS_AND_PROCESSING_H
