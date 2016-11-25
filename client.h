#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>

class Client : public QObject
{
    Q_OBJECT
    
    QTcpSocket *socket;
public:
    explicit Client(QObject *parent = 0);
    void setSocket(int handle);
    
signals:
    
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void taskResult(int n);
};

#endif // CLIENT_H
