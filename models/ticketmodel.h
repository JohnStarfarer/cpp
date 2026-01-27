#ifndef TICKETMODEL_H
#define TICKETMODEL_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

class TicketModel : public QSqlTableModel
{
    Q_OBJECT
    
public:
    explicit TicketModel(QObject *parent = nullptr);
    
    // Методы для работы с данными
    bool addTicket(int scheduleId, int passengerId, int wagonNumber, 
                  int seatNumber, double price, const QString &status = "active");
    
    bool updateTicket(int id, int scheduleId, int passengerId, int wagonNumber,
                     int seatNumber, double price, const QString &status = "active");
    
    bool removeTicket(int id);
    
    // Продажа билета (с проверками)
    bool sellTicket(int scheduleId, int passengerId, int wagonNumber, 
                   int seatNumber, double price);
    
    // Отмена билета
    bool cancelTicket(int ticketId);
    
    // Получение детальной информации о билетах
    QSqlQuery getTicketDetails();
    
    // Получение статистики продаж
    QMap<QString, double> getSalesStatistics(const QDate &from, const QDate &to);
    
    // Проверка доступности места
    bool isSeatAvailable(int scheduleId, int wagonNumber, int seatNumber);
    
private:
    void setupModel();
};

#endif // TICKETMODEL_H