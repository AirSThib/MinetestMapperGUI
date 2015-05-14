#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qprocess.h>
#include <qstringlist.h>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readSettings();
    progressBar = new QProgressBar(ui->statusBar);
    progressBar->setAlignment(Qt::AlignRight);
    progressBar->setMaximumSize(180, 19);
    ui->statusBar->addPermanentWidget(progressBar);
    //progressBar->setValue(0);
    progressBar->setMaximum(0);
    progressBar->setMinimum(0);
    progressBar->hide();
    connect(ui->actionAbout_MinetestMapper, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAbout_QT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    createLanguageMenu();
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
        //switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
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
  }
 }
 QMainWindow::changeEvent(event);
}

QProcess *myProcess;
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_generate_clicked()
{
    // QObject *parent;
    ui->button_generate->setDisabled(true);
    myProcess = new QProcess(this);
    QString appDir =QCoreApplication::applicationDirPath();
    qDebug()<<appDir;
    QString program = QCoreApplication::applicationDirPath()+"\\mapper\\minetestmapper.exe";
    QStringList arguments;
    arguments           <<"-i" << ui->path_World->text()//"D:\\Programme\\minetest\\worlds\\server_minetest.king-arthur.eu_30000"
                        <<"--output" << ui->path_OutputImage->text()//"D:\\Users\\Adrian\\Desktop\\test2.png"
                        <<"--colors" << appDir+"\\colors\\colors.txt"
                        <<"--progress" << "--verbose-search-colors=2" //<<"--verbose"
                        <<"--drawalpha="+ui->drawAlpha->currentText()
                        <<"--bgcolor" << ui->bgcolor->text()
                        <<"--blockcolor" << ui->blockcolor->text()
                        <<"--scalecolor" << ui->scalecolor->text()
                        <<"--origincolor" << ui->origincolor->text()
                        <<"--playercolor" << ui->playercolor->text()
                        <<"--tilebordercolor" << ui->tilebordercolor->text();

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
    if(ui->generateHeightmap->isChecked()){
        arguments <<"--heightmap="+ui->colorHeightmap->text()
                  <<"--heightmap-nodes" << ui->path_HeightmapNodes->text()
                  <<"--heightmap-colors" << ui->path_HeightmapColors->text()
                  <<"--heightmap-yscale" << ui->heightmapYscale->cleanText().replace(',','.')
                  <<"--height-level-0" << ui->heightLevel0->text();
        if(ui->drawHeightscale->isChecked()){
            arguments <<"--drawheightscale";
        }
    }
    myProcess->setProcessChannelMode(QProcess::MergedChannels);
    myProcess->start(program, arguments);
    myProcess->setReadChannel(QProcess::StandardOutput);
    progressBar->show();
    progressBar->setMaximum(100);
    connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(myProcess, SIGNAL(finished(int)), this, SLOT(mapperFinisched(int)));



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
        }


        ui->statusBar->showMessage(out);
        ui->plainTextEdit_output->appendPlainText(out);
    }
}
void MainWindow::mapperFinisched(int exit)
{
    qDebug()<< "Exit code: " <<exit;
    ui->button_generate->setDisabled(false);   
    progressBar->setValue(0);
    progressBar->hide();
    //ui->statusBar->showMessage("Ready");
    if(exit ==0){
    ui->statusBar->showMessage("Finisched :)",1000);
    QDesktopServices::openUrl(QUrl(ui->path_OutputImage->text()));
    }
    else{
        QMessageBox::critical(this, tr("About MinetestMapper GUI"),
                 tr("<h1>ERROR</h1> <h2>minetestmapper failed</h2>"
                    "Exit code: <i>%1</i> <br>"
                    "Status of MinetestMapper: <i>%2</i><br>"
                    "<br>"
                    "Please fix the error and try again ")
                              .arg(exit)
                              .arg(ui->statusBar->currentMessage()));
    }


}

