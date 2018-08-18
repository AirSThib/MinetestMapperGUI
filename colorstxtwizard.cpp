#include "colorstxtwizard.h"
#include "makecolors.h"

#include <QDir>
#include <QVBoxLayout>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QProgressBar>

ColorsTxtWizard::ColorsTxtWizard(QWidget* parent)
    : QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new NodesTxtPage);
    addPage(new TextureFoldersPage);
    addPage(new OutputFilePage);
    addPage(new ConclusionPage);

    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/text.svg"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WizardImage.bmp"));

    setWindowTitle(tr("Colors Txt Wizard"));
    qDebug()<< wizardStyle();
    //if (wizardStyle() == WizardStyle::AeroStyle)
    setWizardStyle(WizardStyle::ModernStyle);
}
void ColorsTxtWizard::setNodesTxtFilePath(const QString &nodesTxtFilePath)
{
    setField("nodesTxt", nodesTxtFilePath);
}

IntroPage::IntroPage(QWidget* parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));
    //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

    label = new QLabel(tr("This wizard will generate a brand new colors.txt file "
                          "that fits exactly to your game and mods. You simply "
                          "need to specify the nodes.txt and the paths where your "
                          "game and your mods are installed."));
    label->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

NodesTxtPage::NodesTxtPage(QWidget* parent)
    : QWizardPage(parent)
{
    setTitle(tr("The nodes.txt file"));
    setSubTitle(tr("Follow the steps and specify the path to the nodes.txt"));

    const QString dumpnodesDownload = QStringLiteral("<a href=\"https://bitbucket.org/adrido/dumpnodes/overview\">https://bitbucket.org/adrido/dumpnodes/overview</a>");
    label = new QLabel(tr("<ol>\n"
                          "<li>First, you have to install the mod <span style=\" font-weight:600;\">dumpnodes</span>. "
                          "You can download it here: %1</li>\n"
                          "<li>Extract it like each other mod into your mods folder. </li>\n"
                          "<li>Activate it in the world configuration </li>\n"
                          "<li>Start the game normaly </li>\n"
                          "<li>If you are ingame type /dumpnodes </li>\n"
                          "<li>Now there should be a file called nodes.txt inside the world folder.</li>\n"
                          "<li>Select the generated nodes.txt file down there</li>\n"
                          "</ol>").arg(dumpnodesDownload));
    label->setWordWrap(true);

    nodesTxtLabel = new QLabel("nodes.txt:");
    nodesTxtLineEdit = new QLineEdit;
    nodesTxtLabel->setBuddy(nodesTxtLineEdit);

    registerField("nodesTxt*", nodesTxtLineEdit);
    QPushButton *button = new QPushButton(QIcon(":/open"), tr("&Browse"), this);
    connect(button, &QAbstractButton::clicked,this,&NodesTxtPage::browse);
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    layout->addWidget(label);
    hlayout->addWidget(nodesTxtLabel);
    hlayout->addWidget(nodesTxtLineEdit);
    hlayout->addWidget(button);
    layout->addLayout(hlayout);
    setLayout(layout);
}
void NodesTxtPage::browse(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open nodes.txt File"),
                                                    nodesTxtLineEdit->text(),
                                                    tr("TXT File (*.txt)"));
    if(fileName!="") nodesTxtLineEdit->setText(fileName);

}

TextureFoldersPage::TextureFoldersPage(QWidget* parent)
    : QWizardPage(parent)
{
    setTitle(tr("Texture Folders"));
    setSubTitle(tr("Seletct one or more folders where the textures for the world are. Eg. the game folder and mods folder."));
    setPixmap(QWizard::WatermarkPixmap,QPixmap());

    inputDirs = new QListWidget;
    addFolder = new QPushButton(QIcon(":/open"), tr("Add folder"),this);
    remFolder = new QPushButton(tr("Remove selected folders"),this);
    chgFolder = new QPushButton(tr("Edit selected folder"),this);

    connect(addFolder, &QAbstractButton::clicked,this,&TextureFoldersPage::add);
    connect(remFolder, &QAbstractButton::clicked,this,&TextureFoldersPage::rem);
    connect(chgFolder, &QAbstractButton::clicked,this,&TextureFoldersPage::chg);

    QPlainTextEdit *inputDirsText = new QPlainTextEdit();
    registerField("inputDirs*", inputDirsText);

    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;



    hlayout->addWidget(addFolder);
    //hlayout->addWidget(chgFolder);
    hlayout->addWidget(remFolder);
    vlayout->addLayout(hlayout);
    //vlayout->addStretch(1);
    vlayout->addWidget(inputDirs);
    setLayout(vlayout);
}

