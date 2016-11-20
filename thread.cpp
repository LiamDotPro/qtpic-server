#include "thread.h"

Thread::Thread(qintptr threadId, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = threadId;
}

void Thread::run() {
    qDebug() << "thread running";

    socket = new QTcpSocket;
    in.setDevice(socket);

    if(!socket->setSocketDescriptor(this->socketDescriptor)) {
        //emit error(socket->error());
        qDebug() << "error sadface";
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << " connected";

    exec();

    handleImage();
}

void Thread::readyRead() {

    data += socket->readAll();

    return;
}

void Thread::handleImage() {
    qDebug() << "size: " << data.size();

    QString alldata (data);
    QStringList stringlist = alldata.split('|');
    QList<QByteArray> qlba = data.split('|');
    
    for(int i = 0; i < qlba.length(); i++) {
        qDebug() << i;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if(db.open ()) {
        //Get right user
        QSqlQuery usrChk;
        if(usrChk.exec("SELECT * FROM `users`")) {
            while(usrChk.next()) {
                qDebug() << "0: " << usrChk.value(0);
                qDebug() << "1: " << usrChk.value(1);
                qDebug() << "sl1: " << stringlist[1];
                qDebug() << "sl2: " << stringlist[2];
                
                //login
                if(usrChk.value(0).toString() == stringlist[1]
                        && usrChk.value(1).toString() == stringlist[2]) {
                    //save image
                    QDir dir;
                    now = QDateTime::currentDateTime();
                    QString fileName = now.toString("'qtpush-'yy-MM-dd-hh-mm-ss'.png'");
                    dir.mkdir(QCoreApplication::applicationDirPath() + "/img/" + stringlist[1]);
                    fileName = QCoreApplication::applicationDirPath() + "/img/" + stringlist[1] + "/" + fileName;
                    QFile file(fileName);
                    file.open(QIODevice::WriteOnly);
                    QByteArray ba_img = QByteArray::fromBase64(qlba[0]);
                    QImage img = QImage::fromData(ba_img);
                    img.save(&file, "PNG");
                    

                    QSqlQuery qqr;
                    qqr.prepare("INSERT INTO `pics` (username, filename, data) "
                                "VALUES (:un, :fn, :dat)");
                    qqr.bindValue(":un", usrChk.value(0));
                    qqr.bindValue(":fn", fileName);
                    qqr.bindValue(":dat", "img/"+stringlist[1]+"/"+fileName);
                    if(qqr.exec()) {
                        qDebug() << "New image saved: " << usrChk.value(0)
                                 << ", " << fileName;
                    } else {
                        qDebug() << qqr.lastError().text() << ", " << qqr.lastError().number();
                    }

                    db.close();
                    break;
                } else {
                    qDebug() << db.lastError().text() << ", " << db.lastError().number();
                }
            }
        }
    }
}

void Thread::disconnected() {
    qDebug() << socketDescriptor << " disconnected";

    socket->deleteLater();
    exit(0);
}
