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


    // Init commandline parser
    QCommandLineParser parser;
    parser.setApplicationDescription("This program provides a graphical user interface for minetestmapper. \n"
                                     "If you are looking for the command line interface of minetesmapper please execute minetestmapper directly.");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption startPortableOption(QStringList() << "p" << "portable",
                                           "Starts in portable mode which reads and writes settings and profiles relative to current directory");
    parser.addOption(startPortableOption);

    parser.process(a.arguments());

    bool portable = parser.isSet(startPortableOption);

    MainWindow w(portable, &t);
    w.show();

    return a.exec();
}
