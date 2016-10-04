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

    Server server;
    server.start();

    return a.exec();
}

