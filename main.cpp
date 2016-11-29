#include <QCoreApplication>
#include <QtSql>
#include "mserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("qtpdb");
    db.setUserName("root");
    db.setPassword("pw");
    
    MServer server;
    
    return a.exec();
}
