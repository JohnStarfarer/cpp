#ifndef TICKETVIEWMODEL_H
#define TICKETVIEWMODEL_H

#include <QSqlQueryModel>
#include <QObject>

class TicketViewModel : public QSqlQueryModel
{
    Q_OBJECT
    
public:
    explicit TicketViewModel(QObject *parent = nullptr);
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void refresh();
    
private:
    void setupQuery();
};

#endif // TICKETVIEWMODEL_H