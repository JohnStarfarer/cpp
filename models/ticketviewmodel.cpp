#include "ticketviewmodel.h"
#include <QSqlQuery>
#include <QDebug>

TicketViewModel::TicketViewModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    setupQuery();
}

void TicketViewModel::setupQuery()
{
    QString queryStr = 
        "SELECT "
        "    t.id, "
        "    t.ticket_number AS Номер_билета, "
        "    p.last_name || ' ' || p.first_name || COALESCE(' ' || p.middle_name, '') AS Пассажир, "
        "    r.departure_city || ' - ' || r.arrival_city AS Маршрут, "
        "    tr.name AS Поезд, "
        "    wt.name AS Тип_вагона, "
        "    t.wagon_number AS Вагон, "
        "    t.seat_number AS Место, "
        "    TO_CHAR(s.departure_date, 'DD.MM.YYYY') || ' ' || TO_CHAR(s.departure_time, 'HH24:MI') AS Отправление, "
        "    t.price AS Цена, "
        "    t.status AS Статус, "
        "    TO_CHAR(t.purchase_date, 'DD.MM.YYYY HH24:MI') AS Дата_покупки "
        "FROM tickets t "
        "JOIN passengers p ON t.passenger_id = p.id "
        "JOIN schedule s ON t.schedule_id = s.id "
        "JOIN routes r ON s.route_id = r.id "
        "JOIN trains tr ON s.train_id = tr.id "
        "JOIN wagon_types wt ON s.wagon_type_id = wt.id "
        "ORDER BY t.purchase_date DESC";
    
    setQuery(queryStr);
}

QVariant TicketViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role == Qt::DisplayRole) {
        int column = index.column();
        
        // Цена
        if (column == 9) {
            double price = QSqlQueryModel::data(index, role).toDouble();
            return QString("%1 ₽").arg(price, 0, 'f', 2);
        }
        
        // Статус билета
        if (column == 10) {
            QString status = QSqlQueryModel::data(index, role).toString();
            if (status == "active") return "Активен";
            if (status == "cancelled") return "Отменен";
            if (status == "refunded") return "Возвращен";
            if (status == "used") return "Использован";
            return status;
        }
    }
    
    return QSqlQueryModel::data(index, role);
}

void TicketViewModel::refresh()
{
    setupQuery();
}
