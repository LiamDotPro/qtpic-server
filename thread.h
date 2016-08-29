#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QtWidgets/QWidget>
#include <QtWidgets/QtWidgets>

class Thread : public QThread
{
    Q_OBJECT

    QTcpSocket *socket;
    QBuffer *buffer;
    QDateTime now;
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
