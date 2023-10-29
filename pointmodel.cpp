#include "pointmodel.h"

PointTableModel::PointTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}
int PointTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

int PointTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2; // Assuming you have x and y coordinates as the parameters
}

QVariant PointTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        const PointData& point = m_data.at(index.row());
        if (index.column() == 0)
            return point.x;
        else if (index.column() == 1)
            return point.y;
    }

    return QVariant();
}

bool PointTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        PointData& point = m_data[index.row()];
        if (index.column() == 0)
            point.x = value.toDouble();
        else if (index.column() == 1)
            point.y = value.toDouble();

        emit dataChanged(index, index);
         m_dataAccess.saveData(point.x, point.y);
        return true;
    }

    return false;
}

QVariant PointTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section == 0)
                return tr("X");
            else if (section == 1)
                return tr("Y");
        } else if (orientation == Qt::Vertical) {
            return section + 1; // Row numbers
        }
    }

    return QVariant();
}
