#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QMap>
#include <QString>
#include "minetestmapperexe.h"


namespace Ui {
class ConfigDialog;
}
class MainWindow;

struct ConfigSettings
{
    QString mapperPath;

    static QStringList getMapperExecutables(void);
    static QString getDefaultMapperExecutable(void);
    static const QString defaultMapperExecutableName;
    static QStringList predefinedMapperLocations;

private:
    struct InitStatics { InitStatics(void); };
    static const InitStatics initStatics;
    friend struct InitStatics;

    static void addMapperExecutablesToList(QStringList &existingList, QStringList &pathList);
};

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(const ConfigSettings &settings, MainWindow *app, QWidget *parent = 0);
    ~ConfigDialog();

    ConfigSettings getSettings() const;
    void setSettings(const ConfigSettings &value);

private:
    Ui::ConfigDialog *ui;
    QStringList executableList;
    ConfigSettings settings;
    MainWindow *application;

protected slots:

private slots:

    void on_browseMapper_clicked();

    void on_path_Minetestmapper_currentIndexChanged(int index);
    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // CONFIGDIALOG_H
