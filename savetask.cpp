#include "savetask.h"

SaveTask::SaveTask()
{
    db = QSqlDatabase::database();
    saveTime = QDateTime::currentDateTime();
    fileName = saveTime.toString("'qtpush-'yy-MM-dd-hh-mm-ss'.png'");
}

void SaveTask::run()
{
    qDebug() << "start";
    
    arrayList = data.split('|');
    
    /*for(int i = 0; i < arrayList.length(); i++) {
            qDebug() << "array" << i << ": " << arrayList[i];
    }*/
    
    if(db.open()) {
        QSqlQuery login;
        QString qString = "SELECT * FROM `users` WHERE `name` = '" + arrayList[1] + "'" +
                "AND `password` = '" + arrayList[2] + "'";
        if(login.exec(qString)) {
            if(login.first()) {
                qDebug() << login.value(0).toString() << " logged in";
                
                saveFile();
                
                saveToDB();
                
                db.close();
            }
        } else {
            qDebug() << login.lastError().text();
        }
    } else {
        qDebug() << db.lastError().text();
    }
    
    qDebug() << "complete";
    emit result(0);
}

void SaveTask::saveFile() {
    fileDirectory.mkdir(QCoreApplication::applicationDirPath() + "/img/");
    fileDirectory.mkdir(QCoreApplication::applicationDirPath() + "/img/" + arrayList[1]);
    fileName = QCoreApplication::applicationDirPath() + "/img/" + arrayList[1] + "/" + fileName;
    
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly);
    img = QByteArray::fromBase64(arrayList[0]);
    qimg = QImage::fromData(img);
    qimg.save(&file, "PNG");
}

void SaveTask::saveToDB() {
    QSqlQuery store;
    fileName = saveTime.toString("'qtpush-'yy-MM-dd-hh-mm-ss'.png'");
    store.prepare("INSERT INTO `pics` (filename, path, username) "
                  "VALUES (:f, :p, :u)");
    store.bindValue(":u", arrayList[1]);
    store.bindValue(":f", fileName);
    store.bindValue(":p", "img/" + arrayList[1] + "/" + fileName);
    if(store.exec()) {
        
    } else {
        qDebug() << store.lastError().text();
    }
}
