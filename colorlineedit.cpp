#include "colorlineedit.h"

#include <QToolButton>
#include <QStyle>

ColorLineEdit::ColorLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    // Create the search button and set its icon, cursor, and stylesheet
    this->mColorButton = new QToolButton(this);
    this->mColorButton->setFixedSize(20,20);
    this->mColorButton->setCursor(Qt::PointingHandCursor);
    this->mColorButton->setStyleSheet(this->buttonStyleSheetForCurrentState());

    // Update the search button when the text changes
    QObject::connect(this, SIGNAL(textChanged(QString)), SLOT(updateColorButton(QString)));
    QObject::connect(this->mColorButton,SIGNAL(clicked(bool)), SLOT(selectColor()));
    // Some stylesheet and size corrections for the text box
    //this->setPlaceholderText(tr("Search"));
    //this->setStyleSheet(this->styleSheetForCurrentState());

    int frameWidth = this->style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    QSize minSizeHint = this->minimumSizeHint();
    this->setMinimumSize(qMax(minSizeHint.width(), this->mColorButton->sizeHint().width() + frameWidth * 2 + 2),
                         qMax(minSizeHint.height(), this->mColorButton->sizeHint().height() + frameWidth * 2+2));
}

void ColorLineEdit::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    QSize size = this->mColorButton->sizeHint();
    int frameWidth = this->style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    this->mColorButton->move(this->rect().right() - frameWidth - size.width() - 2, (this->rect().bottom() + 2 - size.height()) / 2);
}
void ColorLineEdit::selectColor()
{
    const QColorDialog::ColorDialogOptions options = QFlag(QColorDialog::DontUseNativeDialog);
    const QColor color = QColorDialog::getColor(this->text(), this, tr("select color"),options);

    if (color.isValid()) {
        this->setText(color.name());
    }
}

void ColorLineEdit::updateColorButton(const QString &text)
{
    const QColor color = QColor(text);
    if (color.isValid())
    {
        // We have some text in the box - set the button to clear the text
        QPixmap pixmap(this->height(),this->height());
        pixmap.fill(color);
        QIcon icon(pixmap);
        this->mColorButton->setIcon(icon);
    }
    else
    {
        // The text box is empty - make the icon do nothing when clicked
        QIcon icon(":/color");
        this->mColorButton->setIcon(icon);
    }

    //this->mColorButton->setStyleSheet(this->buttonStyleSheetForCurrentState());
}


QString ColorLineEdit::buttonStyleSheetForCurrentState() const
{
    QString style;
    style += "QToolButton {";
    style += "border: 1px solid black; margin: 0; padding: 0;";
    style += "}";

    /*if (!this->text().isEmpty())
    {
        style += "QToolButton:hover { background-image: url(:/images/esf-clear-hover.png); }";
        style += "QToolButton:pressed { background-image: url(:/images/esf-clear-active.png); }";
    }*/

    return style;
}
