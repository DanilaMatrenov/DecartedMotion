#include "model.h"


MyTableModel::MyTableModel(QObject *parent) : QAbstractTableModel(parent) {

}

MyTableModel::~MyTableModel() {

}

int MyTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_data.size();
}

int MyTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 3; // Количество столбцов (datetime, x, y)
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        int row = index.row();
        int col = index.column();

        if (row >= 0 && row < m_data.size()) {
            const RowData &rowData = m_data[row];

            if (col == 0)
                return rowData.datetime;
            else if (col == 1)
                return rowData.x;
            else if (col == 2)
                return rowData.y;
        }
    }

    return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("DateTime");
        case 1:
            return tr("X");
        case 2:
            return tr("Y");
        }
    }

    return QVariant();
}

void MyTableModel::addRow(const QString &datetime, double x, double y) {
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.append({datetime, x, y});
    endInsertRows();
}
