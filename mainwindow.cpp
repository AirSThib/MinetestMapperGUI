#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCompleter>
#include <QDesktopServices>
#include <QDirModel>
#include <QFileDialog>
#include <QStringList>


MainWindow::MainWindow(Translator *translator, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    translator(translator)
{
#ifdef PORTABLE
	//Attention: This paths could be non writable locations!
	pathAppData = qApp->applicationDirPath(); //use the Applications directory
	pathProfiles = pathAppData + "/profiles/";

	//manipulate settingsfile on portable mode
	settings = new QSettings(pathAppData + "/MinetestMapperGui.ini", QSettings::IniFormat);
#else
	QSettings dummySettings(QSettings::IniFormat, QSettings::UserScope, qApp->organizationName(), "dummy");
	pathAppData = QFileInfo(dummySettings.fileName()).path();
	pathProfiles = pathAppData + "/profiles/";
	dummySettings.deleteLater();

	//non portable use OS defaults
	settings = new QSettings();
#endif // PORTABLE

    ui->setupUi(this);
    finishUiInitialisation();
    //profile = new ProfileSettings(ui, portable);
    //backends->setStringList(QStringList());
    ui->backend->setModel(backends);
    readSettings();

    progressBar = new QProgressBar(ui->statusBar);
    progressBar->setAlignment(Qt::AlignRight);
    progressBar->setMaximumSize(180, 19);
    progressBar->setMaximum(0);
    progressBar->hide();

    ui->statusBar->addPermanentWidget(progressBar);

    connect(ui->actionAbout_QT, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionStart_colors_txt_assistant, &QAction::triggered,this,&MainWindow::startColorsTxtAssistant);
    createLanguageMenu();
    createProfilesMenu();

    ui->figureSelect->addItems(DrawMapFigure::getFigureList());

    drawMapFigureTable = new DrawMapFigureTableModel(this);

    ui->figures_list->setModel(drawMapFigureTable);

    ui->figures_list->setItemDelegateForColumn(0, new FigureDelegate(this));
    drawMapFigureTableMapper = new QDataWidgetMapper(this);
    profile = new QSettings(QString("%1/%2.ini").arg(pathProfiles).arg(currentProfile),QSettings::IniFormat);

    readProfile();

    drawMapFigureTableMapper->setModel(drawMapFigureTable);
    drawMapFigureTableMapper->addMapping(ui->figureSelect, 0, "currentIndex");
    drawMapFigureTableMapper->addMapping(ui->figureUseImageCoordinates,1);
    drawMapFigureTableMapper->addMapping(ui->figure_point,2);
    drawMapFigureTableMapper->addMapping(ui->figure_geometry, 3, "geometry");
    drawMapFigureTableMapper->addMapping(ui->figure_color,4);
    drawMapFigureTableMapper->addMapping(ui->figure_text,5);
    connect(ui->figures_list->selectionModel(), &QItemSelectionModel::currentRowChanged,
            drawMapFigureTableMapper, &QDataWidgetMapper::setCurrentModelIndex);
    ui->figures_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->figures_list->resizeColumnsToContents();
    QCompleter *completer = new QCompleter(this);
    QDirModel *model =new QDirModel(completer);
    model->setFilter(QDir::Dirs|QDir::NoDotAndDotDot|QDir::Drives);
    completer->setModel(model);
    ui->path_World->setCompleter(completer);

    if (currentSettings.mapperPath == "") {
        minetestMapper = new MinetestMapperExe(ConfigSettings::getDefaultMapperExecutable(), this);
    } else {
        minetestMapper = new MinetestMapperExe(currentSettings.mapperPath, this);
    }
    connect(minetestMapper, &MinetestMapperExe::stateChanged,
            [=](const QString &state){ ui->statusBar->showMessage(state); });//ui->statusBar,  &QStatusBar::showMessage);
    connect(minetestMapper, &MinetestMapperExe::busyStateChanged,
            progressBar,    &QWidget::setVisible);
    connect(minetestMapper, &MinetestMapperExe::progressRangeChanged,
            progressBar,    &QProgressBar::setRange);
    connect(minetestMapper, &MinetestMapperExe::progressChanged,
            progressBar,    &QProgressBar::setValue);
    connect(minetestMapper, &MinetestMapperExe::busyStateChanged,
            ui->button_generate, &QWidget::setDisabled);
    connect(minetestMapper, &MinetestMapperExe::busyStateChanged,
            ui->button_cancel, &QWidget::setEnabled);
    connect(minetestMapper, &MinetestMapperExe::mappingFinished,
            this,           &MainWindow::mapperFinisched);

    connect(minetestMapper, &MinetestMapperExe::initialisationFinished,
            this,           &MainWindow::mapperInitialized);
    connect(minetestMapper, &MinetestMapperExe::mappingStandardOutput,
            ui->standardOutput, &QTextEdit::append);
    connect(minetestMapper, &MinetestMapperExe::mappingStandardError,
            this, &MainWindow::readError);

    #ifdef Q_OS_WIN
    taskbarButton = new QWinTaskbarButton(this);

    taskbarProgress = taskbarButton->progress();

    connect(minetestMapper, &MinetestMapperExe::progressRangeChanged,
            taskbarProgress,    &QWinTaskbarProgress::setRange);
    connect(minetestMapper, &MinetestMapperExe::progressChanged,
            taskbarProgress,    &QWinTaskbarProgress::setValue);
    connect(minetestMapper, &MinetestMapperExe::busyStateChanged,
            taskbarProgress,    &QWinTaskbarProgress::setVisible);
    #endif

    // Align the Console and the Help action to the right
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    ui->mainToolBar->insertWidget(ui->actionOutputLog, spacerWidget);

    minetestWorldsModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setItemsExpandable(false);
    ui->treeView->setModel(minetestWorldsModel);
    QString worldsPath = ui->path_minetestWorlds->text();

    minetestWorldsModel->setRootPath(worldsPath);
    auto index = minetestWorldsModel->index(worldsPath);
    ui->treeView->setRootIndex(index);

    minetestMapper->init();
}

void MainWindow::showEvent( QShowEvent* event ) {
    QMainWindow::showEvent( event );

    #ifdef Q_OS_WIN
    static bool first = true;
    if(first) {
        taskbarButton->setWindow(this->windowHandle());
        first = false;
    }
    #endif
}


void MainWindow::finishUiInitialisation()
{
    ui->geometrymode_granularity_group->setId(ui->geometrymode_pixel, static_cast<int>(GeometryGranularity::pixel) );
    ui->geometrymode_granularity_group->setId(ui->geometrymode_block, static_cast<int>(GeometryGranularity::block) );

    ui->geometrymode_size_group->setId(ui->geometrymode_auto, static_cast<int>(GeometrySizeMode::automatic));
    ui->geometrymode_size_group->setId(ui->geometrymode_fixed, static_cast<int>(GeometrySizeMode::fixed));
    ui->geometrymode_size_group->setId(ui->geometrymode_shrink, static_cast<int>(GeometrySizeMode::shrink));
}

// we create the language menu entries dynamically, dependent on the existing translations.
void MainWindow::createLanguageMenu()
{
    QActionGroup* langGroup = new QActionGroup(ui->menuLanguage);
    //langGroup->setExclusive(true);

    connect(langGroup, &QActionGroup::triggered, this, &MainWindow::slotLanguageChanged);
	QStringList translations = translator->getTranslations();
	QLocale::Language defaultLanguage = translator->getCurrentLocale().language();
    for (const QString &locale : translations) {
		QLocale l = QLocale(locale);

		QLocale::Language language = l.language();

        QString lang = QLocale::languageToString(language);
        QIcon ico(QString("%1/%2.png").arg(translator->translationsPath).arg(locale));

        QAction *action = new QAction(ico, lang, this);
        action->setCheckable(true);
        action->setData(l);

        ui->menuLanguage->addAction(action);
        langGroup->addAction(action);

        // set default translators and language checked
        if (defaultLanguage == language)
        {
            action->setChecked(true);
        }
    }
}

// Called every time, when a menu entry of the language menu is called
void MainWindow::slotLanguageChanged(QAction* action)
{
    if(action) {
        // load the language dependant on the action content
		qDebug() << action->data();
		QLocale locale = QLocale(action->data().toLocale());
		translator->setLocale(locale);
    }
}

void MainWindow::changeEvent(QEvent* event)
{
	if (event) {
		switch (event->type()) {
		case QEvent::LanguageChange:
			// this event is send if a translator is loaded and installed to the Application
			ui->retranslateUi(this);
			break;

		case QEvent::LocaleChange:
			// this event is send by QWidget::setLocale
			translator->setLocale(QLocale::system());
			break;

		default:
			// Ignore other events
			break;
		}
	}
	QMainWindow::changeEvent(event);
}

MainWindow::~MainWindow()
{
    minetestMapper->cancel();
	delete settings;
	delete profile;
    delete ui;
}

void MainWindow::on_button_generate_clicked()
{
    if(!minetestMapper->isMinetestMapper())
    {
        QString mapperPath = minetestMapper->getMinetestMapperExecutableFile();
        QString message;
        if(mapperPath.isEmpty()){
            message = tr("ERROR: No minetestmapper executable could not be found.\n"
                         "Please configure one. ");
        } else {
            message = tr("ERROR: The Minetetmapper Application (%1) does not look like a Minetetestmapper\n"
                         "Please configure a correct MinetestMapper Application. ").arg(mapperPath);
        }
        int ret = QMessageBox::critical(this, tr("Minetestmapper not found"),
                                        message
                                        + tr("(Edit->Preferences)")
                                        + "\n\n"
                                        + tr("Do you want to open Preferences now?"),
                                        QMessageBox::Yes|QMessageBox::No,
                                        QMessageBox::Yes);

        if(ret == QMessageBox::Yes)
            on_actionPreferences_triggered();
        return;
    }

    qDebug() << "Minetestmapper version: " << minetestMapper->getVersion() << minetestMapper->getTreeString();
    QDir worldDir = QDir(ui->path_World->text());
    if(!worldDir.exists()||worldDir.path()=="."||worldDir.path()=="/"){
        QMessageBox::critical(this, tr("No input world selected"),
                 tr("ERROR: No MinetestWorld selected.\n\n"
                    "please select a world"));
        return;
    }
    QString imgName = getOutputFileName();
    if(imgName.isEmpty()){
        QMessageBox::critical(this, tr("No output image selected"),
                 tr("ERROR: No output image selected.\n\n"
                    "Please select a output image"));
        return;
    }
    if(QFile::exists(imgName)){
        int ret = QMessageBox::question(this, tr("The image file does already exist"),
                 tr("The File <i>%1</i> does already exist. <br><br>"
                    "Do you want to overwrite?")
                              .arg(imgName));
        if(ret != QMessageBox::Yes) return;
    }
    QDir imgPath = QFileInfo(imgName).absoluteDir();
    if(!imgPath.exists())
    {
        int ret = QMessageBox::question(this, tr("The directory does not exist"),
                 tr("The directory <i>%1</i> does not exist. <br><br>"
                    "Should it be created?")
                              .arg(imgPath.absolutePath()));
        if(ret == QMessageBox::Yes)
        {
            imgPath.mkpath(imgPath.absolutePath());
        }
        else return;

    }

    QString appDir = qApp->applicationDirPath();
    //qDebug()<<appDir;
    QDir dir = QDir(appDir);
    QString colorsTxtFilePath = getColorsTxtFilePath(&dir, &worldDir);
    if (colorsTxtFilePath.isEmpty()){
        return;
    }

    QStringList arguments;
    arguments           <<"-i" << ui->path_World->text()
                        <<"--output" << imgName
                        <<"--colors" <<  colorsTxtFilePath
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

    // Draw figures tab
    arguments << drawMapFigureTable->getArguments();

    ui->button_generate->setDisabled(true);

    if(ui->actionExpert_Mode->isChecked()){
        bool ok;
        QString parameters = QInputDialog::getMultiLineText(this,
                                                            tr("Expert Mode"),//title
                                                            tr("MinetestMapper will be executed using this arguments. \n"
                                                               "The arguments can be removed, modified, or new arguments can be added."),//label
                                                            arguments.join("\n"),//text
                                                            &ok);
        if (ok) arguments = parameters.split("\n");
        else {
            ui->button_generate->setDisabled(false);
            return;
        }
    }
    minetestMapper->startMapping(arguments);
}

void MainWindow::on_button_cancel_clicked()
{
    minetestMapper->cancel();
    //myProcess->kill();
    #ifdef Q_OS_WIN
    taskbarProgress->stop();
    #endif
}

void MainWindow::readError(const QString &str)
{
    ui->statusBar->showMessage(str);
    ui->standardOutput->append("<span style='color:red; white-space: pre;'>"+str.toHtmlEscaped()+"</span>");

}

void MainWindow::mapperInitialized()
{
    backends->setStringList(minetestMapper->getSupportedBackends());
    //ui->backend->setCurrentIndex(1);
    ui->backend->setCurrentIndex(profile->value("common/backend", 0).toInt());
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
    //wrapupMapper();
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
}

void MainWindow::createProfilesMenu(){
    profileGroup = new QActionGroup(ui->menuChoose_profile);
    profileGroup->setExclusive(true);

    connect(profileGroup, &QActionGroup::triggered, this, &MainWindow::slotProfileChanged);

    QDir dir(pathProfiles);
    qDebug()<<pathProfiles;
    QStringList fileNames = dir.entryList(QStringList("*.ini"));

    qDebug()<<"found the Profiles"<< fileNames<< "in"<<dir.absolutePath();

    if(fileNames.empty()){
        fileNames.append("default");//if nothing found create default profile
    }
    foreach (QString file, fileNames) {
        QFileInfo fi(file);
        QString name = fi.completeBaseName();

        QAction *action = new QAction(name, this);
        action->setCheckable(true);
        action->setData(name);

        ui->menuChoose_profile->addAction(action);
        profileGroup->addAction(action);

        // check if this profile the selected profile
        if (currentProfile == name)
        {
            action->setChecked(true);
        }
    }
}

// Called every time, when a menu entry of the profile menu is called
void MainWindow::slotProfileChanged(QAction* action)
{
    if(action) {
        writeProfile();
        currentProfile = action->data().toString();
        readProfile();
    }
}

void MainWindow::writeSettings()
{
#ifdef PORTABLE
	if (!settings->isWritable())
	{
		QMessageBox::warning(this, tr("Can not save settings"),
			tr("Minetest Mapper GUI could not save the settings to %1.\n"
				"Please make shure Minetest Mapper Gui can access to the file/directory").arg(settings->fileName()));
	}
#endif // PORTABLE

    settings->beginGroup("MainWindow");
    if(isMaximized()){
        settings->setValue("maximized", true);
    }
    else{
        settings->setValue("maximized", false);
        settings->setValue("size", size());
        settings->setValue("pos", pos());
    }
    settings->setValue("help", ui->actionHelp->isChecked());
    settings->setValue("showOutputLog", ui->actionOutputLog->isChecked());
    settings->setValue("profile", currentProfile);
    settings->setValue("expertMode",ui->actionExpert_Mode->isChecked());
    settings->setValue("openMap",ui->actionOpen_map_after_creation->isChecked());
    settings->endGroup();
}

void MainWindow::writeProfile()
{
#ifdef PORTABLE
	if (!profile->isWritable())
	{
		QMessageBox::warning(this, tr("Can not save profile"),
			tr("Minetest Mapper GUI could not save the current Profile '%1' to %2.\n"
				"Please make shure Minetest Mapper Gui can access to the file/directory").arg(currentProfile).arg(profile->fileName()));
	}
#endif // PORTABLE

    qDebug()<<"Write profile" << currentProfile << "to" << profile->fileName();

    profile->beginGroup("Mapper");
        //'currentSettings'
        profile->setValue("path_minetestmapper", currentSettings.mapperPath);
    profile->endGroup();

    profile->beginGroup("common");//tab1 common
        profile->setValue("path_OutputImage", ui->path_OutputImage->text());
        profile->setValue("path_World", ui->path_World->text());
		profile->setValue("path_minetestWorlds", ui->path_minetestWorlds->text());
        profile->setValue("backend",ui->backend->currentIndex());
    profile->endGroup();

    profile->beginGroup("area");    //tab2 area
        profile->setValue("scalefactor",ui->scalefactor->currentIndex());
		profile->setValue("geometry", ui->geometry->getGeometry());
        profile->setValue("minY",ui->minY->value());
        profile->setValue("maxY",ui->maxY->value());
        profile->setValue("geometry_granularity", meGeometryGranularity.key(ui->geometrymode_granularity_group->checkedId()));
        profile->setValue("geometry_sizemode", meGeometrySizeMode.key(ui->geometrymode_size_group->checkedId()));
    profile->endGroup();

    profile->beginGroup("heightmap");    //tab3 heightmap
        profile->setValue("generateHeightmap",ui->generateHeightmap->isChecked());
        profile->setValue("path_HeightmapNodes", ui->path_HeightmapNodes->text());
        profile->setValue("colorHeightmap", ui->colorHeightmap->text());
        profile->setValue("path_HeightmapColors", ui->path_HeightmapColors->text());
        profile->setValue("drawHeightscale", ui->drawHeightscale->isChecked());
        profile->setValue("heightLevelNull", ui->heightLevelNull->value());
    profile->endGroup();

    profile->beginGroup("colors");    //tab4 Colors
        profile->setValue("path_ColorsTxt", ui->path_ColorsTxt->text());
        profile->setValue("useStaticColorsTxt", ui->useStaticColorsTxt->isChecked());
        profile->setValue("bgcolor", ui->bgcolor->text());
        profile->setValue("blockcolor", ui->blockcolor->text());
        profile->setValue("scalecolor", ui->scalecolor->text());
        profile->setValue("origincolor", ui->origincolor->text());
        profile->setValue("playercolor", ui->playercolor->text());
        profile->setValue("tileborderrcolor", ui->tilebordercolor->text());
    profile->endGroup();

    profile->beginGroup("features");    //tab5 Featurs
        profile->setValue("drawScaleLeft", ui->drawScaleLeft->isChecked());
        profile->setValue("drawScaleTop", ui->drawScaleTop->isChecked());
        profile->setValue("drawOrigin", ui->drawOrigin->isChecked());
        profile->setValue("drawPlayers", ui->drawPlayers->isChecked());
        profile->setValue("drawAlpha", ui->drawAlpha->currentIndex());
        profile->setValue("drawAir", ui->drawAir->isChecked());
        profile->setValue("noShading", ui->noShading->isChecked());
    profile->endGroup();

    profile->beginGroup("tiles");   //tab6 Tiles
        profile->setValue("drawTiles", ui->tiles->isChecked());
        profile->setValue("tilesize", ui->tilesize->value());
        profile->setValue("tileborder", ui->tileborder->value());
        profile->setValue("tiles_coordinateX", ui->tiles_coordinateX->value());
        profile->setValue("tiles_coordinateY", ui->tiles_coordinateY->value());
        profile->setValue("group_tiles", ui->group_tiles_tiles->checkedId());
        profile->setValue("group_tiles_arrange", ui->group_tiles_arrange->checkedId());
        profile->setValue("group_tiles_arrange_at", ui->group_tiles_arrange_at->checkedId());
    profile->endGroup();

    profile->beginGroup("drawFigures");   //tab7 Draw Figures
        profile->setValue("drawMapFigures", drawMapFigureTable->getStringList());
    profile->endGroup();
}

void MainWindow::readSettings()
{
    qDebug()<<"Read settings from"<<settings->fileName();

    settings->beginGroup("MainWindow");
    if (settings->value("maximized",false).toBool()) {
        setWindowState(Qt::WindowMaximized);

    }
    else {
        resize(settings->value("size", QSize(400, 400)).toSize());
        move(settings->value("pos", QPoint(200, 200)).toPoint());

    }
    if(!settings->value("help",false).toBool()){
        ui->dockHelp->close();
    }
    if(!settings->value("showOutputLog",false).toBool()){
        ui->dockOutput->close();
    }
    currentProfile = settings->value("profile","default").toString();
    ui->actionExpert_Mode->setChecked(settings->value("expertMode",false).toBool());
    ui->actionOpen_map_after_creation->setChecked(settings->value("openMap",true).toBool());
    settings->endGroup();
}

void MainWindow::readProfile()
{
    qDebug()<< "Reading profile" << currentProfile << "from" << profile->fileName();

    profile->beginGroup("Mapper");
        //'currentSettings'
        currentSettings.mapperPath = profile->value("path_minetestmapper").toString();
    profile->endGroup();

    profile->beginGroup("common");    //tab1 Common
        ui->path_World->setText(profile->value("path_World",QDir::homePath()).toString());
		// TODO: Create a static class where all standard paths are set.
#ifdef Q_OS_WIN
		QString standard = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/../../Minetest/worlds";
		standard = QDir(standard).absolutePath();
#else
		QString standard = "/home/.minetest/worlds";
#endif
		ui->path_minetestWorlds->setText(profile->value("path_minetestWorlds", standard).toString());
        ui->path_OutputImage->setText(profile->value("path_OutputImage",QDir::homePath().append("/map.png")).toString());
        //ui->backend->setCurrentIndex(profile->value("backend",0).toInt()); //loading the backend here is useless, because the backends are initialized later
    profile->endGroup();

    profile->beginGroup("area");    //tab2 Area
        ui->scalefactor->setCurrentIndex(profile->value("scalefactor",0).toInt());
        ui->geometry->set(profile->value("geometry").toString(), Geometry::FormatUnknown);
        ui->checkBox_maxY->setChecked(profile->value("checkBox_maxY",false).toBool());
        ui->checkBox_minY->setChecked(profile->value("checkBox_minY",false).toBool());
        ui->maxY->setValue(profile->value("maxY",0).toInt());
        ui->minY->setValue(profile->value("minY",0).toInt());
        QString granularity = profile->value("geometry_granularity").toString();
        bool ok = false;
        int index = meGeometryGranularity.keyToValue(granularity.toLatin1().data(), &ok);
        if (ok && index != static_cast<int>(GeometryGranularity::unspecified)) {
            ui->geometrymode_granularity_group->button(index)->setChecked(true);
        }
        else if(!ok) {
            qWarning() << "Granularity "<< granularity << "is invalid.";
        }
        QString sizemode = profile->value("geometry_sizemode").toString();
        index = meGeometrySizeMode.keyToValue(sizemode.toLatin1().data(), &ok);
        if(ok){
            ui->geometrymode_size_group->button(index)->setChecked(true);
        }
        else{
            qWarning() << "GeometrySizeMode "<< sizemode << "is invalid.";
        }
    profile->endGroup();

    profile->beginGroup("heightmap");    //tab3 Heightmap
        ui->generateHeightmap->setChecked(profile->value("generateHeightmap",false).toBool());
        ui->path_HeightmapNodes->setText(profile->value("path_HeightmapNodes","./colors/heightmap-nodes.txt").toString());
        ui->path_HeightmapColors->setText(profile->value("path_HeightmapColors","./colors/heightmap-colors.txt").toString());
        ui->colorHeightmap->setText(profile->value("colorHeightmap","").toString());
        ui->drawHeightscale->setChecked(profile->value("drawHeightscale",false).toBool());
        ui->heightLevelNull->setValue(profile->value("heightLevelNull",0).toInt());
    profile->endGroup();

    profile->beginGroup("colors");    //tab4 Colors
        ui->path_ColorsTxt->setText(profile->value("path_ColorsTxt","./colors/colors.txt").toString());
        ui->useStaticColorsTxt->setChecked(profile->value("useStaticColorsTxt",false).toBool());
        ui->bgcolor->setText(profile->value("bgcolor","white").toString());
        ui->blockcolor->setText(profile->value("blockcolor","white").toString());
        ui->scalecolor->setText(profile->value("scalecolor","black").toString());
        ui->origincolor->setText(profile->value("origincolor","red").toString());
        ui->playercolor->setText(profile->value("playercolor","yellow").toString());
        ui->tilebordercolor->setText(profile->value("tilebordercolor","black").toString());
    profile->endGroup();

    profile->beginGroup("features");    //tab5 Featurs
        ui->drawScaleLeft->setChecked(profile->value("drawScaleLeft",false).toBool());
        ui->drawScaleTop->setChecked(profile->value("drawScaleTop",false).toBool());
        ui->drawOrigin->setChecked(profile->value("drawOrigin",false).toBool());
        ui->drawPlayers->setChecked(profile->value("drawPlayers",false).toBool());
        ui->drawAlpha->setCurrentIndex(profile->value("drawAlpha",0).toInt());
        ui->drawAir->setChecked(profile->value("drawAir",false).toBool());
        ui->noShading->setChecked(profile->value("noShading",false).toBool());
    profile->endGroup();

    profile->beginGroup("tiles");    //tab6 Tiles
        ui->tiles->setChecked(profile->value("drawTiles",false).toBool());
        ui->tilesize->setValue(profile->value("tilesize",20).toInt());
        ui->tileborder->setValue(profile->value("tileborder",1).toInt());
        ui->tiles_coordinateX->setValue(profile->value("tiles_coordinateX",0).toInt());
        ui->tiles_coordinateY->setValue(profile->value("tiles_coordinateY",0).toInt());
        ui->group_tiles_tiles->button(profile->value("group_tiles",-4).toInt())->setChecked(true);
        ui->group_tiles_arrange->button(profile->value("group_tiles_arrange",-3).toInt())->setChecked(true);
        ui->group_tiles_arrange_at->button(profile->value("group_tiles_arrange_at",-3).toInt())->setChecked(true);
    profile->endGroup();

    profile->beginGroup("drawFigures");
        drawMapFigureTable->insertStringList(profile->value("drawMapFigures",QStringList()).toStringList());
    profile->endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        writeSettings();
        writeProfile();
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
                          "<u>Version:</u> %1 (%2)<br>"
                          "<u>License:</u> LGPLv2.1+ and BSD 2-clause.<br>"
                          "<u>Source Code:</u> <a href='https://github.com/Rogier-5/minetest-mapper-cpp'>Github</a><br>")
                       .arg(minetestMapper->getVersion()).arg(minetestMapper->getTreeString()));
}