void TextureFoldersPage::add(){

    QString folder = QFileDialog::getExistingDirectory(this,tr("Select texture folder"));

    QListWidgetItem *item = new QListWidgetItem(fileIconProvider->icon(QFileIconProvider::Folder),folder);
    item->setFlags(item->flags()|Qt::ItemIsEditable);

    inputDirs->addItem(item);

    QStringList list;
    for(int i = 0; i < inputDirs->count(); ++i)
    {
        QListWidgetItem* item = inputDirs->item(i);
        list << item->data(Qt::DisplayRole).toString();
    }
    setField("inputDirs",QVariant(list));
    emit completeChanged();
}

void TextureFoldersPage::rem(){
    qDeleteAll(inputDirs->selectedItems());
    emit completeChanged();
}

void TextureFoldersPage::chg(){
    //TODO: Implement me
}
bool TextureFoldersPage::isComplete() const
{
    return inputDirs->count() >= 1;
}

OutputFilePage::OutputFilePage(QWidget* parent)
    : QWizardPage(parent)
{
    setTitle(tr("Output colors.txt"));
    setSubTitle(tr("Optionally you can specify the colors.txt where the colors should be written into. "
                   "If you leaf this empty, the file placed at the same directory as the nodes.txt file."));

    colorsTxtLabel = new QLabel("colors.txt:");
    colorsTxtLineEdit = new QLineEdit;
    colorsTxtLineEdit->setPlaceholderText("colors.txt");
    colorsTxtLabel->setBuddy(colorsTxtLineEdit);

    registerField("colorsTxt", colorsTxtLineEdit);

    QPushButton *button = new QPushButton(QIcon(":/open"), tr("&Browse"), this);
    connect(button, &QAbstractButton::clicked,this,&OutputFilePage::browse);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(colorsTxtLabel);
    layout->addWidget(colorsTxtLineEdit);
    layout->addWidget(button);
    setLayout(layout);
}

void OutputFilePage::browse(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save colors.txt File"),
                                                    colorsTxtLineEdit->text(),
                                                    tr("TXT File (*.txt)"));
    if(fileName!="") colorsTxtLineEdit->setText(fileName);

}

ConclusionPage::ConclusionPage(QWidget* parent)
    : QWizardPage(parent)
{
    setTitle(tr("Conclusion"));
    setSubTitle(tr("All done. :-) Now click the Generate button to generate the colors.txt"));


    progress = new QProgressBar;
    log = new QPlainTextEdit;
    label = new QLabel;
    label->setWordWrap(true);
    QPushButton *button = new QPushButton(tr("Generate"),this);

    connect(button, &QAbstractButton::clicked,
            this, &ConclusionPage::generate);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(progress);
    layout->addWidget(button);
    layout->addWidget(log);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 to finish.")
                       .arg(finishText));
}

bool ConclusionPage::isComplete() const {
    return generated;
}

bool ConclusionPage::generate(){
    MakeColors *makeColors = new MakeColors();
    QString fileNodesTxt = field("nodesTxt").toString();
    QString fileColorsTxt = field("colorsTxt").toString();
    if(fileColorsTxt.isEmpty()){
        fileColorsTxt = QFileInfo(fileNodesTxt).dir().absoluteFilePath("colors.txt");
    }
    makeColors->setFileColorsTxt(fileColorsTxt);
    makeColors->setFileNodesTxt(fileNodesTxt);
    makeColors->setTextureSearchDirectorys(field("inputDirs").toStringList());

    connect(makeColors, &MakeColors::outputLog,
            log, &QPlainTextEdit::appendPlainText );
    connect(makeColors, &MakeColors::progressChanged,
            progress, &QProgressBar::setValue );
    connect(makeColors, &MakeColors::maxProgressChanged,
            progress, &QProgressBar::setMaximum);
    connect(makeColors, &QThread::finished,
            [=]{generated = true; emit completeChanged();});
    makeColors->startProcess();
    return true;
}
