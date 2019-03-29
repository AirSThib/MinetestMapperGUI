#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "minetestmapperexe.h"

#include <QDialog>
#include <QMap>
#include <QString>

namespace Ui {
class ConfigDialog;
}
class MainWindow;

struct ConfigSettings
{
    QString mapperPath;

    static QStringList getMapperExecutables();
    static QString getDefaultMapperExecutable();
    static const QString defaultMapperExecutableName;
    static QStringList predefinedMapperLocations;

private:
    struct InitStatics { InitStatics(); };
    static const InitStatics initStatics;
    friend struct InitStatics;

    static void addMapperExecutablesToList(QStringList &existingList, QStringList &pathList);
};

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(const ConfigSettings &settings, MainWindow *app, QWidget *parent = nullptr);
    ~ConfigDialog() override;

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
