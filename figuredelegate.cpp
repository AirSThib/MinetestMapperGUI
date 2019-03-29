#include "figuredelegate.h"

#include <QComboBox>

FigureDelegate::FigureDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
list = DrawMapFigure::getFigureList();
}

QWidget *FigureDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->setFrame(false);
    QMetaEnum figureEnum = QMetaEnum::fromType<DrawMapFigure::Figure>();
    for(int i = 0; i<list.length(); i++){
        DrawMapFigure::Figure f = static_cast<DrawMapFigure::Figure>(figureEnum.value(i));
        editor->addItem(DrawMapFigure::getIcon(f), list.at(i), f);
    }

    return editor;
}

void FigureDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QComboBox *comboBox = dynamic_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(value);
}

void FigureDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QComboBox *comboBox = dynamic_cast<QComboBox*>(editor);

    model->setData(index, comboBox->currentData(), Qt::EditRole);
}

void FigureDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

/*void FigureDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyle* style = QApplication::style();
    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &option);
    painter->drawText(textRect, option.displayAlignment, list.at(index.data().toInt()));
    QStyledItemDelegate::paint(painter, option, index);
}*/
