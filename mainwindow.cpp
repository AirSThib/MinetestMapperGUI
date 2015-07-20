#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qprocess.h>
#include <qstringlist.h>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QDesktopServices>
#include <QCompleter>
#include <QDirModel>

#if defined(Q_OS_WIN)
static const QString qSettingsOrganisation("addi");
static const QString qSettingsApplicationPrefix("Minetestmapper_");
#else
static const QString qSettingsOrganisation("minetestmapper");
static const QString qSettingsApplicationPrefix("");
#endif
static QMap<int, QString> geometryGranularitySymbolic;
static QMap<QString, int> geometryGranularityNumeric;
static QMap<int, QString> geometrySizeModeSymbolic;
static QMap<QString, int> geometrySizeModeNumeric;
struct InitStatics { InitStatics(void); };
static const InitStatics initStatics;

InitStatics::InitStatics(void)
{
    int n = -1;
    geometryGranularitySymbolic[n++] = "unspecified";
    geometryGranularitySymbolic[n++] = "pixel";
    geometryGranularitySymbolic[n++] = "block";
    for (int i = -1; i < n; i++)
        geometryGranularityNumeric[geometryGranularitySymbolic[i]] = i;

    n = -1;
    geometrySizeModeSymbolic[n++] = "auto";
    geometrySizeModeSymbolic[n++] = "auto";
    geometrySizeModeSymbolic[n++] = "fixed";
    geometrySizeModeSymbolic[n++] = "shrink";
    for (int i = -1; i < n; i++)
        geometrySizeModeNumeric[geometrySizeModeSymbolic[i]] = i;
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    #ifndef Q_OS_WIN
    if (!migrateSettingsProfiles())
        exit(EXIT_FAILURE);
    #endif
    ui->setupUi(this);
    finishUiInitialisation();
    readSettings();
    readProfile(currentProfile);
    progressBar = new QProgressBar(ui->statusBar);
    progressBar->setAlignment(Qt::AlignRight);
    progressBar->setMaximumSize(180, 19);
    ui->statusBar->addPermanentWidget(progressBar);
    //progressBar->setValue(0);
    progressBar->setMaximum(100);
    progressBar->setMinimum(0);
    progressBar->hide();
    connect(ui->actionAbout_QT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    createLanguageMenu();
    createProfilesMenu();

    QCompleter *completer = new QCompleter(this);
    QDirModel *model =new QDirModel(completer);
    model->setFilter(QDir::Dirs|QDir::NoDotAndDotDot|QDir::Drives);
    completer->setModel(model);
    ui->path_World->setCompleter(completer);
}

void MainWindow::finishUiInitialisation(void)
{
    ui->geometrymode_granularity_group->setId(ui->geometrymode_pixel, geometryGranularityNumeric["pixel"]);
    ui->geometrymode_granularity_group->setId(ui->geometrymode_block, geometryGranularityNumeric["block"]);

    ui->geometrymode_size_group->setId(ui->geometrymode_auto, geometrySizeModeNumeric["auto"]);
    ui->geometrymode_size_group->setId(ui->geometrymode_fixed, geometrySizeModeNumeric["fixed"]);
    ui->geometrymode_size_group->setId(ui->geometrymode_shrink, geometrySizeModeNumeric["shrink"]);
}

// we create the language menu entries dynamically, dependent on the existing translations.
void MainWindow::createLanguageMenu(void)
{
    QActionGroup* langGroup = new QActionGroup(ui->menuLanguage);
    langGroup->setExclusive(true);

    connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

    // format systems language
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"

    m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/languages");
    qDebug()<<"Lang path "<< m_langPath;
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("gui_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i]; // "gui_de.qm"
        locale.truncate(locale.lastIndexOf('.')); // "gui_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());
        QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));

        QAction *action = new QAction(ico, lang, this);
        action->setCheckable(true);
        action->setData(locale);

        ui->menuLanguage->addAction(action);
        langGroup->addAction(action);

        // set default translators and language checked
        if (defaultLocale == locale)
        {
            action->setChecked(true);
            loadLanguage(locale);
        }
    }
}

// Called every time, when a menu entry of the language menu is called
void MainWindow::slotLanguageChanged(QAction* action)
{
    if(0 != action) {
        // load the language dependant on the action content
        loadLanguage(action->data().toString());
        ui->menuLanguage->setIcon(action->icon());
    }
}

void switchTranslator(QTranslator& translator, const QString& filename)
{
    // remove the old translator
    qApp->removeTranslator(&translator);
    QString m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/languages/");
    qDebug()<<"Trying to load language "<< m_langPath+filename;
    qDebug()<<translator.load(m_langPath+filename);
    // load the new translator
    if(translator.load(m_langPath+filename))
        qApp->installTranslator(&translator);
}