void MainWindow::writeSettings()
{
    QSettings settings("addi", "Minetestmapper");

    settings.beginGroup("MainWindow");
    if(isMaximized()){
        settings.setValue("maximized", isMaximized());
    }
    else{
        settings.setValue("maximized", isMaximized());
        settings.setValue("size", size());
        settings.setValue("pos", pos());
    }
    settings.endGroup();
    settings.beginGroup("Mapper");
        settings.setValue("path_OutputImage", ui->path_OutputImage->text());
        settings.setValue("path_World", ui->path_World->text());
        settings.setValue("path_HeightmapNodes", ui->path_HeightmapNodes->text());
        settings.setValue("path_HeightmapColors", ui->path_HeightmapColors->text());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("addi", "Minetestmapper");

    settings.beginGroup("MainWindow");
    if (settings.value("maximized",false).toBool()) {
        showMaximized();

    }
    else {
        resize(settings.value("size", QSize(400, 400)).toSize());
        move(settings.value("pos", QPoint(200, 200)).toPoint());

    }

    settings.endGroup();
    settings.beginGroup("Mapper");
        ui->path_OutputImage->setText(settings.value("path_OutputImage","map.png").toString());
        ui->path_World->setText(settings.value("path_World","/").toString());
        ui->path_HeightmapNodes->setText(settings.value("path_HeightmapNodes","./colors/heightmap-nodes.txt").toString());
        ui->path_HeightmapColors->setText(settings.value("path_HeightmapColors","./colors/heightmap-colors.txt").toString());
    settings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        writeSettings();
        event->accept();
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About MinetestMapper GUI"),
             tr("<h1>About MinetestMapperGUI</h1>"
                "The <b>MinetestMapper Gui</b> is written "
                "by addi <br>"
                "version 0.1"));
}



void MainWindow::on_browseWorld_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Minetest World"),
                                                    ui->path_World->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->path_World->setText(dir);
}

void MainWindow::on_saveImage_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save generated map to..."), "/", tr("png image (*.png)"));
    ui->path_OutputImage->setText(fileName);
}


void MainWindow::on_browseHeightmapNodes_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open HeightmapNodes File"),
                                                    ui->path_HeightmapNodes->text(),
                                                    tr("TXT File (*.txt)"));
    ui->path_HeightmapNodes->setText(fileName);
}

void MainWindow::on_browse_HeightmapColors_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open HeightmapColors File"),
                                                    ui->path_HeightmapColors->text(),
                                                    tr("TXT File (*.txt)"));
    ui->path_HeightmapColors->setText(fileName);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    qDebug()<<index;

}

void MainWindow::on_selectBgColor_clicked()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(ui->bgcolor->text(), this, "Select Color",options);

        if (color.isValid()) {
            ui->bgcolor->setText(color.name());
            ui->bgcolor->setPalette(QPalette(color));
            //ui->lineEdit_bgcolor->setAutoFillBackground(true);
        }
}

void MainWindow::on_selectBlockColor_clicked()
{
    const QColorDialog::ColorDialogOptions options =  QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(ui->blockcolor->text(), this, "Select Color",options);

    if (color.isValid()) {
        ui->blockcolor->setText(color.name());
        ui->blockcolor->setPalette(QPalette(color));
        //ui->lineEdit_bgcolor->setAutoFillBackground(true);
    }
}

void MainWindow::on_selectScaleColor_clicked()
{
    const QColorDialog::ColorDialogOptions options =  QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(ui->scalecolor->text(), this, "Select Color",options);

    if (color.isValid()) {
        ui->scalecolor->setText(color.name());
        ui->scalecolor->setPalette(QPalette(color));
        //ui->lineEdit_bgcolor->setAutoFillBackground(true);
    }
}

void MainWindow::on_selectOriginColor_clicked()
{
    const QColorDialog::ColorDialogOptions options =  QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(ui->origincolor->text(), this, "Select Color",options);

    if (color.isValid()) {
        ui->origincolor->setText(color.name());
        ui->origincolor->setPalette(QPalette(color));
        //ui->lineEdit_bgcolor->setAutoFillBackground(true);
    }
}


void MainWindow::on_selectPlayerColor_clicked()
{
    const QColorDialog::ColorDialogOptions options =  QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(ui->playercolor->text(), this, "Select Color",options);

    if (color.isValid()) {
        ui->playercolor->setText(color.name());
        ui->playercolor->setPalette(QPalette(color));
        //ui->lineEdit_bgcolor->setAutoFillBackground(true);
    }
}

void MainWindow::on_selectTileBorderColor_clicked()
{
    const QColorDialog::ColorDialogOptions options =  QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(ui->tilebordercolor->text(), this, "Select Color",options);

    if (color.isValid()) {
        ui->tilebordercolor->setText(color.name());
        ui->tilebordercolor->setPalette(QPalette(color));
        //ui->lineEdit_bgcolor->setAutoFillBackground(true);
    }
}
