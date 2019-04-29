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
#include <QPainter>
#include <QCameraViewfinderSettings>
#include "communication/image/videoframebuffer.h"
#include <QThread>
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

    gameobject* videostream_go;


    QThread* Thread_videoFrameBuffer;
    VideoFrameBuffer* videoFrameBuffer;


    QImage currentFrame;
    QImage bufferedFrame;

signals:
    void videoFrameBuffer_Frame(QVideoFrame);

public slots:


private slots:
    void videoFrameImage(QVideoFrame image);
    void updateBufferedFrame(QImage image);
};

#endif // COMMUNICATION_GRAPHICS_AND_PROCESSING_H