void MainWindow::loadLanguage(const QString& rLanguage)
{
    if(m_currLang != rLanguage) {
        m_currLang = rLanguage;
        QLocale locale = QLocale(m_currLang);
        QLocale::setDefault(locale);
        QString languageName = QLocale::languageToString(locale.language());
        switchTranslator(m_translator, QString("gui_%1.qm").arg(rLanguage));
        switchTranslator(m_translatorQt, QString("qtbase_%1.qm").arg(rLanguage));
        ui->statusBar->showMessage(tr("Current Language changed to %1").arg(languageName),3000);
    }
}
void MainWindow::changeEvent(QEvent* event)
{
 if(0 != event) {
  switch(event->type()) {
   // this event is send if a translator is loaded
   case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;

   // this event is send, if the system, language changes
   case QEvent::LocaleChange:
   {
    QString locale = QLocale::system().name();
    locale.truncate(locale.lastIndexOf('_'));
    loadLanguage(locale);
   }
   break;

   // Ignore other events
   default:
     break;
  }
 }
 QMainWindow::changeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_generate_clicked()
{
    QDir worldPath = QDir(ui->path_World->text());
    if(!worldPath.exists()||worldPath.path()=="."||worldPath.path()=="/"){
        QMessageBox::critical(this, tr("no input world selected"),
                 tr("ERROR: No MinetestWorld selected<br><br>"
                    "please select a world"));
        return;
    }
    QString imgName = getOutputFileName();
    if(imgName.isEmpty()){
        QMessageBox::critical(this, tr("no output image selected"),
                 tr("ERROR: No output image selected<br><br>"
                    "please select a output image"));
        return;
    }
    if(QFile::exists(imgName)){
        int ret = QMessageBox::question(this, tr("the Image File does already exist"),
                 tr("The File <i>%1</i> does already exist. <br><br>"
                    "Do you want to overwrite?")
                              .arg(imgName));
        if(ret != QMessageBox::Yes) return;
    }
    QDir imgPath = QFileInfo(imgName).absoluteDir();
    if(!imgPath.exists())
    {
        qDebug()<<"Ordner Existiert nicht";
        int ret = QMessageBox::question(this, tr("the directory does not exist"),
                 tr("The directory <i>%1</i> does not exist. <br><br>"
                    "Should it be created?")
                              .arg(imgPath.absolutePath()));
        if(ret == QMessageBox::Yes)
        {
            imgPath.mkpath(imgPath.absolutePath());
        }
        else return;

    }

    QString appDir =QCoreApplication::applicationDirPath();
    qDebug()<<appDir;
    QDir dir = QDir(appDir);

    QStringList arguments;
    arguments           <<"-i" << ui->path_World->text()//"D:\\Programme\\minetest\\worlds\\server_minetest.king-arthur.eu_30000"
                        <<"--output" << imgName //"D:\\Users\\Adrian\\Desktop\\test2.png"
                        <<"--colors" <<  dir.absoluteFilePath(ui->path_ColorsTxt->text()) //appDir+"\\colors\\colors.txt"
                        <<"--progress" //<< "--verbose-search-colors=2" //<<"--verbose"
                        <<"--drawalpha="+ui->drawAlpha->currentText()
                        <<"--bgcolor" << ui->bgcolor->text()
                        <<"--blockcolor" << ui->blockcolor->text()
                        <<"--scalecolor" << ui->scalecolor->text()
                        <<"--origincolor" << ui->origincolor->text()
                        <<"--playercolor" << ui->playercolor->text()
                        <<"--tilebordercolor" << ui->tilebordercolor->text();
    if(ui->backend->currentIndex() !=0){
        arguments <<"--backend" << ui->backend->currentText();
    }
    if(ui->geometry->getFormat() != Geometry::FormatNone && ui->geometry->getGeometry() !=""){
        arguments <<"--geometry" << ui->geometry->getGeometry().trimmed();
    }

    if(ui->scalefactor->currentIndex() !=0){
        arguments <<"--scalefactor" << ui->scalefactor->currentText();
    }
    if(ui->checkBox_maxY->isChecked()){
        arguments <<"--max-y" << ui->maxY->cleanText();
    }
    if(ui->checkBox_minY->isChecked()){
        arguments <<"--min-y" << ui->minY->cleanText();
    }

    if(ui->geometrymode_pixel->isChecked()||ui->geometrymode_block->isChecked()||ui->geometrymode_shrink->isChecked()||ui->geometrymode_fixed->isChecked()){
        arguments <<"--geometrymode";
    if(ui->geometrymode_pixel->isChecked()){
        arguments <<"pixel";
    }
    if(ui->geometrymode_block->isChecked()){
        arguments <<"block";
    }
    if(ui->geometrymode_shrink->isChecked()){
        arguments <<"shrink";
    }
    if(ui->geometrymode_fixed->isChecked()){
        arguments <<"fixed";
    }

    }

    if(ui->drawScaleLeft->isChecked() && ui->drawScaleTop->isChecked()){
        arguments <<"--drawscale=left,top";
    }
    else if(ui->drawScaleLeft->isChecked()){
        arguments <<"--drawscale=left";
    }
    else if(ui->drawScaleTop->isChecked()){
        arguments <<"--drawscale=top";
    }

    if(ui->drawOrigin->isChecked()){
        arguments <<"--draworigin";
    }
    if(ui->drawPlayers->isChecked()){
        arguments <<"--drawplayers";
    }
    if(ui->drawAir->isChecked()){
        arguments <<"--drawair";
    }
    if(ui->noShading->isChecked()){
        arguments <<"--noshading";
    }

    //Heightmap Tab
    if(ui->generateHeightmap->isChecked()){
        if(ui->heightmapColor->isChecked()){
            arguments <<"--heightmap="+ui->colorHeightmap->text();
        }
        else{
            arguments <<"--heightmap";
        }


        arguments <<"--heightmap-nodes" << ui->path_HeightmapNodes->text()
                  <<"--heightmap-colors" << ui->path_HeightmapColors->text()
                  <<"--heightmap-yscale" << ui->heightmapYscale->cleanText().replace(',','.')
                  <<"--height-level-0" << ui->heightLevelNull->cleanText();
        qDebug() << ui->heightLevelNull->cleanText();
        if(ui->drawHeightscale->isChecked()){
            arguments <<"--drawheightscale";
        }
    }

    //Tiles Tab
    if(ui->tiles->isChecked()){
        arguments <<"--tiles";
        if(ui->tiles_sizeAndBorder->isChecked()){
            arguments <<ui->tilesize->cleanText()+"+"+ui->tileborder->cleanText();
        }
        else if(ui->tile_block->isChecked()){
            arguments <<"block";
        }
        else if(ui->tile_chunk->isChecked()){
            arguments <<"chunk";
        }

        if(ui->tileorigin->isChecked()){
            arguments <<"--tileorigin";
        }
        else{
            arguments <<"--tilecenter";
        }
        if(ui->tiles_coordinates->isChecked()){
            arguments << ui->tiles_coordinateX->cleanText() +","+ ui->tiles_coordinateY->cleanText();
        }
        else if(ui->tiles_world) arguments<<"world";
        else {
            arguments<<"map";
        }
    }

    ui->button_generate->setDisabled(true);

    if(ui->actionExpert_Mode->isChecked()){
        bool ok;
        QString parameters = QInputDialog::getMultiLineText(this,
                                                            tr("Expert Mode"),//title
                                                            tr("MinetestMapper will be executed using this arguments. \n"
                                                               "The arguments can be removed, modified, or new arguments can be added."),//label
                                                            arguments.join("\n"),//text
                                                            &ok,0);
        if (ok) arguments = parameters.split("\n");
        else {
            ui->button_generate->setDisabled(false);
            return;
        }
    }

    myProcess = new QProcess(this);
    myProcess->setWorkingDirectory(appDir);
    QString program = appDir+"/mapper/minetestmapper";
    myProcess->setProgram(program);
    qDebug()<<imgName;
    myProcess->setArguments(arguments);

    qDebug()<<myProcess->arguments();
    progressBar->show();
    progressBar->setMaximum(100);
    ui->button_cancel->setDisabled(false);
    connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(myProcess, SIGNAL(readyReadStandardError()), this, SLOT(readError()));//error stream contains unknown nodes
    connect(myProcess, SIGNAL(finished(int)), this, SLOT(mapperFinisched(int)));
    connect(myProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(error(QProcess::ProcessError)));
    ui->standardOutput->append("Starting "+myProcess->program()+" "+arguments.join(" "));
    myProcess->start();
    #ifdef Q_OS_WIN
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(this->windowHandle());
    taskbarButton->setOverlayIcon(QIcon(":/save"));

    taskbarProgress = taskbarButton->progress();
    taskbarProgress->show();
    #endif
}

void MainWindow::on_button_cancel_clicked()
{
    myProcess->kill();
    #ifdef Q_OS_WIN
    taskbarProgress->stop();
    #endif
}

void MainWindow::readOutput()
{
    QByteArray outData = myProcess->readAllStandardOutput();
    QString out = QString(outData).trimmed();
    if(out != "") {
        QRegExp rx("([0-9]{1,3})(\\%)");
        if(rx.indexIn(out)!=-1){
            QString percent = rx.cap(1); // percent == number
            progressBar->setValue(percent.toInt());
            #ifdef Q_OS_WIN
            taskbarProgress->setValue(percent.toInt());
            #endif
        }


        ui->statusBar->showMessage(out);
        ui->standardOutput->append(out);
    }
}
void MainWindow::readError()
{
    QByteArray outData = myProcess->readAllStandardError();
    QString out = QString(outData).trimmed();
    if(out != "") {
        ui->statusBar->showMessage(out);
        ui->standardOutput->append("<span style='color:red; white-space: pre;'>"+out.toHtmlEscaped()+"</span>");
    }
}

QString MainWindow::getOutputFileName()
{
    QString worldPath = ui->path_World->text();
    QString worldName = QDir(worldPath).dirName();
    QString imgName = ui->path_OutputImage->text()
            .replace("<date>",
                     QDate::currentDate().toString(Qt::SystemLocaleShortDate))
            .replace("<longdate>",
                     QDate::currentDate().toString(Qt::SystemLocaleLongDate))
            .replace("<isodate>",
                     QDate::currentDate().toString(Qt::ISODate))
            .replace("<world>",
                     worldName)
            .replace("<time>",
                     QTime::currentTime().toString("hh.mm.ss"));
    return imgName;
}

void MainWindow::mapperFinisched(int exit)
{
    //ui->statusBar->showMessage("Ready");
    if(exit ==0){//mapper finished successfull
        ui->statusBar->showMessage(tr("Finisched :)"),3000);
        if(ui->actionOpen_map_after_creation->isChecked()){
            QString imgName = getOutputFileName();
            QDesktopServices::openUrl(QUrl(imgName));
        }

    }
    else if(exit==62097){
        ui->statusBar->showMessage(tr("minetestmapper terminated"));
    }
    else{//something was wrong
        QMessageBox::critical(this, tr("Minetest Mapper failed"),
                 tr("<h1>ERROR</h1> <h2>minetestmapper failed</h2>"
                    "Exit code: <i>%1</i> <br>"
                    "Status of MinetestMapper: <pre>%2</pre><br>"
                    "<br>"
                    "Please fix the error and try again ")
                              .arg(exit)
                              .arg(ui->statusBar->currentMessage()));
    }
    wrapupMapper();
}

void MainWindow::error(QProcess::ProcessError error)
{
    qDebug() <<"Error starting MinetestMapper:"<<error
            <<"Error code: "<<myProcess->error()
           <<"Error string: "<<myProcess->errorString();
    QMessageBox::critical(this, tr("Minetest Mapper failed"),
             tr("<h1>ERROR</h1> <h2>minetestmapper failed</h2>"
                "Error code: <i>%1</i> <br>"
                "Error Message: <pre>%2</pre><br>")
                          .arg(error)
                          .arg(myProcess->errorString()));
    wrapupMapper();
}

void MainWindow::wrapupMapper()
{
    ui->button_generate->setDisabled(false);
    ui->button_cancel->setDisabled(true);
    progressBar->setValue(0);
    progressBar->hide();
    #ifdef Q_OS_WIN
    taskbarButton->clearOverlayIcon();
    taskbarProgress->hide();
    #endif
}

bool MainWindow::migrateSettingsProfiles()
{
    QSettings oldSettings("addi", "Minetestmapper");
    QFile oldSettingsFile(oldSettings.fileName());
    if (!oldSettingsFile.exists()) return true;
    QSettings newSettings(qSettingsOrganisation, "Minetestmapper");
    QFile newSettingsFile(newSettings.fileName());

    QDir oldDir(oldSettings.fileName().section('/', 0, -2));
    qDebug()<<"Old settings / profile directory "<< oldDir.absolutePath();
    QDir newDir(newSettings.fileName().section('/', 0, -2));
    qDebug()<<"New settings / profile directory "<< newDir.absolutePath();

    if (newSettingsFile.exists()) {
        int ret = QMessageBox::question(this, tr("Migrating settings"),
                tr("<h1>WARNING</h1> <h2>Migrating settings: both old and new settings found</h2>"
                        "old settings directory: <i>%1</i><br>"
                        "new settings directory: <i>%2</i><br>"
                        "<h2>Migrate old settings anyway ?</h2>This overwrites the new settings, and some or all new profiles<br><br>"
                        "Delete the old settings files (<i>%1/Minetestmapper*</i>) to avoid this message.")
                        .arg(oldSettingsFile.fileName()).arg(newSettingsFile.fileName()));
        if(ret != QMessageBox::Yes) return true;
    }


    QString failureCause;
    if (!newDir.exists()) {
        qDebug()<<"Create new settings directory " << newDir.absolutePath();
        if (!QDir().mkpath(newDir.absolutePath())) {
            QMessageBox::critical(this, tr("Failed to migrate settings"),
                     tr("<h1>ERROR</h1> <h2>Failed to migrate settings</h2>"
                        "Reason: failed to create new settings directory <i>%1</i>")
                                  .arg(newDir.absolutePath()));
            return false;
        }
    }

    QStringList oldFileNames = oldDir.entryList(QStringList("Minetestmapper_*"));
    // make sure main config file is last.
    oldFileNames.append(oldSettingsFile.fileName().section('/', -1, -1));
    qDebug() << "Migrate settings files: " << oldFileNames;
    for (int i = 0; i < oldFileNames.size(); ++i) {
        QString newFileName = oldFileNames[i];
        newFileName.replace("Minetestmapper_","");
        QFile oldFile(oldDir.absoluteFilePath(oldFileNames[i]));
        QFile newFile(newDir.absoluteFilePath(newFileName));
        if (newFile.exists()) {
            qDebug()<<"Remove existing settings file " << newFile.fileName();
            if (!newFile.remove()) {
                QMessageBox::critical(this, tr("Failed to migrate settings"),
                         tr("<h1>ERROR</h1> <h2>Failed to migrate settings</h2>"
                            "Reason: failed to remove existing file <i>%1</i>")
                                      .arg(newFile.fileName()));
                return false;
            }
        }
        qDebug()<<"Rename settings file " << oldFile.fileName() << " to " << newFile.fileName();
        if (!QDir().rename(oldFile.fileName(), newFile.fileName())) {
            QMessageBox::critical(this, tr("Failed to migrate settings"),
                     tr("<h1>ERROR</h1> <h2>Failed to migrate settings</h2>"
                        "Reason: failed to move file <i>%1</i> to <i>%2</i>")
                                  .arg(oldFile.fileName())
                                  .arg(newFile.fileName()));
            return false;
        }
        if (oldFile.exists()) {
            qDebug()<<"Remove old settings file " << oldFile.fileName();
            if (!oldFile.remove()) {
                QMessageBox::warning(this, tr("Failed to remove old settings"),
                         tr("<h1>WARNING</h1> <h2>Failed to remove old settings</h2>"
                            "Reason: failed to remove file <i>%1</i>")
                                      .arg(oldFile.fileName()));
            }
        }
    }

    if (oldDir.count() == 2) {
        qDebug()<<"Remove old directory" << oldDir.absolutePath();
        if (!oldDir.removeRecursively()) {
            QMessageBox::warning(this, tr("Failed to remove old settings directory"),
                     tr("<h1>WARNING</h1> <h2>Failed to remove old settings directory</h2>"
                        "Reason: failed to remove directory <i>%1</i>")
                                  .arg(oldDir.absolutePath()));
        }
    }
    return true;
}

void MainWindow::createProfilesMenu(){
    profileGroup = new QActionGroup(ui->menuChoose_profile);
    profileGroup->setExclusive(true);

    connect(profileGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotProfileChanged(QAction *)));

    QSettings settings(QSettings::IniFormat,QSettings::UserScope,qSettingsOrganisation, qSettingsApplicationPrefix+"profile_default");
    QString profilePath = settings.fileName();
    qDebug()<<"Profile path "<< profilePath;
    QDir dir(profilePath);
    dir.cdUp();
    QStringList fileNames = dir.entryList(QStringList("profile_*.ini"));
    qDebug()<<fileNames;
    if(fileNames.size()==0)fileNames.append("profile_default.ini");
    for (int i = 0; i < fileNames.size(); ++i) {
        // get locale extracted by filename
        QString profile;
        profile = fileNames[i]; // "gui_de.qm"
        profile.truncate(profile.lastIndexOf('.')); // "gui_de"
        profile.remove(0, profile.lastIndexOf('_') + 1); // "de"

       // QString lang = QLocale::languageToString(QLocale(locale).language());
       // QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));

        QAction *action = new QAction(profile, this);
        action->setCheckable(true);
        action->setData(profile);

        ui->menuChoose_profile->addAction(action);
        profileGroup->addAction(action);

        // set default translators and language checked
        if (currentProfile == profile)
        {
            action->setChecked(true);
        }
    }

}

