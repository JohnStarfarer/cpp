#include "ticketmodel.h"

TicketModel::TicketModel(QObject *parent) 
    : QSqlTableModel(parent)
{
    setupModel();
}

void TicketModel::setupModel()
{
    setTable("tickets");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "Номер билета");
    setHeaderData(2, Qt::Horizontal, "ID Расписания");
    setHeaderData(3, Qt::Horizontal, "ID Пассажира");
    setHeaderData(4, Qt::Horizontal, "Номер вагона");
    setHeaderData(5, Qt::Horizontal, "Номер места");
    setHeaderData(6, Qt::Horizontal, "Дата покупки");
    setHeaderData(7, Qt::Horizontal, "Цена");
    setHeaderData(8, Qt::Horizontal, "Статус");
    
    select();
}

bool TicketModel::addTicket(int scheduleId, int passengerId, int wagonNumber,
                          int seatNumber, double price, const QString &status)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tickets (schedule_id, passenger_id, wagon_number, "
                  "seat_number, price, status) VALUES (?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(scheduleId);
    query.addBindValue(passengerId);
    query.addBindValue(wagonNumber);
    query.addBindValue(seatNumber);
    query.addBindValue(price);
    query.addBindValue(status);
    
    if (!query.exec()) {
        qDebug() << "Ошибка добавления билета:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool TicketModel::updateTicket(int id, int scheduleId, int passengerId,
                             int wagonNumber, int seatNumber, double price,
                             const QString &status)
{
    QSqlDatabase::database().transaction();

    QSqlQuery query;
    query.prepare("UPDATE tickets SET schedule_id = ?, passenger_id = ?, "
                  "wagon_number = ?, seat_number = ?, price = ?, status = ? "
                  "WHERE id = ?");
    
    query.addBindValue(scheduleId);
    query.addBindValue(passengerId);
    query.addBindValue(wagonNumber);
    query.addBindValue(seatNumber);
    query.addBindValue(price);
    query.addBindValue(status);
    query.addBindValue(id);
    
    if (query.exec()) {
        QSqlDatabase::database().commit();
        return true;
    } else {
        QSqlDatabase::database().rollback();
        return false;
    }
    
    select();
    return true;
}

bool TicketModel::removeTicket(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tickets WHERE id = ?");
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка удаления билета:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool TicketModel::sellTicket(int scheduleId, int passengerId, int wagonNumber,
                           int seatNumber, double price)
{
    if (!isSeatAvailable(scheduleId, wagonNumber, seatNumber)) {
        qDebug() << "Место уже занято";
        return false;
    }

    QSqlQuery setIso;
    if (!setIso.exec("SET TRANSACTION ISOLATION LEVEL REPEATABLE READ")) {
        qDebug() << "Ошибка установки уровня изоляции:" << setIso.lastError();
        return false;
    }

    if (!QSqlDatabase::database().transaction()) {
        qDebug() << "Ошибка начала транзакции";
        return false;
    }

    if (!addTicket(scheduleId, passengerId, wagonNumber, seatNumber, price, "active")) {
        QSqlDatabase::database().rollback();
        return false;
    }
    
    QSqlQuery query;
    query.prepare("UPDATE schedule SET available_seats = available_seats - 1 WHERE id = ?");
    query.addBindValue(scheduleId);
    
    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        qDebug() << "Ошибка обновления доступных мест:" << query.lastError().text();
        return false;
    }
    
    QSqlDatabase::database().commit();
    return true;
}

bool TicketModel::cancelTicket(int ticketId)
{
    QSqlDatabase::database().transaction();
    
    QSqlQuery query;
    query.prepare("SELECT schedule_id FROM tickets WHERE id = ? AND status = 'active'");
    query.addBindValue(ticketId);
    
    if (!query.exec() || !query.next()) {
        QSqlDatabase::database().rollback();
        return false;
    }
    
    int scheduleId = query.value(0).toInt();
    
    query.prepare("UPDATE tickets SET status = 'cancelled' WHERE id = ?");
    query.addBindValue(ticketId);
    
    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }
    
    query.prepare("UPDATE schedule SET available_seats = available_seats + 1 WHERE id = ?");
    query.addBindValue(scheduleId);
    
    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }
    
    QSqlDatabase::database().commit();
    select();
    return true;
}

QSqlQuery TicketModel::getTicketDetails()
{
    QSqlQuery query;
    query.exec("SELECT t.ticket_number, "
               "p.last_name || ' ' || p.first_name || ' ' || COALESCE(p.middle_name, '') as passenger, "
               "r.departure_city || ' - ' || r.arrival_city as route, "
               "tr.name as train, wt.name as wagon_type, "
               "t.wagon_number, t.seat_number, t.price, t.status, t.purchase_date "
               "FROM tickets t "
               "JOIN passengers p ON t.passenger_id = p.id "
               "JOIN schedule s ON t.schedule_id = s.id "
               "JOIN routes r ON s.route_id = r.id "
               "JOIN trains tr ON s.train_id = tr.id "
               "JOIN wagon_types wt ON s.wagon_type_id = wt.id "
               "ORDER BY t.purchase_date DESC");
    
    return query;
}

QMap<QString, double> TicketModel::getSalesStatistics(const QDate &from, const QDate &to)
{
    QMap<QString, double> stats;
    
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) as tickets_sold, "
                  "SUM(price) as total_revenue, "
                  "AVG(price) as avg_price "
                  "FROM tickets "
                  "WHERE status = 'active' AND purchase_date BETWEEN ? AND ?");
    
    query.addBindValue(from);
    query.addBindValue(to.addDays(1));
    
    if (query.exec() && query.next()) {
        stats["tickets_sold"] = query.value(0).toDouble();
        stats["total_revenue"] = query.value(1).toDouble();
        stats["avg_price"] = query.value(2).toDouble();
    }
    
    return stats;
}

bool TicketModel::isSeatAvailable(int scheduleId, int wagonNumber, int seatNumber)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM tickets "
                  "WHERE schedule_id = ? AND wagon_number = ? AND seat_number = ? "
                  "AND status = 'active'");
    
    query.addBindValue(scheduleId);
    query.addBindValue(wagonNumber);
    query.addBindValue(seatNumber);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() == 0;
    }
    
    return false;
}
