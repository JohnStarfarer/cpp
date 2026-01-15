#include "databasemanager.h"
#include <QMessageBox>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QPSQL");
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connect()
{
    m_db.setHostName("localhost");
    m_db.setDatabaseName("courier_manager");
    m_db.setUserName("courier_user");
    m_db.setPassword("password123");
    m_db.setPort(5432);

    if (!m_db.open()) {
        QMessageBox::critical(nullptr, "Ошибка подключения",
                              "Не удалось подключиться к базе данных:\n" + m_db.lastError().text());
        return false;
    }

    qDebug() << "Подключение к базе данных установлено";
    return true;
}
