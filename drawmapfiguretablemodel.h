#ifndef DRAWMAPFIGURETABLEMODEL_H
#define DRAWMAPFIGURETABLEMODEL_H

#include <QAbstractTableModel>
#include <QPixmap>
#include "drawmapfigure.h"
#include "geometry.h"

class DrawMapFigureTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DrawMapFigureTableModel(QObject *parent = 0);
    explicit DrawMapFigureTableModel(QList<DrawMapFigure *> *list, QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int position, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int position, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    QStringList getStringList(void) const;
    QStringList getArguments(void) const;
    void insertStringList(const QStringList &other);

private:
    QList<DrawMapFigure *> *list;
    QStringList header;
};

#endif // DRAWMAPFIGURETABLEMODEL_H
