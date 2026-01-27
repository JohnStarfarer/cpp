#ifndef ROUTEMODEL_H
#define ROUTEMODEL_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class RouteModel : public QSqlTableModel
{
    Q_OBJECT
    
public:
    explicit RouteModel(QObject *parent = nullptr);
    
    // Методы для работы с данными
    bool addRoute(const QString &departure, const QString &arrival, 
                  double basePrice, const QString &status = "active", 
                  int distance = 0);
    bool updateRoute(int id, const QString &departure, const QString &arrival,
                     double basePrice, const QString &status = "active",
                     int distance = 0);
    bool removeRoute(int id);
    
    // Получение маршрутов для комбобокса
    QMap<int, QString> getRoutesMap();
    
    // Проверка существования маршрута
    bool routeExists(const QString &departure, const QString &arrival);
    
private:
    void setupModel();
};

#endif // ROUTEMODEL_H