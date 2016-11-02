#include "colorstxtassistant.h"
#include "ui_colorstxtassistant.h"

ColorsTxtAssistant::ColorsTxtAssistant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorsTxtAssistant)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->buttonPrevious->setVisible(false);
    ui->buttonFinished->setVisible(false);
    parent->
}

ColorsTxtAssistant::~ColorsTxtAssistant()
{
    delete ui;
}

void ColorsTxtAssistant::on_buttonGenerate_clicked()
{
    MakeColors *makeColors = new MakeColors();
    QString fileNodesTxt = ui->fileNodesTxt->text();
    QString fileColorsTxt = ui->fileColorsTxt->text();
    if(fileColorsTxt.isEmpty()){
        fileColorsTxt = QFileInfo(fileNodesTxt).dir().absoluteFilePath("colors.txt");
    }
    makeColors->setFileColorsTxt(fileColorsTxt);
    makeColors->setFileNodesTxt(fileNodesTxt);
    makeColors->setTextureSearchDirectorys(getAllSearchDirs());

    connect(makeColors,SIGNAL(outputLog(QString, int)), this, SLOT(reciveOuputLog(QString, int)) );
    connect(makeColors,SIGNAL(progressChanged(int)), this, SLOT(reciveProgressChanged(int)));
    connect(makeColors,SIGNAL(maxProgressChanged(int)) ,this, SLOT(reciveMaxProgressChanged(int)));
    makeColors->startProcess();

}


void ColorsTxtAssistant::reciveOuputLog(QString text, int level)
{
    QMetaEnum metaEnumLogLevel = QMetaEnum::fromType<MakeColors::LogLevel>();
    QString msg = QString("%1:\t%2").arg(metaEnumLogLevel.key(level)).arg(text);
    ui->output->appendPlainText(msg);
}

void ColorsTxtAssistant::reciveProgressChanged(int newProgress)
{
    ui->progressBar->setValue(newProgress);
    //ui->output->appendPlainText(QString("Progress changed to %1").arg(newProgress));
}
void ColorsTxtAssistant::reciveMaxProgressChanged(int newProgress)
{
    ui->progressBar->setMaximum(newProgress);
    //ui->output->appendPlainText(QString("Max Progress changed to %1").arg(newProgress));
}

void ColorsTxtAssistant::on_buttonPrevious_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(--currentIndex);
    ui->buttonNext->setVisible(currentIndex != ui->stackedWidget->children().size());
    ui->buttonPrevious->setVisible(currentIndex > 0);
    ui->buttonFinished->setVisible((currentIndex+1) == ui->stackedWidget->children().size());//only visible on last page
}

void ColorsTxtAssistant::on_buttonNext_clicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(++currentIndex);
    ui->buttonPrevious->setVisible(currentIndex > 0);//Visible if not on page 0
    ui->buttonNext->setVisible((currentIndex+1) < ui->stackedWidget->children().size());// Visible if not on last page
    ui->buttonFinished->setVisible((currentIndex+1) == ui->stackedWidget->children().size());//visible on last page
}

void ColorsTxtAssistant::on_buttonAddSearchDir_clicked()
{
    QFileIconProvider *p = new QFileIconProvider();
    QString folder = QFileDialog::getExistingDirectory(this,tr("Select Folder"));

    QListWidgetItem *item = new QListWidgetItem(p->icon(QFileIconProvider::Folder),folder);
    item->setFlags(item->flags()|Qt::ItemIsEditable);

    ui->listSearchDirs->addItem(item);
    //ui->listSearchDirs->setE
}

void ColorsTxtAssistant::on_buttonRemoveSearchDir_clicked()
{
    qDeleteAll(ui->listSearchDirs->selectedItems());
}

QStringList ColorsTxtAssistant::getAllSearchDirs(void)
{
    QStringList textureSearchDirecotries;
    for(int i = 0; i < ui->listSearchDirs->count(); ++i)
    {
        QListWidgetItem* item = ui->listSearchDirs->item(i);
        textureSearchDirecotries<< item->data(Qt::DisplayRole).toString();
    }
    return textureSearchDirecotries;
}

void ColorsTxtAssistant::on_buttonFinished_clicked()
{
    this->accept();
}

void ColorsTxtAssistant::on_browseColorsTxt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open colors.txt File"),
                                                    ui->fileColorsTxt->text(),
                                                    tr("TXT File (*.txt)"));
    if(fileName!="") ui->fileColorsTxt->setText(fileName);
}

void ColorsTxtAssistant::on_browseFileNodesTxt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open colors.txt File"),
                                                    ui->fileNodesTxt->text(),
                                                    tr("TXT File (*.txt)"));
    if(fileName!="") ui->fileNodesTxt->setText(fileName);
}
