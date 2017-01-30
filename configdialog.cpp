#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QStandardPaths>
#include <QProcessEnvironment>

#include "configdialog.h"
#include "ui_configdialog.h"
#include "mainwindow.h"

const QString ConfigSettings::defaultMapperExecutableName("minetestmapper");
QStringList ConfigSettings::predefinedMapperLocations;

ConfigSettings::InitStatics::InitStatics()
{
    #ifndef Q_OS_WIN
    ConfigSettings::predefinedMapperLocations << "/bin/" + defaultMapperExecutableName;
    ConfigSettings::predefinedMapperLocations << "/usr/bin/" + defaultMapperExecutableName;
    ConfigSettings::predefinedMapperLocations << "/usr/local/bin/" + defaultMapperExecutableName;
    #endif
}


ConfigDialog::ConfigDialog(const ConfigSettings &settings, MainWindow *app, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog),
    settings(settings),
    application(app)
{
    ui->setupUi(this);
    executableList = ConfigSettings::getMapperExecutables();
    QString standardExecutable;
    if (!executableList.empty())
        standardExecutable = executableList.at(0);
    if (standardExecutable != "")
        executableList.push_front(tr("---Automatic---  (Currently: %1)").arg(standardExecutable));
    else
        executableList.push_front(tr("---Automatic---  (Currently: NONE - Minetestmapper Not Found)"));
    ui->path_Minetestmapper->addItems(executableList);
    ui->path_Minetestmapper->setCurrentIndex(0);
    if (settings.mapperPath != "") {
        ui->path_Minetestmapper->setCurrentText(settings.mapperPath);
        if (ui->path_Minetestmapper->currentText() != settings.mapperPath) {
            // Unfortunately, adding it means that the saved path can be chosen again, even if it
            // does not exist. Can't avoid that, as we still want it to be the *current* value...
            executableList.push_back(settings.mapperPath);
            ui->path_Minetestmapper->addItem(settings.mapperPath);
            ui->path_Minetestmapper->setCurrentText(settings.mapperPath);
            // TODO: make the combobox editable (also solves the problem above)
        }
    }
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

ConfigSettings ConfigDialog::getSettings() const
{
    return settings;
}

void ConfigDialog::setSettings(const ConfigSettings &value)
{
    settings = value;
}

void ConfigDialog::on_browseMapper_clicked()
{
#ifdef Q_OS_WIN
    QString fileType = tr("Executable (*.exe)");
#else
    QString fileType;
#endif

    bool selectionSeemsOK;
    QString fileName;
    if (ui->path_Minetestmapper->currentIndex() != 0) {
        fileName = ui->path_Minetestmapper->currentText();
    }
    else if (ui->path_Minetestmapper->count() > 0) {
        fileName = ui->path_Minetestmapper->itemText(1);
    }
    else {
        #ifdef Q_OS_WIN
        fileName = QCoreApplication::applicationDirPath();
        #else
        fileName =  QDir::currentPath();
        #endif
    }
    do {
        fileName = QFileDialog::getOpenFileName(this, tr("Select Mapper Location"),
                                                        fileName,
                                                        fileType);
        if (fileName != "" && !(QFile(fileName).permissions() & QFileDevice::ExeUser)) {
            selectionSeemsOK = false;
            QMessageBox::critical(this, tr("Invalid minetestmapper executable"),
                                        tr("ERROR: The selected file is not executable"));
        }
        else {
            // TODO: verify if it is minetestmapper (?) -> invoke with --help ?
            selectionSeemsOK = true;
        }
    } while (!selectionSeemsOK);

    if(fileName != "") {
        settings.mapperPath = fileName;
        ui->path_Minetestmapper->setCurrentText(fileName);
        if (ui->path_Minetestmapper->currentText() != fileName) {
            executableList.push_back(fileName);
            ui->path_Minetestmapper->addItem(fileName);
            ui->path_Minetestmapper->setCurrentText(fileName);
        }
    }
}

QString ConfigSettings::getDefaultMapperExecutable(void)
{
    QStringList locations = getMapperExecutables();
    if (locations.empty()) return "";
    else return locations.at(0);
}

void ConfigSettings::addMapperExecutablesToList(QStringList &existingList, QStringList &pathList)
{
    QString prevLocation;
    for (; ! pathList.empty(); pathList.pop_front()) {
        QString location = QStandardPaths::findExecutable(ConfigSettings::defaultMapperExecutableName, pathList);
        if (location != "" && prevLocation != location) {
            prevLocation = location;
            int count = existingList.count();
            int i;
            for (i = 0; i < count; i++) {
                if (existingList[i] == location)
                    break;
            }
            if (i >= count)
                existingList << location;
        }
    }
}

QStringList ConfigSettings::getMapperExecutables(void)
{
    QStringList mapperLocations;
    QStringList moreLocations = ConfigSettings::predefinedMapperLocations;

    // On windows, check installation directory of minetestmappergui, & give precedence over anything else
    #ifdef Q_OS_WIN
    QString appDir = QCoreApplication::applicationDirPath();
    QString mapperFileName;

    mapperFileName = QStandardPaths::findExecutable(ConfigSettings::defaultMapperExecutableName, QStringList(appDir));
    if (mapperFileName != "")
        mapperLocations << mapperFileName;

    mapperFileName = QStandardPaths::findExecutable(ConfigSettings::defaultMapperExecutableName, QStringList(appDir + '/' + ConfigSettings::defaultMapperExecutableName));
    if (mapperFileName != "")
        mapperLocations << mapperFileName;

    mapperFileName = QStandardPaths::findExecutable(ConfigSettings::defaultMapperExecutableName, QStringList(appDir + "/mapper"));
    if (mapperFileName != "")
        mapperLocations << mapperFileName;
    #endif

    // Find all minetestmappers in PATH. Unfortunately, it seems that QT can't do this directly...
    QStringList path = QProcessEnvironment::systemEnvironment().value("PATH").split(":");
    addMapperExecutablesToList(mapperLocations, path);

    // Find all minetestmappers in QStandardPaths::ApplicationsLocation, add if not already added
    QStringList appLocations = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
    addMapperExecutablesToList(mapperLocations, appLocations);

    // Add locations from moreLocations that were not already added
    addMapperExecutablesToList(mapperLocations, moreLocations);

    return mapperLocations;
}


void ConfigDialog::on_path_Minetestmapper_currentIndexChanged(int index)
{
    if (index == 0)
        settings.mapperPath = "";
    else
        settings.mapperPath = ui->path_Minetestmapper->currentText();
}



void ConfigDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton b = ui->buttonBox->standardButton(button);
    if(b== QDialogButtonBox::RestoreDefaults)
    {
        ui->path_Minetestmapper->setCurrentIndex(0);
    }
}
