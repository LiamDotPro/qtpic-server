#ifndef SAVETASK_H
#define SAVETASK_H

#include <QRunnable>
#include <QDebug>
#include <QObject>

#include <QImage>
#include <QFile>
#include <QtSql>

class SaveTask : public QObject, public QRunnable
{
    Q_OBJECT
    
    QSqlDatabase db;
    QList<QByteArray> arrayList;
    QDir fileDirectory;
    QDateTime saveTime;
    QString fileName;
    QFile file;
    QByteArray img;
    QImage qimg;
    void saveFile();
    void saveToDB();
public:
    SaveTask();
    QByteArray data;
signals:
    void result(int n);    
    
protected:
    void run();
};

#endif // SAVETASK_H
