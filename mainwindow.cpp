#include "mainwindow.h"
#include "dbconnection.h"
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
    model = new MyTableModel(this);
   ui->tableFix->setModel(model);


    ui->tableFix->show();

    // Создаем объект для соединения с базой данных
 Database dbConnection;
    // Устанавливаем параметры соединения
    QString host = "127.0.0.1";

    QString database = "FixPos";
    QString username = "postgres";
    QString password = "admin";
   dbConnection.connect(database,host, username, password);


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

        ui->lblX->setText(QString("X: %1").arg(x));
        ui->lblY->setText(QString("Y: %1").arg(y));
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString datetimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");

        model->addRow(datetimeStr, x, y);
   //     dbConnection.insertData(currentDateTime,x,y);
    });
    timer->start(1000);

}
MainWindow::~MainWindow()
{  delete model;
    delete ui;
}

