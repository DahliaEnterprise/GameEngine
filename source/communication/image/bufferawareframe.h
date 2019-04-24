#ifndef BUFFERAWAREFRAME_H
#define BUFFERAWAREFRAME_H

#include <QObject>
#include <QList>
#include <QRgb>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QDebug>
#include <QBrush>
class bufferAwareFrame : public QObject
{
    Q_OBJECT
public:
    explicit bufferAwareFrame(QObject *parent = nullptr);
    void start(QImage image);
    void defineLowQualityWholeFrame(QList<QRgb> setlowQualityWholeFrame, int everyNthPixel);
    QImage lowQualityImage();

private:
    QImage wholeImage;

    //Whole image specification
    int width;
    int height;

    //Low Quality
    int lowQualityNthPixel;
    QList<QRgb> lowQualityWholeFrame;

signals:

public slots:
};

#endif // BUFFERAWAREFRAME_H