// Called every time, when a menu entry of the profile menu is called
void MainWindow::slotProfileChanged(QAction* action)
{
    if(action != 0) {
        //writeProfile(currentProfile);
        currentProfile = action->data().toString();
        readProfile(currentProfile);
        // load the language dependant on the action content
        //ui->menuLanguage->setIcon(action->icon());
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(qSettingsOrganisation, "Minetestmapper");

    settings.beginGroup("MainWindow");
    if(isMaximized()){
        settings.setValue("maximized", isMaximized());
    }
    else{
        settings.setValue("maximized", isMaximized());
        settings.setValue("size", size());
        settings.setValue("pos", pos());
    }
    settings.setValue("help", ui->actionHelp->isChecked());
    settings.setValue("profile", currentProfile);
    settings.setValue("expertMode",ui->actionExpert_Mode->isChecked());
    settings.setValue("openMap",ui->actionOpen_map_after_creation->isChecked());
    settings.endGroup();
}

void MainWindow::writeProfile(QString profile)
{
    QSettings settings(QSettings::IniFormat,QSettings::UserScope,qSettingsOrganisation, qSettingsApplicationPrefix+"profile_"+profile);
    //todo: check the current profile

    settings.beginGroup("Mapper");
        settings.setValue("path_OutputImage", ui->path_OutputImage->text());
        settings.setValue("path_World", ui->path_World->text());
        settings.setValue("backend",ui->backend->currentIndex());

        //tab2 area
        settings.setValue("scalefactor",ui->scalefactor->currentIndex());
        settings.setValue("geometry",ui->geometry->getGeometry());
        settings.setValue("geometry_format",ui->geometry->getFormatStr());
        settings.setValue("minY",ui->minY->value());
        settings.setValue("maxY",ui->maxY->value());
        settings.setValue("geometry_granularity",geometryGranularitySymbolic[ui->geometrymode_granularity_group->checkedId()]);
        settings.setValue("geometry_sizemode",geometrySizeModeSymbolic[ui->geometrymode_size_group->checkedId()]);

        //tab3 heightmap
        settings.setValue("generateHeightmap",ui->generateHeightmap->isChecked());
        settings.setValue("path_HeightmapNodes", ui->path_HeightmapNodes->text());
        settings.setValue("colorHeightmap", ui->colorHeightmap->text());
        settings.setValue("path_HeightmapColors", ui->path_HeightmapColors->text());
        settings.setValue("drawHeightscale", ui->drawHeightscale->isChecked());
        settings.setValue("heightLevelNull", ui->heightLevelNull->value());

        //tab4 Colors
        settings.setValue("path_ColorsTxt",ui->path_ColorsTxt->text());
        settings.setValue("bgcolor",ui->bgcolor->text());
        settings.setValue("blockcolor",ui->blockcolor->text());
        settings.setValue("scalecolor",ui->scalecolor->text());
        settings.setValue("origincolor",ui->origincolor->text());
        settings.setValue("playercolor",ui->playercolor->text());
        settings.setValue("tileborderrcolor",ui->tilebordercolor->text());

        //tab5 Featurs
        settings.setValue("drawScaleLeft",ui->drawScaleLeft->isChecked());
        settings.setValue("drawScaleTop",ui->drawScaleTop->isChecked());
        settings.setValue("drawOrigin",ui->drawOrigin->isChecked());
        settings.setValue("drawPlayers",ui->drawPlayers->isChecked());
        settings.setValue("drawAlpha",ui->drawAlpha->currentIndex());
        settings.setValue("drawAir",ui->drawAir->isChecked());
        settings.setValue("noShading",ui->noShading->isChecked());

        //tab6 Tiles
        settings.setValue("drawTiles",ui->tiles->isChecked());

    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings(qSettingsOrganisation, "Minetestmapper");

    settings.beginGroup("MainWindow");
    if (settings.value("maximized",false).toBool()) {
        showMaximized();

    }
    else {
        resize(settings.value("size", QSize(400, 400)).toSize());
        move(settings.value("pos", QPoint(200, 200)).toPoint());

    }
    if(settings.value("help",false).toBool()==false){
        ui->dockHelp->close();
    }
    currentProfile = settings.value("profile","default").toString();
    ui->actionExpert_Mode->setChecked(settings.value("expertMode",false).toBool());
    ui->actionOpen_map_after_creation->setChecked(settings.value("openMap",true).toBool());
    settings.endGroup();
}

void MainWindow::readProfile(QString profile)
{
    QSettings settings(QSettings::IniFormat,QSettings::UserScope,qSettingsOrganisation, qSettingsApplicationPrefix+"profile_"+profile);
    settings.beginGroup("Mapper");
        //tab1 Genral
        ui->path_World->setText(settings.value("path_World",QDir::homePath()).toString());
        ui->path_OutputImage->setText(settings.value("path_OutputImage",QDir::homePath().append("/map.png")).toString());
        ui->backend->setCurrentIndex(settings.value("backend",0).toInt());

        //tab2 Area
        ui->scalefactor->setCurrentIndex(settings.value("scalefactor",0).toInt());
        ui->geometry->set(settings.value("geometry").toString());
        ui->geometry->setFormat(settings.value("geometry_format").toString());
        ui->checkBox_maxY->setChecked(settings.value("checkBox_maxY",false).toBool());
        ui->checkBox_minY->setChecked(settings.value("checkBox_minY",false).toBool());
        ui->maxY->setValue(settings.value("maxY",0).toInt());
        ui->minY->setValue(settings.value("minY",0).toInt());
        QString granularity = settings.value("geometry_granularity").toString();
        if (geometryGranularityNumeric.find(granularity) != geometryGranularityNumeric.end())
            ui->geometrymode_granularity_group->button(geometryGranularityNumeric[granularity])->setChecked(true);
        // Else post a warning message ??
        QString sizemode = settings.value("geometry_sizemode").toString();
        if (geometrySizeModeNumeric.find(sizemode) != geometrySizeModeNumeric.end())
            ui->geometrymode_size_group->button(geometrySizeModeNumeric[sizemode])->setChecked(true);
        // Else post a warning message ??

        //tab3 Heightmap
        ui->generateHeightmap->setChecked(settings.value("generateHeightmap",false).toBool());
        ui->path_HeightmapNodes->setText(settings.value("path_HeightmapNodes","./colors/heightmap-nodes.txt").toString());
        ui->path_HeightmapColors->setText(settings.value("path_HeightmapColors","./colors/heightmap-colors.txt").toString());
        ui->colorHeightmap->setText(settings.value("colorHeightmap","").toString());
        ui->drawHeightscale->setChecked(settings.value("drawHeightscale",false).toBool());
        ui->heightLevelNull->setValue(settings.value("heightLevelNull",0).toInt());

        //tab4 Colors
        ui->path_ColorsTxt->setText(settings.value("path_ColorsTxt","./colors/colors.txt").toString());
        ui->bgcolor->setText(settings.value("bgcolor","white").toString());
        ui->blockcolor->setText(settings.value("blockcolor","white").toString());
        ui->scalecolor->setText(settings.value("scalecolor","black").toString());
        ui->origincolor->setText(settings.value("origincolor","red").toString());
        ui->playercolor->setText(settings.value("playercolor","yellow").toString());
        ui->tilebordercolor->setText(settings.value("tilebordercolor","black").toString());

        //tab5 Featurs
        ui->drawScaleLeft->setChecked(settings.value("drawScaleLeft",false).toBool());
        ui->drawScaleTop->setChecked(settings.value("drawScaleTop",false).toBool());
        ui->drawOrigin->setChecked(settings.value("drawOrigin",false).toBool());
        ui->drawPlayers->setChecked(settings.value("drawPlayers",false).toBool());
        ui->drawAlpha->setCurrentIndex(settings.value("drawAlpha",0).toInt());
        ui->drawAir->setChecked(settings.value("drawAir",false).toBool());
        ui->noShading->setChecked(settings.value("noShading",false).toBool());

        //tab6 Tiles
        ui->tiles->setChecked(settings.value("drawTiles",false).toBool());
        ui->tilesize->setValue(settings.value("tilesize",20).toInt());
        ui->tileborder->setValue(settings.value("tileborder",1).toInt());
        ui->tiles_coordinateX->setValue(settings.value("tiles_coordinateX",0).toInt());
        ui->tiles_coordinateY->setValue(settings.value("tiles_coordinateY",0).toInt());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        writeSettings();
        writeProfile(currentProfile);
        event->accept();
}

void MainWindow::on_browseWorld_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Minetest World"),
                                                    ui->path_World->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(dir!="") ui->path_World->setText(dir);
}

