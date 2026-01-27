#include "passengermodel.h"

PassengerModel::PassengerModel(QObject *parent) 
    : QSqlTableModel(parent)
{
    setupModel();
}

void PassengerModel::setupModel()
{
    setTable("passengers");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "Фамилия");
    setHeaderData(2, Qt::Horizontal, "Имя");
    setHeaderData(3, Qt::Horizontal, "Отчество");
    setHeaderData(4, Qt::Horizontal, "Дата рождения");
    setHeaderData(5, Qt::Horizontal, "Пол");
    setHeaderData(6, Qt::Horizontal, "Тип документа");
    setHeaderData(7, Qt::Horizontal, "Номер документа");
    setHeaderData(8, Qt::Horizontal, "Телефон");
    setHeaderData(9, Qt::Horizontal, "Email");
    setHeaderData(10, Qt::Horizontal, "Дата регистрации");
    
    select();
}

bool PassengerModel::addPassenger(const QString &lastName, const QString &firstName, 
                                 const QString &middleName, const QDate &birthDate,
                                 const QString &gender, const QString &documentType,
                                 const QString &documentNumber, const QString &phone,
                                 const QString &email)
{
    QSqlQuery query;
    query.prepare("INSERT INTO passengers (last_name, first_name, middle_name, "
                  "birth_date, gender, document_type, document_number, phone, email) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    
    query.addBindValue(lastName);
    query.addBindValue(firstName);
    query.addBindValue(middleName.isEmpty() ? QVariant() : QVariant(middleName));
    query.addBindValue(birthDate);
    query.addBindValue(gender);
    query.addBindValue(documentType);
    query.addBindValue(documentNumber);
    query.addBindValue(phone.isEmpty() ? QVariant() : QVariant(phone));
    query.addBindValue(email.isEmpty() ? QVariant() : QVariant(email));
    
    if (!query.exec()) {
        qDebug() << "Ошибка добавления пассажира:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool PassengerModel::updatePassenger(int id, const QString &lastName, const QString &firstName,
                                    const QString &middleName, const QDate &birthDate,
                                    const QString &gender, const QString &documentType,
                                    const QString &documentNumber, const QString &phone,
                                    const QString &email)
{
    QSqlQuery query;
    query.prepare("UPDATE passengers SET last_name = ?, first_name = ?, middle_name = ?, "
                  "birth_date = ?, gender = ?, document_type = ?, document_number = ?, "
                  "phone = ?, email = ? WHERE id = ?");
    
    query.addBindValue(lastName);
    query.addBindValue(firstName);
    query.addBindValue(middleName.isEmpty() ? QVariant() : QVariant(middleName));
    query.addBindValue(birthDate);
    query.addBindValue(gender);
    query.addBindValue(documentType);
    query.addBindValue(documentNumber);
    query.addBindValue(phone.isEmpty() ? QVariant() : QVariant(phone));
    query.addBindValue(email.isEmpty() ? QVariant() : QVariant(email));
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка обновления пассажира:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool PassengerModel::removePassenger(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM passengers WHERE id = ?");
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка удаления пассажира:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

QMap<int, QString> PassengerModel::getPassengersMap()
{
    QMap<int, QString> map;
    
    QSqlQuery query("SELECT id, last_name || ' ' || first_name || ' ' || COALESCE(middle_name, '') "
                    "FROM passengers ORDER BY last_name, first_name");
    while (query.next()) {
        map.insert(query.value(0).toInt(), query.value(1).toString().trimmed());
    }
    
    return map;
}

bool PassengerModel::passengerExists(const QString &documentNumber)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM passengers WHERE document_number = ?");
    query.addBindValue(documentNumber);
    
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    
    return false;
}
