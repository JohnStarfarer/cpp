#include "mainwindow.h"
#include <QTimer>
#include <QApplication>
#include "dialogs/addtraindialog.h"
#include "dialogs/addwagontypedialog.h"
#include "dialogs/addroutedialog.h"
#include "dialogs/addpassengerdialog.h"
#include "dialogs/addscheduledialog.h"
#include "dialogs/addticketdialog.h"
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QStyle>
#include <QHeaderView>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_database(new Database(this))
    , m_mainTabWidget(nullptr)
    , m_reportsTabWidget(nullptr)
    , m_mainSplitter(nullptr)
{
    if (!m_database->connectToDatabase()) {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось подключиться к базе данных. Приложение будет закрыто.");
        QTimer::singleShot(0, qApp, &QApplication::quit);
        return;
    }

    // модели для операций
    m_trainModel = new TrainModel(this);
    m_wagonTypeModel = new WagonTypeModel(this);
    m_routeModel = new RouteModel(this);
    m_passengerModel = new PassengerModel(this);
    m_scheduleModel = new ScheduleModel(this);
    m_ticketModel = new TicketModel(this);

    m_scheduleViewModel = new ScheduleViewModel(this);
    m_ticketViewModel = new TicketViewModel(this);

    m_mainTabWidget = new QTabWidget(this);

    setupUI();
    setupMenuBar();
    setupToolBar();
    setupStatusBar();
    setupConnections();

    refreshAllTables();

    setWindowTitle("РЖД-Путь - Управление базой данных");
    setMinimumSize(1280, 768);

    // Добавляем стили для улучшенного внешнего вида
    QString styleSheet =
        "QTabWidget::pane {"
        "    border: 1px solid #ccc;"
        "    background-color: #2196F3;"
        "}"
        ""
        "QTabBar::tab {"
        "    background-color: #2196F3;"
        "    padding: 8px 16px;"
        "    margin-right: 2px;"
        "}"
        ""
        "QTabBar::tab:selected {"
        "    background-color: #2196F3;"
        "    color: white;"
        "}"
        ""
        "QSplitter::handle {"
        "    background-color: #2196F3;"
        "    width: 4px;"
        "}"
        ""
        "QTableView {"
        "    gridline-color: #ddd;"
        "    selection-background-color: #2196F3;"
        "}"
        "";

    setStyleSheet(styleSheet);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // разделитель
    m_mainSplitter = new QSplitter(Qt::Horizontal, this);

    // основной табвиджет
    m_mainTabWidget = new QTabWidget(this);

    // вкладка "Поезда"
    QWidget *trainTab = new QWidget;
    QVBoxLayout *trainLayout = new QVBoxLayout(trainTab);

    // кнопки для поездов
    QHBoxLayout *trainButtonLayout = new QHBoxLayout;
    m_btnAddTrain = new QPushButton("Добавить поезд", this);
    m_btnEditTrain = new QPushButton("Редактировать", this);
    m_btnDeleteTrain = new QPushButton("Удалить", this);

    trainButtonLayout->addWidget(m_btnAddTrain);
    trainButtonLayout->addWidget(m_btnEditTrain);
    trainButtonLayout->addWidget(m_btnDeleteTrain);
    trainButtonLayout->addStretch();

    // таблица поездов
    m_trainTable = new QTableView(this);
    m_trainTable->setModel(m_trainModel);
    m_trainTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_trainTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_trainTable->horizontalHeader()->setStretchLastSection(true);

    m_trainTable->hideColumn(4);

    trainLayout->addLayout(trainButtonLayout);
    trainLayout->addWidget(m_trainTable);

    m_mainTabWidget->addTab(trainTab, "Поезда");

    // вкладка "Типы вагонов"
    QWidget *wagonTypeTab = new QWidget;
    QVBoxLayout *wagonTypeLayout = new QVBoxLayout(wagonTypeTab);

    QHBoxLayout *wagonTypeButtonLayout = new QHBoxLayout;
    m_btnAddWagonType = new QPushButton("Добавить тип", this);
    m_btnEditWagonType = new QPushButton("Редактировать", this);
    m_btnDeleteWagonType = new QPushButton("Удалить", this);

    wagonTypeButtonLayout->addWidget(m_btnAddWagonType);
    wagonTypeButtonLayout->addWidget(m_btnEditWagonType);
    wagonTypeButtonLayout->addWidget(m_btnDeleteWagonType);
    wagonTypeButtonLayout->addStretch();

    m_wagonTypeTable = new QTableView(this);
    m_wagonTypeTable->setModel(m_wagonTypeModel);
    m_wagonTypeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_wagonTypeTable->horizontalHeader()->setStretchLastSection(true);

    wagonTypeLayout->addLayout(wagonTypeButtonLayout);
    wagonTypeLayout->addWidget(m_wagonTypeTable);

    m_mainTabWidget->addTab(wagonTypeTab, "Типы вагонов");

    // вкладка "Маршруты"
    QWidget *routeTab = new QWidget;
    QVBoxLayout *routeLayout = new QVBoxLayout(routeTab);

    QHBoxLayout *routeButtonLayout = new QHBoxLayout;
    m_btnAddRoute = new QPushButton("Добавить маршрут", this);
    m_btnEditRoute = new QPushButton("Редактировать", this);
    m_btnDeleteRoute = new QPushButton("Удалить", this);

    routeButtonLayout->addWidget(m_btnAddRoute);
    routeButtonLayout->addWidget(m_btnEditRoute);
    routeButtonLayout->addWidget(m_btnDeleteRoute);
    routeButtonLayout->addStretch();

    m_routeTable = new QTableView(this);
    m_routeTable->setModel(m_routeModel);
    m_routeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_routeTable->horizontalHeader()->setStretchLastSection(true);

    routeLayout->addLayout(routeButtonLayout);
    routeLayout->addWidget(m_routeTable);

    m_mainTabWidget->addTab(routeTab, "Маршруты");

    // Создаем табвиджет для отчетов
    m_reportsTabWidget = new QTabWidget(this);
    createReportsTabWidget();

    // Добавляем оба табвиджета в разделитель
    m_mainSplitter->addWidget(m_mainTabWidget);
    m_mainSplitter->addWidget(m_reportsTabWidget);

    // Устанавливаем начальные размеры
    m_mainSplitter->setSizes({640, 640});

    mainLayout->addWidget(m_mainSplitter);
    setCentralWidget(centralWidget);
}

