#ifndef SAVETASK_H
#define SAVETASK_H

#include <QRunnable>
#include <QDebug>
#include <QObject>

class SaveTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    SaveTask();
    
signals:
    void result(int n);    
    
protected:
    void run();
};

#endif // SAVETASK_H
