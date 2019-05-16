#ifndef DAHLIABROADCAST_H
#define DAHLIABROADCAST_H

#include <QObject>

class dahliaBroadcast : public QObject
{
    Q_OBJECT
public:
    explicit dahliaBroadcast(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DAHLIABROADCAST_H