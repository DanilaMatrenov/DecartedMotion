// dbconnection.cpp
#include "dbconnection.h"
#include <QtSQl/QSqlDatabase>

Database::Database()
{
}

Database::~Database()
{
    disconnect();
}

void Database::connect(const QString dbName, const QString host, const QString user, const QString password)
{qDebug() << QSqlDatabase::drivers();
    m_db.QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(host);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);

    if (!m_db.open())
    {
        // Произошла ошибка при подключении к базе данных
        qDebug() << "Failed to connect to database:" << m_db.lastError().text();
    }
}

void Database::disconnect()
{
    if (isConnected())
    {
        m_db.close();
        m_db.removeDatabase(m_db.connectionName());
    }
}

bool Database::isConnected() const
{
    return m_db.isOpen();
}

void Database::insertData(const QDateTime& dateTime, double x, double y)
{
    if (isConnected())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO fix (x, y,datefix) VALUES ( :x, :y:,datetime)");
        query.bindValue(":datetime", dateTime);
        query.bindValue(":x", x);
        query.bindValue(":y", y);

        if (!query.exec())
        {
            // Произошла ошибка при выполнении запроса
            qDebug() << "Failed to insert data:" << query.lastError().text();
        }
    }
}
