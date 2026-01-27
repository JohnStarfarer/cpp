#include "scheduleviewmodel.h"
#include <QSqlQuery>
#include <QDebug>

ScheduleViewModel::ScheduleViewModel(QObject *parent)
    : QSqlQueryModel(parent)
{
    setupQuery();
}

void ScheduleViewModel::setupQuery()
{
    // Делаем JOIN запрос, чтобы получить названия вместо ID
    QString queryStr = 
        "SELECT "
        "    s.id, "
        "    r.departure_city || ' - ' || r.arrival_city AS Маршрут, "
        "    t.name AS Поезд, "
        "    wt.name AS Тип_вагона, "
        "    s.departure_date AS Дата_отправления, "
        "    s.departure_time AS Время_отправления, "
        "    s.arrival_date AS Дата_прибытия, "
        "    s.arrival_time AS Время_прибытия, "
        "    s.available_seats AS Свободных_мест, "
        "    s.price AS Цена, "
        "    s.status AS Статус "
        "FROM schedule s "
        "JOIN routes r ON s.route_id = r.id "
        "JOIN trains t ON s.train_id = t.id "
        "JOIN wagon_types wt ON s.wagon_type_id = wt.id "
        "ORDER BY s.departure_date, s.departure_time";
    
    setQuery(queryStr);
    
    // Проверяем ошибки
    if (lastError().isValid()) {
        qDebug() << "Ошибка в ScheduleViewModel:" << lastError().text();
    }
}

QVariant ScheduleViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    // Форматируем даты для красивого отображения
    if (role == Qt::DisplayRole) {
        int column = index.column();
        
        // Дата отправления
        if (column == 4) {
            QDate date = QSqlQueryModel::data(index, role).toDate();
            return date.toString("dd.MM.yyyy");
        }
        
        // Время отправления
        if (column == 5) {
            QTime time = QSqlQueryModel::data(index, role).toTime();
            return time.toString("HH:mm");
        }
        
        // Дата прибытия
        if (column == 6) {
            QDate date = QSqlQueryModel::data(index, role).toDate();
            return date.toString("dd.MM.yyyy");
        }
        
        // Время прибытия
        if (column == 7) {
            QTime time = QSqlQueryModel::data(index, role).toTime();
            return time.toString("HH:mm");
        }
        
        // Цена
        if (column == 9) {
            double price = QSqlQueryModel::data(index, role).toDouble();
            return QString("%1 ₽").arg(price, 0, 'f', 2);
        }
    }
    
    return QSqlQueryModel::data(index, role);
}

void ScheduleViewModel::refresh()
{
    setupQuery();
}