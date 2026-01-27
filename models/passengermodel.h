#ifndef PASSENGERMODEL_H
#define PASSENGERMODEL_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

class PassengerModel : public QSqlTableModel
{
    Q_OBJECT
    
public:
    explicit PassengerModel(QObject *parent = nullptr);
    
    bool addPassenger(const QString &lastName, const QString &firstName, const QString &middleName,
                     const QDate &birthDate, const QString &gender, const QString &documentType,
                     const QString &documentNumber, const QString &phone = "", 
                     const QString &email = "");
    
    bool updatePassenger(int id, const QString &lastName, const QString &firstName, 
                        const QString &middleName, const QDate &birthDate, 
                        const QString &gender, const QString &documentType,
                        const QString &documentNumber, const QString &phone = "", 
                        const QString &email = "");
    
    bool removePassenger(int id);
    
    // получение пассажиров для комбобокса
    QMap<int, QString> getPassengersMap();
    
    // проверка существования пассажира по номеру документа
    bool passengerExists(const QString &documentNumber);
    
private:
    void setupModel();
};

#endif // PASSENGERMODEL_H
