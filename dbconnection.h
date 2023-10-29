#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QtSQl/QSqlDatabase>
#include <QtSQl/QSqlError>
#include <QtSQl/QSqlQuery>

class  Database
{

public:
    Database();
    ~Database();
    void connect(const QString dbName, const QString host, const QString user, const QString password);
    void disconnect();
    bool isConnected() const;
    void insertData(const QDateTime& dateTime, double x, double y);

private:
    QSqlDatabase m_db;
};


#endif // DBCONNECTION_H
