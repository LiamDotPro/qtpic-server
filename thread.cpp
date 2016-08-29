#include "thread.h"

Thread::Thread(qintptr threadId, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = threadId;
}

void Thread::run() {
    qDebug() << "thread running";

    socket = new QTcpSocket;

    if(!socket->setSocketDescriptor(this->socketDescriptor)) {
        //emit error(socket->error());
        qDebug() << "error sadface";
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << " connected";

    exec();
}

void Thread::readyRead() {
    QImage screenshot;
    QByteArray data;

    data = socket->readAll();

    if(screenshot.loadFromData(data)) {
        qDebug() << "it worked";

        now = QDateTime::currentDateTime();
        QString fileName = now.toString("'qtpush-'yy-MM-dd-hh-mm-ss'.png'");
        QFile file(fileName);

        file.open(QIODevice::WriteOnly);
        screenshot.save(&file, "PNG");
    }
}

void Thread::disconnected() {
    qDebug() << socketDescriptor << " disconnected";

    socket->deleteLater();
    exit(0);
}
