#include <QCoreApplication>
#include "mserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    MServer server;
    
    return a.exec();
}
