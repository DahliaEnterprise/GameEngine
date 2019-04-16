#ifndef COMMUNICATION_GRAPHICS_AND_PROCESSING_H
#define COMMUNICATION_GRAPHICS_AND_PROCESSING_H

#include <QObject>
#include "communication/network/network.h"
class communication_graphics_and_processing : public QObject
{
    Q_OBJECT
public:
    explicit communication_graphics_and_processing(QObject *parent = nullptr);
    void start();

private:
    network* net;
signals:

public slots:
};

#endif // COMMUNICATION_GRAPHICS_AND_PROCESSING_H
