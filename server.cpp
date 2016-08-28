#include "server.h"
#include "thread.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
}

void Server::start() {
    int port = 1234;

    if(!this->listen(QHostAddress::Any, port)) {
        qDebug() << "start failed";
    } else {
        qDebug() << "listening on port " << port;
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << socketDescriptor << " connecting..";

    Thread *t = new Thread(socketDescriptor, this);

    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    t->start();
}
