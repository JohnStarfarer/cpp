#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QTime>

class ScheduleModel : public QSqlTableModel
{
    Q_OBJECT
    
public:
    explicit ScheduleModel(QObject *parent = nullptr);
    
    // Методы для работы с данными
    bool addSchedule(int routeId, int trainId, int wagonTypeId,
                    const QDate &departureDate, const QTime &departureTime,
                    const QDate &arrivalDate, const QTime &arrivalTime,
                    int availableSeats, double price, const QString &status = "scheduled");
    
    bool updateSchedule(int id, int routeId, int trainId, int wagonTypeId,
                       const QDate &departureDate, const QTime &departureTime,
                       const QDate &arrivalDate, const QTime &arrivalTime,
                       int availableSeats, double price, const QString &status = "scheduled");
    
    bool removeSchedule(int id);
    
    // Получение расписания с деталями (для view)
    QSqlQuery getFullSchedule();
    
    // Обновление доступных мест
    bool updateAvailableSeats(int scheduleId, int change);
    
    // Получение расписания для комбобокса
    QMap<int, QString> getScheduleMap();
    
private:
    void setupModel();
};

#endif // SCHEDULEMODEL_H