void MainWindow::on_saveImage_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save generated map to..."), "/", tr("png image (*.png)"));
    if(fileName!="") ui->path_OutputImage->setText(fileName);
}


void MainWindow::on_browseHeightmapNodes_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open HeightmapNodes File"),
                                                    ui->path_HeightmapNodes->text(),
                                                    tr("TXT File (*.txt)"));
    if(fileName!="") ui->path_HeightmapNodes->setText(fileName);
}

void MainWindow::on_browse_HeightmapColors_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open HeightmapColors File"),
                                                    ui->path_HeightmapColors->text(),
                                                    tr("TXT File (*.txt)"));
    if(fileName!="") ui->path_HeightmapColors->setText(fileName);
}

void MainWindow::on_browseColorsTxt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open colors.txt File"),
                                                    ui->path_ColorsTxt->text(),
                                                    tr("TXT File (*.txt)"));
    if(fileName!="") ui->path_ColorsTxt->setText(fileName);
}


void MainWindow::on_actionAbout_MinetestMapperGUI_triggered()
{
    QMessageBox::about(this, tr("About MinetestMapper GUI"),
             tr("<h1>About MinetestMapperGUI</h1>"
                "The <b>MinetestMapper Gui</b> is written by addi.<br />"
                "It is licensed under a <a href=\"http://creativecommons.org/licenses/by/3.0/\">Creative Commons Attribution 3.0 Unported License</a>.<br>"
                "The current version is %1. <br>"
                "The sourcecode is aviable on <a href='https://bitbucket.org/adrido/minetestmappergui/'>Bitbucket</a>.<br>"
                "You may also want to read the <a href='https://forum.minetest.net/viewtopic.php?f=14&t=12139'>Minetest forum thread</a>.<br><br>"
                "<b>Thanks to:</b><br>"
                "McKrustenkaese for his great icon").arg(GIT_VERSION));
}


