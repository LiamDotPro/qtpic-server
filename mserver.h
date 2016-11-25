#ifndef MSERVER_H
#define MSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThreadPool>
#include <QDebug>
#include "client.h"

class MServer : public QTcpServer
{

public:
    MServer(QObject *parent = 0);
protected:
    void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
};

#endif // MSERVER_H
