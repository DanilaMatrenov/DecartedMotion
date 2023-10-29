#include "writeintable.h"
#include <QApplication>
#include <QAbstractTableModel>
#include <QTableView>
#include <QTimer>
#include <QVariant>
#include <QDateTime>
WriteInTable::WriteInTable()
{
    class WriteInTable : public QAbstractTableModel
    {
        Q_OBJECT

    public:
        explicit WriteInTable(QObject *parent = nullptr) : QAbstractTableModel(parent)
        {
            // Инициализация таймера для обновления данных каждые 50 мс
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, &WriteInTable::updateData);
            timer->start(50);
        }

        int rowCount(const QModelIndex &parent = QModelIndex()) const override
        {
            return coordinates.size();
        }

        int columnCount(const QModelIndex &parent = QModelIndex()) const override
        {
            return 3; // Две колонки для координат x и y и дата
        }

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
        {
            if (!index.isValid())
                return QVariant();

            if (role == Qt::DisplayRole) {
                if (index.column() == 0)
                    return coordinates.at(index.row()).x;
                else if (index.column() == 1)
                    return coordinates.at(index.row()).y;
                else if(index.column()==2);
                    return coordinates.at(index.row()).datefix;
            }

            return QVariant();
        }

    private:
        struct Coordinate {
            double x;
            double y;
            QDateTime datefix;
            // Можно добавить другие данные, связанные с координатами
        };

        QList<Coordinate> coordinates;

    private slots:
        void updateData()
        {
            // Получение новых координат объекта
            double newX;
            double newY;

            // Добавление новых координат в модель
            beginInsertRows(QModelIndex(), coordinates.size(), coordinates.size());
            coordinates.append({newX, newY});
            endInsertRows();
        }
    };
    int main(int argc, char *argv[])
    {
        QApplication app(argc, argv);

        QTableView tableView;
        WriteInTable model;
        tableView.setModel(&model);
        tableView.show();

        return app.exec();
    }
}



