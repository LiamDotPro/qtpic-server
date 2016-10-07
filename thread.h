#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QtWidgets/QWidget>
#include <QtWidgets/QtWidgets>
#include <QtSql>
#include <string.h>

class Thread : public QThread
{
    Q_OBJECT

    QTcpSocket *socket;
    QBuffer *buffer;
    QDateTime now;
    int socketDescriptor;
    QByteArray data;
    QDataStream in;

    void handleImage();
public:
    explicit Thread(qintptr threadId,QObject *parent = 0);
    void run();

signals:

public slots:
    void readyRead();
    void disconnected();

};

#endif // THREAD_H
