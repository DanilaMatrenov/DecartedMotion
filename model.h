#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QDateTime>

class MyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyTableModel(QObject *parent = nullptr);
    ~MyTableModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
 QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
public slots:
    void addRow(const QString &datetime, double x, double y);

private:
    struct RowData {
        QString datetime;
        double x;
        double y;
    };

    QList<RowData> m_data;


    void updateTimerInterval();


};

#endif // MODEL_H