void MainWindow::createReportsTabWidget()
{
    // вкладка "Пассажиры"
    QWidget *passengerTab = new QWidget;
    QVBoxLayout *passengerLayout = new QVBoxLayout(passengerTab);

    QHBoxLayout *passengerButtonLayout = new QHBoxLayout;
    m_btnAddPassenger = new QPushButton("Добавить пассажира", this);
    m_btnEditPassenger = new QPushButton("Редактировать", this);
    m_btnDeletePassenger = new QPushButton("Удалить", this);

    passengerButtonLayout->addWidget(m_btnAddPassenger);
    passengerButtonLayout->addWidget(m_btnEditPassenger);
    passengerButtonLayout->addWidget(m_btnDeletePassenger);
    passengerButtonLayout->addStretch();

    m_passengerTable = new QTableView(this);
    m_passengerTable->setModel(m_passengerModel);
    m_passengerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_passengerTable->horizontalHeader()->setStretchLastSection(true);

    passengerLayout->addLayout(passengerButtonLayout);
    passengerLayout->addWidget(m_passengerTable);

    m_reportsTabWidget->addTab(passengerTab, "Пассажиры");

    // вкладка "Расписание"
    QWidget *scheduleTab = new QWidget;
    QVBoxLayout *scheduleLayout = new QVBoxLayout(scheduleTab);

    QHBoxLayout *scheduleButtonLayout = new QHBoxLayout;
    m_btnAddSchedule = new QPushButton("Добавить рейс", this);
    m_btnEditSchedule = new QPushButton("Редактировать", this);
    m_btnDeleteSchedule = new QPushButton("Удалить", this);

    scheduleButtonLayout->addWidget(m_btnAddSchedule);
    scheduleButtonLayout->addWidget(m_btnEditSchedule);
    scheduleButtonLayout->addWidget(m_btnDeleteSchedule);
    scheduleButtonLayout->addStretch();

    m_scheduleTable = new QTableView(this);
    m_scheduleTable->setModel(m_scheduleViewModel);
    m_scheduleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_scheduleTable->horizontalHeader()->setStretchLastSection(true);

    scheduleLayout->addLayout(scheduleButtonLayout);
    scheduleLayout->addWidget(m_scheduleTable);

    m_reportsTabWidget->addTab(scheduleTab, "Расписание");

    // вкладка "Билеты"
    QWidget *ticketTab = new QWidget;
    QVBoxLayout *ticketLayout = new QVBoxLayout(ticketTab);

    QHBoxLayout *ticketButtonLayout = new QHBoxLayout;
    m_btnAddTicket = new QPushButton("Добавить билет", this);
    m_btnEditTicket = new QPushButton("Редактировать", this);
    m_btnDeleteTicket = new QPushButton("Удалить", this);

    ticketButtonLayout->addWidget(m_btnAddTicket);
    ticketButtonLayout->addWidget(m_btnEditTicket);
    ticketButtonLayout->addWidget(m_btnDeleteTicket);
    ticketButtonLayout->addStretch();

    m_ticketTable = new QTableView(this);
    m_ticketTable->setModel(m_ticketViewModel);
    m_ticketTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ticketTable->horizontalHeader()->setStretchLastSection(true);

    ticketLayout->addLayout(ticketButtonLayout);
    ticketLayout->addWidget(m_ticketTable);

    m_reportsTabWidget->addTab(ticketTab, "Билеты");
}

