#ifndef OGLECAMERACONTROLLER_H
#define OGLECAMERACONTROLLER_H

#include <QObject>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraViewfinderSettings>
#include <QVideoProbe>

class ogleCameraController : public QObject
{
    Q_OBJECT
public:
    explicit ogleCameraController(QObject *parent = nullptr);
    void start();

private:
    QCamera* camera;
    QCameraViewfinder* cameraViewFinder;
    QVideoProbe* videoProbe;

signals:
    void videoFrame(QVideoFrame);
    void unalteredCameraFrame(QVideoFrame);

public slots:
    void slotUnalteredCameraFrame(QVideoFrame);

};

#endif // OGLECAMERACONTROLLER_H
