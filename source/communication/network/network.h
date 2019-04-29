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
    QTcpSocket* socket;

signals:

public slots:

private slots:
};

#endif // NETWORK_H
