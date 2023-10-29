#include "mainwindow.h"
#include "model.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QRect>
#include <QDateTime>
#include <QItemDelegate>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel();
    model->setHeaderData(0, Qt::Horizontal, "Дата");
    model->setHeaderData(1, Qt::Horizontal, "Время");
    model->setHeaderData(2, Qt::Horizontal, "X");
    model->setHeaderData(3, Qt::Horizontal, "Y");

    ui->tableFix->setModel(model);
    animation = new QPropertyAnimation(ui->lblPointMotion,"geometry");
    animation->setDuration(10000);
    animation->setStartValue(ui->lblPointMotion->geometry());
    animation->setEndValue(QRect(200,200,100,50));
    animation->start();
    QTimer *timer = new QTimer(this);


    connect(timer, &QTimer::timeout, this, [this]() {
        // Получить текущие координаты объекта
        QPoint pos = ui->lblPointMotion->pos();
        int x = pos.x();
        int y = pos.y();
        QDateTime currentDateTime = QDateTime::currentDateTime();
        ui->lblX->setText(QString("X: %1").arg(x));
        ui->lblY->setText(QString("Y: %1").arg(y));
        addNewRow(x,y);
    });
    timer->start(1000);

}
void MainWindow::addNewRow(int x,int y)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();


    QStandardItem* itemDateTime = new QStandardItem(currentDateTime.toString());
    QStandardItem* itemX = new QStandardItem(QString::number(x));
    QStandardItem* itemY = new QStandardItem(QString::number(y));

    QList<QStandardItem*> newRow;
    newRow << itemDateTime << itemX << itemY;
    model->appendRow(newRow);
}
MainWindow::~MainWindow()
{
    delete ui;
}

