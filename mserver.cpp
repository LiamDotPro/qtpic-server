#include "mserver.h"

MServer::MServer(QObject *parent) :
    QTcpServer(parent)
{
    if(this->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Started successfully";
    } else {
        qDebug() << "Start failed.";
    }
}

void MServer::incomingConnection(qintptr handle)
{
    Client *client = new Client(this);
    client->setSocket(handle);
}
