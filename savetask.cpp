#include "savetask.h"

SaveTask::SaveTask()
{
    
}

void SaveTask::run()
{
    qDebug() << "start";
    
    QList<QByteArray> qlba = data.split('|');
    
    for(int i = 0; i < qlba.length(); i++) {
            qDebug() << qlba[i];
    }
    
    //QSqlDatabase db = QSqlDatabase::database();
    /*
    if(db.open()) {
        QSqlQuery login;
        QString qString = "SELECT * FROM `users` WHERE name = " + qlba[3];
        if(login.exec())
    } else {
        qDebug() << "Error opening db";
    }*/
    
    qDebug() << "complete";
    emit result(0);
}
