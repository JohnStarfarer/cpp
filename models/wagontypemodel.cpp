#include "wagontypemodel.h"

WagonTypeModel::WagonTypeModel(QObject *parent) 
    : QSqlTableModel(parent)
{
    setupModel();
}

void WagonTypeModel::setupModel()
{
    setTable("wagon_types");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "Название");
    setHeaderData(2, Qt::Horizontal, "Вместимость");
    setHeaderData(3, Qt::Horizontal, "Описание");
    
    select();
}

bool WagonTypeModel::addWagonType(const QString &name, int capacity, const QString &description)
{
    QSqlQuery query;
    query.prepare("INSERT INTO wagon_types (name, capacity, description) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(capacity);
    query.addBindValue(description);
    
    if (!query.exec()) {
        qDebug() << "Ошибка добавления типа вагона:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool WagonTypeModel::updateWagonType(int id, const QString &name, int capacity, const QString &description)
{
    QSqlQuery query;
    query.prepare("UPDATE wagon_types SET name = ?, capacity = ?, description = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(capacity);
    query.addBindValue(description);
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка обновления типа вагона:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool WagonTypeModel::removeWagonType(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM wagon_types WHERE id = ?");
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка удаления типа вагона:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

QMap<int, QString> WagonTypeModel::getWagonTypesMap()
{
    QMap<int, QString> map;
    
    QSqlQuery query("SELECT id, name FROM wagon_types ORDER BY name");
    while (query.next()) {
        map.insert(query.value(0).toInt(), query.value(1).toString());
    }
    
    return map;
}
