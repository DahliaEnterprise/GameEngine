#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
class camera : public QObject
{
    Q_OBJECT
public:
    explicit camera(QObject *parent = nullptr);
    void start();

private:

signals:

public slots:
};

#endif // CAMERA_H
