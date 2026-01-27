#include "routemodel.h"

RouteModel::RouteModel(QObject *parent) 
    : QSqlTableModel(parent)
{
    setupModel();
}

void RouteModel::setupModel()
{
    setTable("routes");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "Отправление");
    setHeaderData(2, Qt::Horizontal, "Прибытие");
    setHeaderData(3, Qt::Horizontal, "Дистанция (км)");
    setHeaderData(4, Qt::Horizontal, "Базовая цена");
    setHeaderData(5, Qt::Horizontal, "Статус");
    
    select();
}

bool RouteModel::addRoute(const QString &departure, const QString &arrival, 
                         double basePrice, const QString &status, int distance)
{
    QSqlQuery query;
    query.prepare("INSERT INTO routes (departure_city, arrival_city, distance_km, base_price, status) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(departure);
    query.addBindValue(arrival);
    query.addBindValue(distance);
    query.addBindValue(basePrice);
    query.addBindValue(status);
    
    if (!query.exec()) {
        qDebug() << "Ошибка добавления маршрута:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool RouteModel::updateRoute(int id, const QString &departure, const QString &arrival,
                           double basePrice, const QString &status, int distance)
{
    QSqlQuery query;
    query.prepare("UPDATE routes SET departure_city = ?, arrival_city = ?, "
                  "distance_km = ?, base_price = ?, status = ? WHERE id = ?");
    query.addBindValue(departure);
    query.addBindValue(arrival);
    query.addBindValue(distance);
    query.addBindValue(basePrice);
    query.addBindValue(status);
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка обновления маршрута:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool RouteModel::removeRoute(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM routes WHERE id = ?");
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка удаления маршрута:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

QMap<int, QString> RouteModel::getRoutesMap()
{
    QMap<int, QString> map;
    
    QSqlQuery query("SELECT id, departure_city || ' - ' || arrival_city FROM routes ORDER BY departure_city");
    while (query.next()) {
        map.insert(query.value(0).toInt(), query.value(1).toString());
    }
    
    return map;
}

bool RouteModel::routeExists(const QString &departure, const QString &arrival)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM routes WHERE departure_city = ? AND arrival_city = ?");
    query.addBindValue(departure);
    query.addBindValue(arrival);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    return false;
}