void MainWindow::setupMenuBar()
{
    // меню "Файл"
    QMenu *fileMenu = menuBar()->addMenu("Файл");

    QAction *refreshAction = new QAction("Обновить все таблицы", this);
    refreshAction->setShortcut(QKeySequence::Refresh);
    fileMenu->addAction(refreshAction);
    connect(refreshAction, &QAction::triggered, this, &MainWindow::refreshAllTables);

    fileMenu->addSeparator();

    QAction *checkDbAction = new QAction("Проверить подключение", this);
    fileMenu->addAction(checkDbAction);
    connect(checkDbAction, &QAction::triggered, this, &MainWindow::checkDatabaseConnection);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction("Выход", this);
    exitAction->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);

    // меню "Справка"
    QMenu *helpMenu = menuBar()->addMenu("Справка");

    QAction *aboutAction = new QAction("О программе", this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::setupToolBar()
{
    QToolBar *mainToolBar = addToolBar("Основные");
    mainToolBar->setMovable(false);

    QAction *refreshAction = new QAction("Обновить", this);
    refreshAction->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    mainToolBar->addAction(refreshAction);
    connect(refreshAction, &QAction::triggered, this, &MainWindow::refreshAllTables);

    mainToolBar->addSeparator();
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Готово", this);
    statusBar()->addWidget(m_statusLabel);

    QLabel *dbStatus = new QLabel("✓ База данных подключена", this);
    statusBar()->addPermanentWidget(dbStatus);
}

void MainWindow::setupConnections()
{
    // поезда
    connect(m_btnAddTrain, &QPushButton::clicked, this, &MainWindow::addTrain);
    connect(m_btnEditTrain, &QPushButton::clicked, this, &MainWindow::editTrain);
    connect(m_btnDeleteTrain, &QPushButton::clicked, this, &MainWindow::deleteTrain);

    // типы вагонов
    connect(m_btnAddWagonType, &QPushButton::clicked, this, &MainWindow::addWagonType);
    connect(m_btnEditWagonType, &QPushButton::clicked, this, &MainWindow::editWagonType);
    connect(m_btnDeleteWagonType, &QPushButton::clicked, this, &MainWindow::deleteWagonType);

    // маршруты
    connect(m_btnAddRoute, &QPushButton::clicked, this, &MainWindow::addRoute);
    connect(m_btnEditRoute, &QPushButton::clicked, this, &MainWindow::editRoute);
    connect(m_btnDeleteRoute, &QPushButton::clicked, this, &MainWindow::deleteRoute);

    // пассажиры
    connect(m_btnAddPassenger, &QPushButton::clicked, this, &MainWindow::addPassenger);
    connect(m_btnEditPassenger, &QPushButton::clicked, this, &MainWindow::editPassenger);
    connect(m_btnDeletePassenger, &QPushButton::clicked, this, &MainWindow::deletePassenger);

    // расписание
    connect(m_btnAddSchedule, &QPushButton::clicked, this, &MainWindow::addSchedule);
    connect(m_btnEditSchedule, &QPushButton::clicked, this, &MainWindow::editSchedule);
    connect(m_btnDeleteSchedule, &QPushButton::clicked, this, &MainWindow::deleteSchedule);

    // билеты
    connect(m_btnAddTicket, &QPushButton::clicked, this, &MainWindow::addTicket);
    connect(m_btnEditTicket, &QPushButton::clicked, this, &MainWindow::editTicket);
    connect(m_btnDeleteTicket, &QPushButton::clicked, this, &MainWindow::deleteTicket);
}

void MainWindow::refreshAllTables()
{
    m_statusLabel->setText("Обновление данных...");

    m_trainModel->select();
    m_wagonTypeModel->select();
    m_routeModel->select();
    m_passengerModel->select();
    m_scheduleModel->select();
    m_ticketModel->select();

    m_scheduleViewModel->refresh();
    m_ticketViewModel->refresh();

    m_statusLabel->setText("Данные обновлены");
    QTimer::singleShot(2000, [this]() { m_statusLabel->setText("Готово"); });
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "О программе",
                       "<h2>РЖД-Путь - Управление базой данных</h2>"
                       "<p>Версия 1.0.0</p>"
                       "<p>Программа для управления базой данных железнодорожных перевозок.</p>"
                       "<p>Функции:</p>"
                       "<ul>"
                       "<li>Управление поездами</li>"
                       "<li>Управление типами вагонов</li>"
                       "<li>Управление маршрутами</li>"
                       "<li>Управление пассажирами</li>"
                       "<li>Управление расписанием</li>"
                       "<li>Управление билетами</li>"
                       "</ul>"
                       "<p>База данных: PostgreSQL</p>"
                       "<p>Интерфейс: Qt 6.0</p>");
}

