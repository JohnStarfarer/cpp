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

    bool addTicket(int scheduleId, int passengerId, int wagonNumber, 
                  int seatNumber, double price, const QString &status = "active");
    
    bool updateTicket(int id, int scheduleId, int passengerId, int wagonNumber,
                     int seatNumber, double price, const QString &status = "active");
    
    bool removeTicket(int id);
    
    // продажа билета
    bool sellTicket(int scheduleId, int passengerId, int wagonNumber, 
                   int seatNumber, double price);
    
    // отмена билета
    bool cancelTicket(int ticketId);
    
    // получение детальной информации о билетах
    QSqlQuery getTicketDetails();
    
    // получение статистики продаж
    QMap<QString, double> getSalesStatistics(const QDate &from, const QDate &to);
    
    // проверка доступности места
    bool isSeatAvailable(int scheduleId, int wagonNumber, int seatNumber);
    
private:
    void setupModel();
};

#endif // TICKETMODEL_H
