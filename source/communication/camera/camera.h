#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QCamera>
class camera : public QObject
{
    Q_OBJECT
public:
    explicit camera(QObject *parent = nullptr);
    void start();

signals:

public slots:
};

#endif // CAMERA_H