void MainWindow::checkDatabaseConnection()
{
    if (Database::testConnection()) {
        QMessageBox::information(this, "Проверка подключения",
                                 "Подключение к базе данных успешно установлено.");
    } else {
        QMessageBox::critical(this, "Проверка подключения",
                              "Не удалось подключиться к базе данных.");
    }
}

// методы для работы с поездами
void MainWindow::addTrain()
{
    AddTrainDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_trainModel->addTrain(dialog.getName(),
                                   dialog.getStatus(),
                                   dialog.getTotalSeats())) {
            m_trainModel->select();
            m_statusLabel->setText("Поезд добавлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить поезд");
        }
    }
}

void MainWindow::editTrain()
{
    QModelIndexList selected = m_trainTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите поезд для редактирования.");
        return;
    }

    int row = selected.first().row();
    int id = m_trainModel->data(m_trainModel->index(row, 0)).toInt();

    AddTrainDialog dialog(id, this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_trainModel->updateTrain(id,
                                      dialog.getName(),
                                      dialog.getStatus(),
                                      dialog.getTotalSeats())) {
            m_trainModel->select();
            m_statusLabel->setText("Поезд обновлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить поезд");
        }
    }
}

void MainWindow::deleteTrain()
{
    QModelIndexList selected = m_trainTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите поезд для удаления.");
        return;
    }

    int row = selected.first().row();
    int id = m_trainModel->data(m_trainModel->index(row, 0)).toInt();
    QString name = m_trainModel->data(m_trainModel->index(row, 1)).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы уверены, что хотите удалить поезд '%1'?").arg(name),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_trainModel->removeTrain(id)) {
            m_trainModel->select();
            m_statusLabel->setText("Поезд удален");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить поезд.");
        }
    }
}

// методы для работы с типами вагонов
void MainWindow::addWagonType()
{
    AddWagonTypeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_wagonTypeModel->addWagonType(dialog.getName(),
                                           dialog.getCapacity(),
                                           dialog.getDescription())) {
            m_wagonTypeModel->select();
            m_statusLabel->setText("Тип вагона добавлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить тип вагона");
        }
    }
}

void MainWindow::editWagonType()
{
    QModelIndexList selected = m_wagonTypeTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите тип вагона для редактирования.");
        return;
    }

    int row = selected.first().row();
    int id = m_wagonTypeModel->data(m_wagonTypeModel->index(row, 0)).toInt();

    AddWagonTypeDialog dialog(id, this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_wagonTypeModel->updateWagonType(id,
                                              dialog.getName(),
                                              dialog.getCapacity(),
                                              dialog.getDescription())) {
            m_wagonTypeModel->select();
            m_statusLabel->setText("Тип вагона обновлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить тип вагона");
        }
    }
}

