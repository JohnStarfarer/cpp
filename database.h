#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    
    bool connectToDatabase();
    bool isConnected() const { return m_db.isOpen(); }
    
    QSqlDatabase getDatabase() { return m_db; }
    
    // Методы для выполнения запросов
    bool executeQuery(const QString &query);
    QSqlQuery executeSelectQuery(const QString &query);
    
    // Статические методы для проверки
    static bool testConnection();
    
private:
    QSqlDatabase m_db;
    bool initializeDatabase();
};

#endif // DATABASE_H