void MainWindow::on_actionAbout_MinetestMapper_triggered()
{
        QMessageBox::about(this, tr("About MinetestMapper"),
                 tr("<h1>About MinetestMapper</h1>"
                    "The <b>MinetestMapper</b> is written by:<br>"
                    "Miroslav Bendík <miroslav.bendik@gmail.com><br>"
                    "ShadowNinja <shadowninja@minetest.net><br>"
                    "sfan5 <sfan5@live.de><br>"
                    "Rogier <rogier777@gmail.com><br><br>"
                    "<u>License:</u>LGPLv2.1+ and BSD 2-clause.<br>"
                    "<u>Source Code:</u> <a href='https://github.com/Rogier-5/minetest-mapper-cpp'>Github</a><br>"));
}

void MainWindow::on_path_OutputImage_textChanged()
{
    ui->label_preview->setText(tr("preview: %1").arg(getOutputFileName()));
}

void MainWindow::on_selectHeightmapColor_clicked()
{
    const QColorDialog::ColorDialogOptions options =  QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(ui->colorHeightmap->text(), this, tr("select color"),options);

    if (color.isValid()) {
        ui->colorHeightmap->setText(color.name());
        ui->colorHeightmap->setPalette(QPalette(color));
        //ui->lineEdit_bgcolor->setAutoFillBackground(true);
    }
}

