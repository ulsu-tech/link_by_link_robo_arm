#include "cd.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CentralDialog w;
    w.show();
    w.startScan();
    return a.exec();
}