void MainWindow::deleteWagonType()
{
    QModelIndexList selected = m_wagonTypeTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите тип вагона для удаления.");
        return;
    }

    int row = selected.first().row();
    int id = m_wagonTypeModel->data(m_wagonTypeModel->index(row, 0)).toInt();
    QString name = m_wagonTypeModel->data(m_wagonTypeModel->index(row, 1)).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы уверены, что хотите удалить тип вагона '%1'?").arg(name),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_wagonTypeModel->removeWagonType(id)) {
            m_wagonTypeModel->select();
            m_statusLabel->setText("Тип вагона удален");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить тип вагона.");
        }
    }
}

// методы для работы с маршрутами
void MainWindow::addRoute()
{
    AddRouteDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_routeModel->addRoute(dialog.getDeparture(),
                                   dialog.getArrival(),
                                   dialog.getBasePrice(),
                                   dialog.getStatus(),
                                   dialog.getDistance())) {
            m_routeModel->select();
            m_statusLabel->setText("Маршрут добавлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить маршрут");
        }
    }
}

void MainWindow::editRoute()
{
    QModelIndexList selected = m_routeTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите маршрут для редактирования.");
        return;
    }

    int row = selected.first().row();
    int id = m_routeModel->data(m_routeModel->index(row, 0)).toInt();

    AddRouteDialog dialog(id, this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_routeModel->updateRoute(id,
                                      dialog.getDeparture(),
                                      dialog.getArrival(),
                                      dialog.getBasePrice(),
                                      dialog.getStatus(),
                                      dialog.getDistance())) {
            m_routeModel->select();
            m_statusLabel->setText("Маршрут обновлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить маршрут");
        }
    }
}

void MainWindow::deleteRoute()
{
    QModelIndexList selected = m_routeTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите маршрут для удаления.");
        return;
    }

    int row = selected.first().row();
    int id = m_routeModel->data(m_routeModel->index(row, 0)).toInt();
    QString route = m_routeModel->data(m_routeModel->index(row, 1)).toString() + " - " +
                    m_routeModel->data(m_routeModel->index(row, 2)).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы уверены, что хотите удалить маршрут '%1'?").arg(route),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_routeModel->removeRoute(id)) {
            m_routeModel->select();
            m_statusLabel->setText("Маршрут удален");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить маршрут.");
        }
    }
}

// методы для работы с пассажирами
void MainWindow::addPassenger()
{
    AddPassengerDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_passengerModel->addPassenger(dialog.getLastName(),
                                           dialog.getFirstName(),
                                           dialog.getMiddleName(),
                                           dialog.getBirthDate(),
                                           dialog.getGender(),
                                           dialog.getDocumentType(),
                                           dialog.getDocumentNumber(),
                                           dialog.getPhone(),
                                           dialog.getEmail())) {
            m_passengerModel->select();
            m_statusLabel->setText("Пассажир добавлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить пассажира");
        }
    }
}

void MainWindow::editPassenger()
{
    QModelIndexList selected = m_passengerTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите пассажира для редактирования.");
        return;
    }

    int row = selected.first().row();
    int id = m_passengerModel->data(m_passengerModel->index(row, 0)).toInt();

    AddPassengerDialog dialog(id, this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_passengerModel->updatePassenger(id,
                                              dialog.getLastName(),
                                              dialog.getFirstName(),
                                              dialog.getMiddleName(),
                                              dialog.getBirthDate(),
                                              dialog.getGender(),
                                              dialog.getDocumentType(),
                                              dialog.getDocumentNumber(),
                                              dialog.getPhone(),
                                              dialog.getEmail())) {
            m_passengerModel->select();
            m_statusLabel->setText("Пассажир обновлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить пассажира");
        }
    }
}

void MainWindow::deletePassenger()
{
    QModelIndexList selected = m_passengerTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите пассажира для удаления.");
        return;
    }

    int row = selected.first().row();
    int id = m_passengerModel->data(m_passengerModel->index(row, 0)).toInt();
    QString name = m_passengerModel->data(m_passengerModel->index(row, 1)).toString() + " " +
                   m_passengerModel->data(m_passengerModel->index(row, 2)).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы уверены, что хотите удалить пассажира '%1'?").arg(name),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_passengerModel->removePassenger(id)) {
            m_passengerModel->select();
            m_statusLabel->setText("Пассажир удален");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить пассажира.");
        }
    }
}

