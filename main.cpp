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
    QApplication::setApplicationName("MinetestMapperGui");
#ifdef PORTABLE
	QApplication::setApplicationDisplayName("Minetest Mapper GUI (Portable)");
#else
	QApplication::setApplicationDisplayName("Minetest Mapper GUI");
#endif // PORTABLE
    QApplication::setApplicationVersion(GIT_VERSION);
    QApplication::setOrganizationName("MinetestMapperGui");


    // Setup the translators
	Translator t(QLocale::system());

    MainWindow w(&t);
    w.show();

    return QApplication::exec();
}
