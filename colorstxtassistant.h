#ifndef COLORSTXTASSISTANT_H
#define COLORSTXTASSISTANT_H

#include <QDialog>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMetaEnum>
#include <QObject>
#include <QStringList>

#include "makecolors.h"

namespace Ui {
class ColorsTxtAssistant;
}

class ColorsTxtAssistant : public QDialog
{
    Q_OBJECT

public:
    explicit ColorsTxtAssistant(QWidget *parent = 0);
    ~ColorsTxtAssistant();

    void setNodesTxtFilePath(const QString &nodesTxtFilePath);
public slots:

private slots:
    void on_buttonGenerate_clicked();

    void on_buttonPrevious_clicked();

    void on_buttonNext_clicked();

    void on_buttonAddSearchDir_clicked();

    void on_buttonRemoveSearchDir_clicked();

    void reciveOuputLog(QString text, int level);

    void reciveProgressChanged(int newProgress);
    void reciveMaxProgressChanged(int newProgress);
    void on_buttonFinished_clicked();

    void on_browseColorsTxt_clicked();

    void on_browseFileNodesTxt_clicked();

private:
    Ui::ColorsTxtAssistant *ui;

    QStringList getAllSearchDirs(void);
};

#endif // COLORSTXTASSISTANT_H
