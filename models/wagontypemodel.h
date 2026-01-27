#ifndef WAGONTYPEMODEL_H
#define WAGONTYPEMODEL_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class WagonTypeModel : public QSqlTableModel
{
    Q_OBJECT
    
public:
    explicit WagonTypeModel(QObject *parent = nullptr);
    
    // Методы для работы с данными
    bool addWagonType(const QString &name, int capacity, const QString &description = "");
    bool updateWagonType(int id, const QString &name, int capacity, const QString &description = "");
    bool removeWagonType(int id);
    
    // Получение списка типов вагонов для комбобокса
    QMap<int, QString> getWagonTypesMap();
    
private:
    void setupModel();
};

#endif // WAGONTYPEMODEL_H