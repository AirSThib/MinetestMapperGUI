#include "mainwindow.h"
#include <QCoreApplication>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("MinetestMapperGui");
    a.setApplicationDisplayName("Minetest Mapper GUI");
    a.setApplicationVersion(GIT_VERSION);
    a.setOrganizationName("MinetestMapperGui");

    MainWindow w;
    w.show();

    return a.exec();
}
