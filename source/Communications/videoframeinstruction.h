#ifndef VIDEOFRAMEINSTRUCTION_H
#define VIDEOFRAMEINSTRUCTION_H

#include <QObject>

class videoFrameInstruction : public QObject
{
    Q_OBJECT
public:
    explicit videoFrameInstruction(QObject *parent = nullptr);

    //
    int instructionType();

    //
    void text(QString textToDisplay);
    QString getText();

    //
    void unalteredCameraVideo(int setFpsMonitorId, int setMaxFps, double setX, double setY, double setWidth, double setHeight);
    int unalteredCameraVideo_getMaxFps();
    int unalteredCameraVideo_getFpsMonitorId();

    //
    void splitQualitiesCameraVideo(int setFpsMonitorId, int setMaxFps, double setX, double setY, double setWidth, double setHeight);

    //
    enum VideoInstructionDataType{Text,
                                  UnalteredCameraVideoFrame,
                                  SplitQualitiesVideoFrame};

private:

    ///Instruction Data Types
    //data type indicator
    int instructionDataType = -1;

    //Common
    double x,y,width,height;
    int maxFps,fpsMonitorId;

    //Text
    QString textString;


signals:

public slots:
};

#endif // VIDEOFRAMEINSTRUCTION_H
