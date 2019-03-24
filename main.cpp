#include "mainwindow.h"
#include "translator.h"
#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QCommandLineParser>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("MinetestMapperGui");
    a.setApplicationDisplayName("Minetest Mapper GUI");
    a.setApplicationVersion(GIT_VERSION);
    a.setOrganizationName("MinetestMapperGui");


    // Setup the translators
	Translator t(QLocale::system());

    MainWindow w(&t);
    w.show();

    return a.exec();
}
