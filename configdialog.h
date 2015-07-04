#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

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

    static QString versionUnknown;
    static QString versionError;
    static QString optionsVersionKey;
    static QString optionsTreeKey;
    static QString optionsTreeMinetest;
    static QString optionsTreeRogier5;

    static QStringList getMapperExecutables(void);
    static QString getDefaultMapperExecutable(void);
    static const QString defaultMapperExecutableName;
    static QStringList predefinedMapperLocations;
    static QString getMapperVersion(const QString &mapperBinary, QWidget *parent = NULL);
    static QMap<QString, QString> getMapperOptions(const QString &mapperBinary, QWidget *parent = NULL);

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

private:
    Ui::ConfigDialog *ui;
    QStringList executableList;
    ConfigSettings settings;
    MainWindow *application;

protected slots:

private slots:

    void on_browseMapper_clicked();

    void on_path_Minetestmapper_currentIndexChanged(int index);

    void on_CancelButton_clicked();
    void on_ApplyButton_clicked();
    void on_OKButton_clicked();
};

#endif // CONFIGDIALOG_H
