#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    
}

void Client::setSocket(int handle) {
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(handle);
    
    socket->connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    socket->connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        
    qDebug() << "Client connected";
}

void Client::connected() {
    qDebug() << "Client connected event should never be fired";
}

void Client::readyRead() {
    qDebug() << socket->readAll();
}

void Client::disconnected() {
    qDebug() << "Client disconnected";
}

void Client::taskResult(int n)
{
    
}
