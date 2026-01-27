#ifndef SCHEDULEVIEWMODEL_H
#define SCHEDULEVIEWMODEL_H

#include <QSqlQueryModel>
#include <QSqlError>
#include <QDate>
#include <QTime>
#include <QVariant>
#include <QDebug>

class ScheduleViewModel : public QSqlQueryModel
{
    Q_OBJECT
    
public:
    explicit ScheduleViewModel(QObject *parent = nullptr);
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void refresh();
    
private:
    void setupQuery();
};

#endif // SCHEDULEVIEWMODEL_H
