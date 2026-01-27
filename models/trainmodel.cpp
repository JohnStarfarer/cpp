#include "trainmodel.h"

TrainModel::TrainModel(QObject *parent) 
    : QSqlTableModel(parent)
{
    setupModel();
}

void TrainModel::setupModel()
{
    setTable("trains");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    setHeaderData(0, Qt::Horizontal, "ID");
    setHeaderData(1, Qt::Horizontal, "Название");
    setHeaderData(2, Qt::Horizontal, "Статус");
    setHeaderData(3, Qt::Horizontal, "Мест всего");
    setHeaderData(4, Qt::Horizontal, "Дата создания");
    
    select();
}

bool TrainModel::addTrain(const QString &name, const QString &status, int totalSeats)
{
    QSqlQuery query;
    query.prepare("INSERT INTO trains (name, status, total_seats) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(status);
    query.addBindValue(totalSeats);
    
    if (!query.exec()) {
        qDebug() << "Ошибка добавления поезда:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool TrainModel::updateTrain(int id, const QString &name, const QString &status, int totalSeats)
{
    QSqlQuery query;
    query.prepare("UPDATE trains SET name = ?, status = ?, total_seats = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(status);
    query.addBindValue(totalSeats);
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка обновления поезда:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

bool TrainModel::removeTrain(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM trains WHERE id = ?");
    query.addBindValue(id);
    
    if (!query.exec()) {
        qDebug() << "Ошибка удаления поезда:" << query.lastError().text();
        return false;
    }
    
    select();
    return true;
}

QVariant TrainModel::getTrainData(int id, const QString &field)
{
    QSqlQuery query;
    query.prepare(QString("SELECT %1 FROM trains WHERE id = ?").arg(field));
    query.addBindValue(id);
    
    if (query.exec() && query.next()) {
        return query.value(0);
    }
    
    return QVariant();
}