void MainWindow::on_actionNew_Profile_triggered()
{
    bool ok;
    QString profile = QInputDialog::getText(this,
                                            tr("New Profile"),//title
                                            tr("Name of the new Profile:"),//label
                                            QLineEdit::Normal,
                                            "",//text
                                            &ok,0);
    if(ok && !profile.isEmpty()) {
        currentProfile = profile;
        QAction *action = new QAction(profile, this);
        action->setCheckable(true);
        action->setData(profile);

        ui->menuChoose_profile->addAction(action);
        profileGroup->addAction(action);
        action->setChecked(true);
    }
}

void MainWindow::on_actionEdit_colors_txt_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(ui->path_ColorsTxt->text()).absoluteFilePath()));
}

void MainWindow::on_actionEdit_heightmap_nodes_txt_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(ui->path_HeightmapNodes->text()).absoluteFilePath()));
}

void MainWindow::on_actionEdit_heightmap_colors_txt_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(ui->path_HeightmapColors->text()).absoluteFilePath()));
}

void MainWindow::on_drawScaleLeft_toggled(bool checked)
{
    bool state = checked || ui->drawScaleTop->isChecked();
    ui->sidescaleInterval->setEnabled(state);
    state = state && ui->sidescaleInterval->isChecked();
    ui->sidescaleIntervalMajor->setEnabled(state);
    ui->sidescaleIntervalMinor->setEnabled(state);
}

void MainWindow::on_drawScaleTop_toggled(bool checked)
{
    bool state = checked || ui->drawScaleLeft->isChecked();
    ui->sidescaleInterval->setEnabled(state);
    state = state && ui->sidescaleInterval->isChecked();
    ui->sidescaleIntervalMajor->setEnabled(state);
    ui->sidescaleIntervalMinor->setEnabled(state);
}

void MainWindow::on_drawHeightscale_toggled(bool checked)
{
    ui->heightscaleInterval->setEnabled(checked);
    bool state = checked && ui->heightscaleInterval->isChecked();
    ui->heightscaleIntervalMajor->setEnabled(state);
    ui->heightscaleIntervalMinor->setEnabled(state);
}

void MainWindow::on_tilecenter_clicked()
{
    ui->tiles_map->setText(tr("map center"));
}

void MainWindow::on_tileorigin_clicked()
{
    ui->tiles_map->setText(tr("map origin (top left)"));
}
