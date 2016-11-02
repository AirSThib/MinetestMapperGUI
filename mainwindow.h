#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QProgressBar>
#include <QMessageBox>
#include <QRegExp>
#include <QTranslator>
#include <QColorDialog>
#include <QDate>
#include <QCloseEvent>
#include <QInputDialog>
#include <QActionGroup>
#include <QSettings>
#ifdef Q_OS_WIN
#include <QWinTaskbarProgress>
#include <QWinTaskbarButton>
#endif

#include "configdialog.h"
#include "colorstxtassistant.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Interaction with config dialog
    void closeConfigDialog(void);
    void updateConfigSettings(const ConfigSettings &newSettings);

public slots:
    void startColorsTxtAssistant();
protected:
    void closeEvent(QCloseEvent* event);
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*);

protected slots:
    // this slot is called by the language menu actions
    void slotLanguageChanged(QAction* action);
    void slotProfileChanged(QAction* action);

private slots:
    QString getOutputFileName();
    void on_button_generate_clicked();
    void readOutput();
    void readError();
    void mapperFinisched(int exit);
    void error(QProcess::ProcessError error);
    void wrapupMapper();
    void createProfilesMenu();
    void writeSettings();
    void writeProfile(QString strProfile);
    void readSettings();
    void readProfile(QString strProfile);
    bool migrateSettingsProfiles();

    void on_browseWorld_clicked();

    void on_saveImage_clicked();

    void on_browseHeightmapNodes_clicked();

    void on_browse_HeightmapColors_clicked();

    void on_browseColorsTxt_clicked();

    void on_actionAbout_MinetestMapperGUI_triggered();

    void on_actionAbout_MinetestMapper_triggered();

    void on_path_OutputImage_textChanged();

    void on_selectHeightmapColor_clicked();

    void on_button_cancel_clicked();

    void on_actionNew_Profile_triggered();

    void on_actionEdit_colors_txt_triggered();

    void on_actionEdit_heightmap_nodes_txt_triggered();

    void on_actionEdit_heightmap_colors_txt_triggered();

    void on_drawScaleLeft_toggled(bool checked);

    void on_drawScaleTop_toggled(bool checked);

    void on_drawHeightscale_toggled(bool checked);
    
    void on_tilecenter_clicked();

    void on_tileorigin_clicked();

    void on_actionPreferences_triggered();

private:
    bool portable;
    Ui::MainWindow *ui;
    QProgressBar *progressBar;
    QProcess *myProcess;
    QActionGroup *profileGroup;
    #ifdef Q_OS_WIN
    QWinTaskbarButton *taskbarButton;
    QWinTaskbarProgress *taskbarProgress;
    #endif
    ConfigSettings currentSettings;
    ConfigDialog *configDialog;

    void finishUiInitialisation(void);

    // loads a language by the given language shortcur (e.g. de, en)
    void loadLanguage(const QString& rLanguage);

    // creates the language menu dynamically from the content of m_langPath
    void createLanguageMenu(void);

    QTranslator m_translator; // contains the translations for this application
    QTranslator m_translatorQt; // contains the translations for qt
    QString m_currLang; // contains the currently loaded language
    QString m_langPath; // Path of language files. This is always fixed to /languages.
    QString currentProfile; //contains the name of current loaded profile
    QString pathAppData; // Path where the settings should be stored.
    QString pathProfiles; // path where the profiles should be stored.
    //QSettings profile;
    QSettings *settings;
};

#endif // MAINWINDOW_H
