#ifndef CAMERASPLITBYQUALITY_H
#define CAMERASPLITBYQUALITY_H

#include <QObject>
#include <QVideoFrame>
#include <QImage>
#include <QDebug>
#include <QVector>
#include <QTimer>
class cameraSplitByQuality : public QObject
{
    Q_OBJECT
public:
    explicit cameraSplitByQuality(QObject *parent = nullptr);
    void start();

private:
    QTimer* timer;
    QVector<QVideoFrame> framesAwaitingToBeSplit;

signals:
    void renderedSplitQualities(QVector<QColor>);

public slots:
    void requestSplitByQuality(QVideoFrame);

private slots:
    void splitQuality();
};

#endif // CAMERASPLITBYQUALITY_H
