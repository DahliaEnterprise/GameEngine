#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QObject *parent = nullptr);
    void start();

private:
    QTcpServer* server;
    QTcpSocket* socket;

signals:

public slots:
};

#endif // NETWORK_H
