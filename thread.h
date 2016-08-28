#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class Thread : public QThread
{
    Q_OBJECT

    QTcpSocket *socket;
    int socketDescriptor;

public:
    explicit Thread(qintptr threadId,QObject *parent = 0);
    void run();

signals:

public slots:
    void readyRead();
    void disconnected();

};

#endif // THREAD_H
