#include "schedulemodel.h"

ScheduleModel::ScheduleModel(QObject *parent) 
    : QSqlTableModel(parent)
{
    setupModel();
}

void ScheduleModel::setupModel()
{
    setTable("schedule");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "ID Маршрута");
    setHeaderData(2, Qt::Horizontal, "ID Поезда");
    setHeaderData(3, Qt::Horizontal, "ID Типа вагона");
    setHeaderData(4, Qt::Horizontal, "Дата отправления");
    setHeaderData(5, Qt::Horizontal, "Время отправления");
    setHeaderData(6, Qt::Horizontal, "Дата прибытия");
    setHeaderData(7, Qt::Horizontal, "Время прибытия");
    setHeaderData(8, Qt::Horizontal, "Свободных мест");
    setHeaderData(9, Qt::Horizontal, "Цена");
    setHeaderData(10, Qt::Horizontal, "Статус");
    
    select();
}

bool ScheduleModel::addSchedule(int routeId, int trainId, int wagonTypeId,
                              const QDate &departureDate, const QTime &departureTime,
                              const QDate &arrivalDate, const QTime &arrivalTime,
                              int availableSeats, double price, const QString &status)
{
    QSqlQuery query;
    query.prepare("INSERT INTO schedule (route_id, train_id, wagon_type_id, "
                  "departure_date, departure_time, arrival_date, arrival_time, "
                  "available_seats, price, status) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(routeId);
    query.addBindValue(trainId);
    query.addBindValue(wagonTypeId);
    query.addBindValue(departureDate);
    query.addBindValue(departureTime);
    query.addBindValue(arrivalDate);
    query.addBindValue(arrivalTime);
    query.addBindValue(availableSeats);
    query.addBindValue(price);
    query.addBindValue(status);
    
    if (!query.exec()) {
        qDebug() << "Ошибка добавления расписания:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool ScheduleModel::updateSchedule(int id, int routeId, int trainId, int wagonTypeId,
                                 const QDate &departureDate, const QTime &departureTime,
                                 const QDate &arrivalDate, const QTime &arrivalTime,
                                 int availableSeats, double price, const QString &status)
{
    QSqlQuery query;
    query.prepare("UPDATE schedule SET route_id = ?, train_id = ?, wagon_type_id = ?, "
                  "departure_date = ?, departure_time = ?, arrival_date = ?, arrival_time = ?, "
                  "available_seats = ?, price = ?, status = ? WHERE id = ?");
    
    query.addBindValue(routeId);
    query.addBindValue(trainId);
    query.addBindValue(wagonTypeId);
    query.addBindValue(departureDate);
    query.addBindValue(departureTime);
    query.addBindValue(arrivalDate);
    query.addBindValue(arrivalTime);
    query.addBindValue(availableSeats);
    query.addBindValue(price);
    query.addBindValue(status);
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка обновления расписания:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool ScheduleModel::removeSchedule(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM schedule WHERE id = ?");
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка удаления расписания:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

QSqlQuery ScheduleModel::getFullSchedule()
{
    QSqlQuery query;
    query.exec("SELECT s.id, r.departure_city || ' - ' || r.arrival_city as route, "
               "t.name as train, wt.name as wagon_type, s.departure_date, "
               "s.departure_time, s.arrival_date, s.arrival_time, "
               "s.available_seats, s.price, s.status "
               "FROM schedule s "
               "JOIN routes r ON s.route_id = r.id "
               "JOIN trains t ON s.train_id = t.id "
               "JOIN wagon_types wt ON s.wagon_type_id = wt.id "
               "ORDER BY s.departure_date, s.departure_time");
    
    return query;
}

bool ScheduleModel::updateAvailableSeats(int scheduleId, int change)
{
    QSqlQuery query;
    query.prepare("UPDATE schedule SET available_seats = available_seats + ? WHERE id = ?");
    query.addBindValue(change);
    query.addBindValue(scheduleId);
    
    return query.exec();
}

QMap<int, QString> ScheduleModel::getScheduleMap()
{
    QMap<int, QString> map;
    
    QSqlQuery query("SELECT s.id, r.departure_city || ' - ' || r.arrival_city || ' (' || "
                    "TO_CHAR(s.departure_date, 'DD.MM.YYYY') || ' ' || "
                    "TO_CHAR(s.departure_time, 'HH24:MI') || ')' as schedule_info "
                    "FROM schedule s "
                    "JOIN routes r ON s.route_id = r.id "
                    "ORDER BY s.departure_date, s.departure_time");
    
    while (query.next()) {
        map.insert(query.value(0).toInt(), query.value(1).toString());
    }
    
    return map;
}
