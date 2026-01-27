#ifndef TRAINMODEL_H
#define TRAINMODEL_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class TrainModel : public QSqlTableModel
{
    Q_OBJECT
    
public:
    explicit TrainModel(QObject *parent = nullptr);

    bool addTrain(const QString &name, const QString &status, int totalSeats);
    bool updateTrain(int id, const QString &name, const QString &status, int totalSeats);
    bool removeTrain(int id);
    
    // получение данных по ID
    QVariant getTrainData(int id, const QString &field);
    
private:
    void setupModel();
};

#endif // TRAINMODEL_H
