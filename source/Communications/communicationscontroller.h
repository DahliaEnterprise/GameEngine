#ifndef COMMUNICATIONSCONTROLLER_H
#define COMMUNICATIONSCONTROLLER_H

#include <QObject>

class CommunicationsController : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationsController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COMMUNICATIONSCONTROLLER_H