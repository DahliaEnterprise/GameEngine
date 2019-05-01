#ifndef QCAMERACONTROLLER_H
#define QCAMERACONTROLLER_H

#include <QObject>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraViewfinderSettings>

class QCameraController : public QObject
{
    Q_OBJECT
public:
    explicit QCameraController(QObject *parent = nullptr);
    void start();

    QCamera* getCamera();

private:
    QCamera* camera;
    QCameraViewfinderSettings* viewFinderSettings;

signals:

public slots:
};

#endif // QCAMERACONTROLLER_H
