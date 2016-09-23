#include <QCoreApplication>
#include <server.h>
#include <QtSql>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase ("QMYSQL");
    db.setHostName ("127.0.0.1");
    db.setDatabaseName ("qtpdb");
    db.setUserName ("root");
    /*
    if(db.open ()) {
        qDebug() << "db connected";

        QSqlQuery qqr;
        if(qqr.exec("SELECT * FROM `users` ")) {
            while(qqr.next()) {
                qDebug() << qqr.value(1).toString();
            }
        } else {
            qDebug() << qqr.lastError().text() << ", " << qqr.lastError().number();
        }

        db.close();
    } else {
        qDebug() << db.lastError();
    }
    */
    Server server;
    server.start();

    return a.exec();
}
