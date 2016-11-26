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
public:
    SaveTask();
    QByteArray data;
signals:
    void result(int n);    
    
protected:
    void run();
};

#endif // SAVETASK_H
