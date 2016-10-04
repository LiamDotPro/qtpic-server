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

    QString qs (data);
    QStringList qsl = qs.split(',');
    if(qsl[0] == "login") {
        qDebug() << "login data";
        if(qsl[1] == "testy" && qsl[2] == "password") {
            qDebug() << "logged in";
        }
    }


    QString temp = QString::number(std::rand());

    if(screenshot.loadFromData(data)) {

        QSqlDatabase db = QSqlDatabase::database();
        if(db.open ()) {
            qDebug() << "db connected";

            QSqlQuery qqr;
            qqr.prepare("INSERT INTO `pics` (filename, data) "
                        "VALUES (:fn, :dat)");
            qqr.bindValue(":fn", temp);
            qqr.bindValue(":dat", data.toBase64());
            if(qqr.exec()) {
                qDebug() << "it worked";
            } else {
                qDebug() << qqr.lastError().text() << ", " << qqr.lastError().number();
            }

            db.close();
        } else {
            qDebug() << db.lastError();
        }



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
