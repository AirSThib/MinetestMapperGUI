#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //set organization to MinetestMapperGui which is read by settings
    QCoreApplication::setOrganizationName("MinetestMapperGui");
    QCoreApplication::setApplicationName("MinetestMapperGui");
    MainWindow w;
    w.show();

    return a.exec();
}
