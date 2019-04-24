#ifndef SPLITWHOLEIMAGEINTOTHREEQUALITIES_H
#define SPLITWHOLEIMAGEINTOTHREEQUALITIES_H

#include <QObject>
#include <QVideoFrame>
#include <QList>
#include <QImage>
class splitWholeImageIntoThreeQualities : public QObject
{
    Q_OBJECT
public:
    explicit splitWholeImageIntoThreeQualities(QObject *parent = nullptr);

private:
    QList<QVideoFrame> videoFrames;


signals:
    void videoFrameImage(QImage image);

public slots:
    void appendVideoFrame(QVideoFrame videoFrame);
};

#endif // SPLITWHOLEIMAGEINTOTHREEQUALITIES_H
