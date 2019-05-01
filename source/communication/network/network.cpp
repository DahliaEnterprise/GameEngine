#include "network.h"

network::network(QObject *parent) : QObject(parent)
{

}

void network::start()
{
    quint16 recvPort = 8080;

    server = new QTcpServer();
    server->listen(QHostAddress::Any, recvPort);

    socket = new QTcpSocket();
    socket->connectToHost(QString("127.0.0.1"), recvPort, QIODevice::ReadWrite);
    qWarning() << socket->waitForConnected();

}

