#ifndef COLORSTXTWIZARD_H
#define COLORSTXTWIZARD_H

#include <QFileIconProvider>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QObject>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QWidget>
#include <QWizard>

class ColorsTxtWizard : public QWizard
{
    Q_OBJECT

public:
    ColorsTxtWizard(QWidget *parent = 0);
    void setNodesTxtFilePath(const QString &nodesTxtFilePath);
};

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

private:
    QLabel *label;
};

class NodesTxtPage : public QWizardPage
{
    Q_OBJECT

public:
    NodesTxtPage(QWidget *parent = 0);

private slots:
    void browse();
private:
    QLabel *label;
    QLabel *nodesTxtLabel;
    QLineEdit *nodesTxtLineEdit;
};

class TextureFoldersPage : public QWizardPage
{
    Q_OBJECT

public:
    TextureFoldersPage(QWidget *parent = 0);

    bool isComplete(void) const;
private slots:
    void add();
    void rem();
    void chg();
private:
    QFileIconProvider *fileIconProvider = new QFileIconProvider();
    QListWidget *inputDirs;
    QPushButton *addFolder;
    QPushButton *chgFolder;
    QPushButton *remFolder;
};

class OutputFilePage : public QWizardPage
{
    Q_OBJECT

public:
    OutputFilePage(QWidget *parent = 0);

private slots:
    void browse();
private:
    QLabel *colorsTxtLabel;
    QLineEdit *colorsTxtLineEdit;
};

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    bool isComplete(void) const override;
protected:
    void initializePage() override;

private slots:
    bool generate();
private:
    bool generated = false;
    QLabel *label;
    QProgressBar *progress;
    QPlainTextEdit *log;
};

#endif
