#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QApplication>
#include <QTabWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStatusBar>
#include <QLabel>
#include <QSplitter>
#include "database.h"

// Включаем модели
#include "models/trainmodel.h"
#include "models/wagontypemodel.h"
#include "models/routemodel.h"
#include "models/passengermodel.h"
#include "models/schedulemodel.h"
#include "models/ticketmodel.h"
#include "models/scheduleviewmodel.h"
#include "models/ticketviewmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void refreshAllTables();
    void showAbout();
    void checkDatabaseConnection();
    
    // Слоты для кнопок
    void addTrain();
    void editTrain();
    void deleteTrain();
    
    void addWagonType();
    void editWagonType();
    void deleteWagonType();
    
    void addRoute();
    void editRoute();
    void deleteRoute();
    
    void addPassenger();
    void editPassenger();
    void deletePassenger();
    
    void addSchedule();
    void editSchedule();
    void deleteSchedule();
    
    void addTicket();
    void editTicket();
    void deleteTicket();
    
private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupStatusBar();
    void setupConnections();
    void createMainTabWidget();
    void createReportsTabWidget();
    
    // База данных
    Database *m_database;
    
    // Основной виджет для разделения
    QSplitter *m_mainSplitter;

    // Два табвиджета вместо одного
    QTabWidget *m_mainTabWidget;      // Основные операции
    QTabWidget *m_reportsTabWidget;   // Отчеты
    
    // Таблицы
    QTableView *m_trainTable;
    QTableView *m_wagonTypeTable;
    QTableView *m_routeTable;
    QTableView *m_passengerTable;
    QTableView *m_scheduleTable;
    QTableView *m_ticketTable;
    
    // Модели
    TrainModel *m_trainModel;
    WagonTypeModel *m_wagonTypeModel;
    RouteModel *m_routeModel;
    PassengerModel *m_passengerModel;
    ScheduleModel *m_scheduleModel;
    TicketModel *m_ticketModel;
    ScheduleViewModel *m_scheduleViewModel;
    TicketViewModel *m_ticketViewModel;
    
    // Кнопки для каждой вкладки
    QPushButton *m_btnAddTrain;
    QPushButton *m_btnEditTrain;
    QPushButton *m_btnDeleteTrain;
    
    QPushButton *m_btnAddWagonType;
    QPushButton *m_btnEditWagonType;
    QPushButton *m_btnDeleteWagonType;
    
    QPushButton *m_btnAddRoute;
    QPushButton *m_btnEditRoute;
    QPushButton *m_btnDeleteRoute;
    
    QPushButton *m_btnAddPassenger;
    QPushButton *m_btnEditPassenger;
    QPushButton *m_btnDeletePassenger;
    
    QPushButton *m_btnAddSchedule;
    QPushButton *m_btnEditSchedule;
    QPushButton *m_btnDeleteSchedule;
    
    QPushButton *m_btnAddTicket;
    QPushButton *m_btnEditTicket;
    QPushButton *m_btnDeleteTicket;
    
    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H
