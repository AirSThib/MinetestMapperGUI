#include "drawmapfiguretablemodel.h"

#include <QBrush>

DrawMapFigureTableModel::DrawMapFigureTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    list = new QList<DrawMapFigure *>;
    header <<tr("Figure")<<tr("Coordinates")<<tr("Point")<<tr("Geometry")<<tr("Color")<<tr("Text");
}

QVariant DrawMapFigureTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal && section <= header.size())
    {
        return header[section];
    }
    else if(role == Qt::DisplayRole && orientation == Qt::Vertical){
        return section+1;
    }
    return QVariant();
}

bool DrawMapFigureTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role) && role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        header[section] = value.toString();
        emit headerDataChanged(orientation, section, section);
        return true;
    }


    return false;
}


int DrawMapFigureTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (parent.isValid())
        return 0;


    return list->size();
}

int DrawMapFigureTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (parent.isValid())
        return 0;

    return header.size();
    // FIXME: Implement me!
}

QVariant DrawMapFigureTableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
        int row = index.row();
        int col = index.column();
        DrawMapFigure *item = list->at(row);
        QPoint p = item->getPoint();
        QMetaEnum metaEnum = QMetaEnum::fromType<DrawMapFigure::Figure>();
        if(role == Qt::DecorationRole && col ==0)
        {
            return item->getIcon();
        }
        else if(role == Qt::BackgroundRole)
        {
            if(item->getFigure()==DrawMapFigure::Unknown){
                return QBrush(Qt::red);
            }
            else if(col == 2 && !item->requiresPoint()){
                return QBrush(Qt::lightGray);
            }
            else if (col == 3 && !item->requiresGeometry()){
                return QBrush(Qt::lightGray);
            }
            else if(col == 5 && !item->requiresText()){
                return QBrush(Qt::lightGray);
            }
        }
        else if(role == Qt::EditRole ||role == Qt::DisplayRole){

            switch(col){
            case 0:
                return (role == Qt::EditRole) ? QVariant(item->getFigure()) : QString(metaEnum.key(item->getFigure()));
                break;

            case 1:
                if(role == Qt::EditRole){
                    return item->getUseImageCoordinates();
                }
                else {
                    return item->getUseImageCoordinates() ? "Image (x,y)" : "Minetest (x,z)";
                }
                break;
            case 2:
                return (item->requiresPoint()) ? QString("(%1,%2)").arg(p.x()).arg(p.y()) : QVariant();
                break;
            case 3:
                return item->requiresGeometry() ? item->getGeometry()->getString(Geometry::FormatKeep) : QVariant();
                break;
            case 4:
                return item->getColor();
                break;
            case 5:
                return item->getText();
                break;
            default:
                return QVariant();
            }

            // FIXME: Implement me!
            return QVariant();
        }
       else if(role == Qt::DecorationRole && col==4){
            return item->getColor();
        }
        else if(role == Qt::CheckStateRole && col ==1){
            return item->getUseImageCoordinates()? Qt::Checked : Qt::Unchecked;
        }
    }
    return QVariant();
}

bool DrawMapFigureTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole && data(index, role) != value) {
        int row = index.row();
        int col = index.column();
        DrawMapFigure *item = list->at(row);
        switch(col){
        case 0:
            item->setFigure(value.toInt());
            break;
        case 1:
            item->setUseImageCoordinates(value.toBool());
            break;
        case 2:
            item->setPoint(value.toString());
            break;
        case 3:
            item->getGeometry()->set(value.toString());
            break;
        case 4:
            item->setColor(QColor(value.toString()));
            break;
        case 5:
            item->setText(value.toString());
        default:
            break;
        }
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    else if( index.isValid() && role == Qt::CheckStateRole &&index.column()==1){
        DrawMapFigure *item = list->at(index.row());
        item->setUseImageCoordinates(value.toInt() == Qt::Checked);
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags DrawMapFigureTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    Qt::ItemFlags flag = QAbstractItemModel::flags(index);
    int col = index.column();
    DrawMapFigure *item = list->at(index.row());
    if(col == 0)
        flag |= Qt::ItemIsEnabled|Qt::ItemIsEditable;
    else if(col == 1)
        flag |= Qt::ItemIsUserCheckable;
    else if (col == 2 && item->requiresPoint())
        flag |= Qt::ItemIsEditable;
    else if (col == 3 && item->requiresGeometry())
        flag |= Qt::ItemIsEditable;
    else if (col == 4)
        flag |= Qt::ItemIsEditable;
    else if(col == 5 && item->requiresText())
        flag |= Qt::ItemIsEditable;

    return flag;
}

bool DrawMapFigureTableModel::insertRows(int position, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, position, position + count - 1);
    for (int row = 0; row < count; ++row) {
        list->insert(position, new DrawMapFigure());
    }
    endInsertRows();
    return true;
}

bool DrawMapFigureTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return false;
}

bool DrawMapFigureTableModel::removeRows(int position, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, position, position + count - 1);
    for (int row = 0; row < count; ++row) {
        list->removeAt(position);
    }
    endRemoveRows();
    return true;
}

bool DrawMapFigureTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return false;
}

QStringList DrawMapFigureTableModel::getStringList() const
{
    QStringList retval;
    for (int i = 0; i < list->size(); ++i)
         retval << list->at(i)->getString();
    return retval;
}

QStringList DrawMapFigureTableModel::getArguments() const
{
    QStringList retval;
    for (int i = 0; i < list->size(); ++i)
         retval << list->at(i)->getSplittedString();
    return retval;
}

void DrawMapFigureTableModel::insertStringList(const QStringList &other)
{
    if(other.length() > 0){
        int leng = other.length();
        beginInsertRows(QModelIndex() , list->length(), list->length()+leng - 1);
        //insertRows(0, other.length(),QModelIndex());
        for(int i = 0; i < leng; ++i){
            list->append(new DrawMapFigure(other.at(i)));
        }
        endInsertRows();
    }
}
