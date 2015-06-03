#ifndef COLORLINEEDIT_H
#define COLORLINEEDIT_H
#include <QLineEdit>
#include <QPushButton>
#include <QColorDialog>

class QToolButton;

class ColorLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit ColorLineEdit(QWidget *parent = NULL);

public slots:
    void selectColor();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateColorButton(const QString &text);

private:
    //QString styleSheetForCurrentState() const;
    QString buttonStyleSheetForCurrentState() const;

    QToolButton *mColorButton;
};


#endif // COLORLINEEDIT_H
