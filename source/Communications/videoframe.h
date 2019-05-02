#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <QObject>

class videoFrame : public QObject
{
    Q_OBJECT
public:
    explicit videoFrame(QObject *parent = nullptr);

signals:

public slots:
};

#endif // VIDEOFRAME_H