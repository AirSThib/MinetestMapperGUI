#ifndef FIGUREDELEGATE_H
#define FIGUREDELEGATE_H

#include <QApplication>
#include <QObject>
#include <QPainter>
#include <QSpinBox>
#include <QStyledItemDelegate>
#include <QWidget>

#include "drawmapfigure.h"

class FigureDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    FigureDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const Q_DECL_OVERRIDE;

       void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
       void setModelData(QWidget *editor, QAbstractItemModel *model,
                         const QModelIndex &index) const Q_DECL_OVERRIDE;

       void updateEditorGeometry(QWidget *editor,
           const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

       //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE ;
private:
       QStringList list;
};

#endif // FIGUREDELEGATE_H
