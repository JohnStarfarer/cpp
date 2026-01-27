#include "database.h"
#include <QDebug>
#include <QDir>
#include <QApplication>

Database::Database(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
}

Database::~Database()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool Database::connectToDatabase()
{
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setDatabaseName("rzd_control");
    m_db.setUserName("rzd_admin");
    m_db.setPassword("admin123");
    
    if (!m_db.open()) {
        QMessageBox::critical(nullptr, "Ошибка подключения", 
            "Не удалось подключиться к базе данных:\n" + m_db.lastError().text());
        return false;
    }
    
    qDebug() << "Успешное подключение к базе данных";
    return true;
}

bool Database::initializeDatabase()
{
    QStringList tables = m_db.tables();
    
    if (tables.isEmpty()) {
        QMessageBox::information(nullptr, "Инициализация", 
            "База данных пуста. Необходимо создать таблицы.");
        return false;
    }
    
    qDebug() << "Таблицы в базе данных:" << tables;
    return true;
}

bool Database::executeQuery(const QString &query)
{
    QSqlQuery sqlQuery(m_db);
    
    if (!sqlQuery.exec(query)) {
        qDebug() << "Ошибка выполнения запроса:" << sqlQuery.lastError().text();
        qDebug() << "Запрос:" << query;
        return false;
    }
    
    return true;
}

QSqlQuery Database::executeSelectQuery(const QString &query)
{
    QSqlQuery sqlQuery(m_db);
    sqlQuery.exec(query);
    return sqlQuery;
}

bool Database::testConnection()
{
    QSqlDatabase testDb = QSqlDatabase::addDatabase("QPSQL", "test_connection");
    testDb.setHostName("localhost");
    testDb.setPort(5432);
    testDb.setDatabaseName("rzd_control");
    testDb.setUserName("rzd_admin");
    testDb.setPassword("admin123");
    
    bool connected = testDb.open();
    testDb.close();
    
    QSqlDatabase::removeDatabase("test_connection");
    
    return connected;
}
