#ifndef COLORLINEEDIT_H
#define COLORLINEEDIT_H
#include <QAction>
#include <QColorDialog>
#include <QLineEdit>
#include <QPainter>

class ColorLineEdit : public QLineEdit {
    Q_OBJECT

public:
    explicit ColorLineEdit(QWidget *parent = nullptr);

public slots:
    void selectColor();

private slots:
    void updateColorButton(const QString &text);

private:
    QAction *action;
    const QIcon defaultIcon = QIcon(":/color");
    static QPainter *painter;

    static inline const QIcon getColorIcon(const QColor &color) ;
};


#endif // COLORLINEEDIT_H