// методы для работы с расписанием
void MainWindow::addSchedule()
{
    AddScheduleDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_scheduleModel->addSchedule(
                dialog.getRouteId(),
                dialog.getTrainId(),
                dialog.getWagonTypeId(),
                dialog.getDepartureDate(),
                dialog.getDepartureTime(),
                dialog.getArrivalDate(),
                dialog.getArrivalTime(),
                dialog.getAvailableSeats(),
                dialog.getPrice(),
                dialog.getStatus()))
        {
            m_scheduleModel->select();
            m_scheduleViewModel->refresh();
            m_statusLabel->setText("Рейс добавлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить рейс");
        }
    }
}



void MainWindow::editSchedule()
{
    QModelIndexList selected = m_scheduleTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите рейс для редактирования.");
        return;
    }

    int row = selected.first().row();
    // Получаем ID из модели отображения (первый скрытый столбец)
    int id = m_scheduleViewModel->data(m_scheduleViewModel->index(row, 0)).toInt();

    AddScheduleDialog dialog(id, this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_scheduleModel->updateSchedule(
                id,
                dialog.getRouteId(),
                dialog.getTrainId(),
                dialog.getWagonTypeId(),
                dialog.getDepartureDate(),
                dialog.getDepartureTime(),
                dialog.getArrivalDate(),
                dialog.getArrivalTime(),
                dialog.getAvailableSeats(),
                dialog.getPrice(),
                dialog.getStatus()))
        {
            m_scheduleModel->select();
            m_scheduleViewModel->refresh();
            m_statusLabel->setText("Рейс обновлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить рейс");
        }
    }
}

void MainWindow::deleteSchedule()
{
    QModelIndexList selected = m_scheduleTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите рейс для удаления.");
        return;
    }

    int row = selected.first().row();
    int id = m_scheduleViewModel->data(m_scheduleViewModel->index(row, 0)).toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  "Вы уверены, что хотите удалить этот рейс?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_scheduleModel->removeSchedule(id)) {
            m_scheduleModel->select();
            m_scheduleViewModel->refresh();
            m_statusLabel->setText("Рейс удален");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить рейс.");
        }
    }
}

// методы для работы с билетами
void MainWindow::addTicket()
{
    AddTicketDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_ticketModel->addTicket(
                dialog.getScheduleId(),
                dialog.getPassengerId(),
                dialog.getWagonNumber(),
                dialog.getSeatNumber(),
                dialog.getPrice(),
                dialog.getStatus()))
        {
            m_ticketModel->select();
            m_ticketViewModel->refresh();
            m_statusLabel->setText("Билет добавлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить билет");
        }
    }
}


void MainWindow::editTicket()
{
    QModelIndexList selected = m_ticketTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите билет для редактирования.");
        return;
    }

    int row = selected.first().row();
    int id = m_ticketViewModel->data(m_ticketViewModel->index(row, 0)).toInt();

    AddTicketDialog dialog(id, this);
    if (dialog.exec() == QDialog::Accepted) {
        if (m_ticketModel->updateTicket(
                id,
                dialog.getScheduleId(),
                dialog.getPassengerId(),
                dialog.getWagonNumber(),
                dialog.getSeatNumber(),
                dialog.getPrice(),
                dialog.getStatus()))
        {
            m_ticketModel->select();
            m_ticketViewModel->refresh();
            m_statusLabel->setText("Билет обновлен");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось обновить билет");
        }
    }
}


void MainWindow::deleteTicket()
{
    QModelIndexList selected = m_ticketTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Выберите билет для удаления.");
        return;
    }

    int row = selected.first().row();
    int id = m_ticketViewModel->data(m_ticketViewModel->index(row, 0)).toInt();
    QString ticketNumber = m_ticketViewModel->data(m_ticketViewModel->index(row, 1)).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы уверены, что хотите удалить билет '%1'?").arg(ticketNumber),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_ticketModel->removeTicket(id)) {
            m_ticketModel->select();
            m_ticketViewModel->refresh();
            m_statusLabel->setText("Билет удален");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить билет.");
        }
    }
}
