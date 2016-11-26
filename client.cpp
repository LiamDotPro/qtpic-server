#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(2);
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
    qDebug() << "Client connected event that should never be fired";
}

void Client::readyRead() {
    imgData += socket->readAll();
}

void Client::disconnected() {
    qDebug() << "Client disconnected";
    SaveTask *task = new SaveTask();
    task->data = imgData;
    task->setAutoDelete(true);
    connect(task, SIGNAL(result(int)), this, SLOT(taskResult(int)),Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(task);
}

void Client::taskResult(int n){
    qDebug() << "saved";
    /*
    QByteArray b;
    b.append("\r\nresult: ");
    b.append(QString::number(n));
    socket->write(b);
    socket->flush();*/
}
