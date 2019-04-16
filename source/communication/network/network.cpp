#include "network.h"

network::network(QObject *parent) : QObject(parent)
{

}

void network::start()
{
    server->listen(QHostAddress::Any, 6060);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(incomingNewConnection()));

    //socket->connectToHost()
}
