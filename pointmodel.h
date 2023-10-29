#ifndef POINTMODEL_H
#define POINTMODEL_H
#include "dataaccsess.h"
#include <QAbstractTableModel>
#include <QVector>

class PointTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PointTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    struct PointData {
        double x;
        double y;
        // Add more parameters as necessary
    };

    QVector<PointData> m_data;
private:
    dataaccsess m_dataAccess;
};

#endif // POINTMODEL_H
