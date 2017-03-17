#include "colorlineedit.h"

QPainter *ColorLineEdit::painter = new QPainter();

ColorLineEdit::ColorLineEdit(QWidget *parent) : QLineEdit(parent)
{
    action = this->addAction(defaultIcon, QLineEdit::LeadingPosition);
    connect(action, &QAction::triggered, this, &ColorLineEdit::selectColor);

    connect(this, &QLineEdit::textChanged, this, &ColorLineEdit::updateColorButton);
}


void ColorLineEdit::selectColor()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::DontUseNativeDialog);
    QColor current = QColor(this->text());

    if (!current.isValid()) {
        current = Qt::white;
    }
    const QColor color = QColorDialog::getColor(current, this, NULL, options);

    if (color.isValid()) {
        this->setText(color.name());
    }
}

inline const QIcon ColorLineEdit::getColorIcon(const QColor &color)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(color);
    painter->begin(&pixmap);
    painter->drawRect(0, 0, pixmap.size().height() - 1, pixmap.size().width() - 1);
    painter->end();
    return QIcon(pixmap);
}

void ColorLineEdit::updateColorButton(const QString &text)
{
    const QColor color = QColor(text);
    const QIcon icon = color.isValid() ? getColorIcon(color) : defaultIcon;

    action->setIcon(icon);
}
