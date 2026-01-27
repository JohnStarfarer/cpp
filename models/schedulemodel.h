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

    bool addSchedule(int routeId, int trainId, int wagonTypeId,
                    const QDate &departureDate, const QTime &departureTime,
                    const QDate &arrivalDate, const QTime &arrivalTime,
                    int availableSeats, double price, const QString &status = "scheduled");
    
    bool updateSchedule(int id, int routeId, int trainId, int wagonTypeId,
                       const QDate &departureDate, const QTime &departureTime,
                       const QDate &arrivalDate, const QTime &arrivalTime,
                       int availableSeats, double price, const QString &status = "scheduled");
    
    bool removeSchedule(int id);
    
    // получение расписания с деталями
    QSqlQuery getFullSchedule();
    
    // обновление доступных мест
    bool updateAvailableSeats(int scheduleId, int change);
    
    // получение расписания для комбобокса
    QMap<int, QString> getScheduleMap();
    
private:
    void setupModel();
};

#endif // SCHEDULEMODEL_H