void MainWindow::on_path_OutputImage_textChanged()
{
    ui->label_preview->setText(tr("preview: %1").arg(getOutputFileName()));
}

void MainWindow::on_actionNew_Profile_triggered()
{
    bool ok;
    QString profile = QInputDialog::getText(this,
                                            tr("New Profile"),//title
                                            tr("Name of the new Profile:"),//label
                                            QLineEdit::Normal,
                                            "",//text
                                            &ok);
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

void MainWindow::on_actionPreferences_triggered()
{
    ConfigDialog *d = new ConfigDialog(currentSettings, this, this);
    int ret = d->exec();
    if(ret == ConfigDialog::Accepted)
    {
        // Update all 'auto' paths (colors files, ...) ???
        // (currently there are none, but in the future,
        //  colors files could be searched for relative to the minetestmapper path.
        //  If the mapper path changes, the paths of the possible colors files
        //  may change as well
        currentSettings = d->getSettings();
        minetestMapper->setExecutableFile(currentSettings.mapperPath);
        minetestMapper->init();
    }
}

void MainWindow::startColorsTxtAssistant()
{
    ColorsTxtWizard *wizard = new ColorsTxtWizard(this);
    wizard->exec();
}

/**
 * @brief MainWindow::getColorsTxtFilePath
 * @param appDir Current applications working dir
 * @param worldDir Dir of the selected minetest world
 * @return Returns a filepath to a colors.txt file or a empty string.
 */
QString MainWindow::getColorsTxtFilePath(QDir *appDir, QDir *worldDir)
{
    QString retval;

    if(ui->useStaticColorsTxt->isChecked()){

        retval = appDir->absoluteFilePath(ui->path_ColorsTxt->text()); //appDir+"\\colors\\colors.txt"
    }
    else{
        // First check if there is a colors.txt file in world dir
        if(QFile::exists( worldDir->absoluteFilePath("colors.txt")))
        {
            retval = worldDir->absoluteFilePath("colors.txt");
        }
        //else check if there is a nodes.txt in worldpath
        else if(QFile::exists( worldDir->absoluteFilePath("nodes.txt")))
        {
            // There is a nodes.txt but no colors.txt; Ask if the user want to create a colors.txt file
            int ret = QMessageBox::question(this, tr("Create a colors.txt"),
                     tr("There is a nodes.txt but no colors.txt in the world directory\n"
                        "Do you want to generate one? \n"
                        "If you select 'No' the default colors.txt will be used.")
                                 );
            if(ret == QMessageBox::Yes)
            {
                ColorsTxtWizard wizard(this);
                wizard.setNodesTxtFilePath(worldDir->absoluteFilePath("nodes.txt"));
                wizard.exec();//maybe exec should return if a colors.txt file could successfuly generated.


                if(QFile::exists( worldDir->absoluteFilePath("colors.txt"))){
                    retval = worldDir->absoluteFilePath("colors.txt");
                }
                else{
                    //not shure how to handle this case. We could just return now and do nothing, or we could use the default colors.txt file.
                    //Let the user decide. even if he have seen way too much messages.
                    int ret2 = QMessageBox::critical(this, tr("No colors.txt file"),
                                          tr("ERROR: Still no colors.txt file found inside world directory.\n\n"
                                             "Do you want to cancel or proceed with default colors.txt file?"),
                                          tr("Cancel"),
                                          tr("Proceed with default"));
                    if(ret2 == 1){
                        //Proceed button pressed
                        retval = appDir->absoluteFilePath(ui->path_ColorsTxt->text());
                    }
                    else {
                        //case of cancel
                        retval = QString();//empty string
                    }

                }

            }
            else{
                // User has choose to use the default one
                retval = appDir->absoluteFilePath(ui->path_ColorsTxt->text());
            }
        }
        else{
            // there is neither a colors.txt nor a nodes.txt file in world dir.
            // Use the colors.txt file from colors tab.
            retval = appDir->absoluteFilePath(ui->path_ColorsTxt->text());
        }
    }
    return retval;
}

void MainWindow::on_button_addFigure_clicked()
{
    drawMapFigureTable->insertRow(0);
}

void MainWindow::on_figure_geometry_apply_clicked()
{
    drawMapFigureTableMapper->submit();
}

void MainWindow::on_button_deleteFigure_clicked()
{
    QModelIndexList indexes;
    while (!(indexes = ui->figures_list->selectionModel()->selectedIndexes()).empty()) {
        drawMapFigureTable->removeRow(indexes.first().row());
    }
}

void MainWindow::on_figureSelect_currentIndexChanged(int index)
{
    static const QStringList anchors = QStringList() << "figure"
                                                     << "drawmaparrow"
                                                     << "drawmapcircle"
                                                     << "drawmapellipse"
                                                     << "drawmapline"
                                                     << "drawmappoint"
                                                     << "drawmaprectangle"
                                                     << "drawmaptext";
    ui->figureInformation->scrollToAnchor(anchors.at(index));
}

void MainWindow::on_actionOpen_Terminal_triggered()
{
    QUrl mtmapperenv;
#if defined Q_OS_LINUX
    mtmapperenv = QUrl::fromLocalFile("mtmapperenv.sh");
#elif defined Q_OS_WIN
    mtmapperenv = QUrl::fromLocalFile("mtmapperenv.bat");
#elif defined Q_OS_MACOS
    mtmapperenv = QUrl::fromLocalFile("mtmapperenv.sh"); // The sh might also work on OSX
#else
    mtmapperenv = QUrl();
#endif
    if (!QDesktopServices::openUrl(mtmapperenv)) {
        QMessageBox::critical(this,
                              tr("Could not open Terminal"),
                              tr("Error: Could not open scriptfile (%1) for Terminal").arg(mtmapperenv.toDisplayString()));
    }
}

void MainWindow::on_treeView_activated(const QModelIndex &index)
{
    ui->path_World->setText(minetestWorldsModel->filePath(index));
}

void MainWindow::on_path_minetestWorlds_editingFinished()
{
    minetestWorldsModel->setRootPath(ui->path_minetestWorlds->text());
    auto index = minetestWorldsModel->index(ui->path_minetestWorlds->text());
    ui->treeView->setRootIndex(index);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->path_World->setText(minetestWorldsModel->filePath(index));
}


void MainWindow::on_browseWorldsDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    ui->path_minetestWorlds->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        ui->path_minetestWorlds->setText(dir);
        on_path_minetestWorlds_editingFinished();
    }
}
