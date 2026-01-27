#include "addscheduledialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMap>

AddScheduleDialog::AddScheduleDialog(QWidget *parent)
    : QDialog(parent)
    , m_scheduleId(0)
{
    setupUI();
    setWindowTitle("Добавить рейс в расписание");
}

AddScheduleDialog::AddScheduleDialog(int scheduleId, QWidget *parent)
    : QDialog(parent)
    , m_scheduleId(scheduleId)
{
    setupUI();
    setWindowTitle("Редактировать рейс");
    loadScheduleData(scheduleId);
}

void AddScheduleDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Группа "Основные данные"
    QGroupBox *mainGroup = new QGroupBox("Основные данные", this);
    QFormLayout *formLayout = new QFormLayout(mainGroup);
    
    // Маршрут
    m_routeCombo = new QComboBox(this);
    formLayout->addRow("Маршрут:*", m_routeCombo);
    
    // Поезд
    m_trainCombo = new QComboBox(this);
    formLayout->addRow("Поезд:*", m_trainCombo);
    
    // Тип вагона
    m_wagonTypeCombo = new QComboBox(this);
    formLayout->addRow("Тип вагона:*", m_wagonTypeCombo);
    
    mainGroup->setLayout(formLayout);
    mainLayout->addWidget(mainGroup);
    
    // Группа "Даты и время"
    QGroupBox *timeGroup = new QGroupBox("Даты и время", this);
    QFormLayout *timeLayout = new QFormLayout(timeGroup);
    
    // Отправление
    QHBoxLayout *departureLayout = new QHBoxLayout;
    m_departureDateEdit = new QDateEdit(this);
    m_departureDateEdit->setCalendarPopup(true);
    m_departureDateEdit->setDate(QDate::currentDate().addDays(1));
    m_departureDateEdit->setMinimumDate(QDate::currentDate());
    m_departureDateEdit->setDisplayFormat("dd.MM.yyyy");
    
    m_departureTimeEdit = new QTimeEdit(this);
    m_departureTimeEdit->setTime(QTime(8, 0));
    m_departureTimeEdit->setDisplayFormat("HH:mm");
    
    departureLayout->addWidget(m_departureDateEdit);
    departureLayout->addWidget(new QLabel("в", this));
    departureLayout->addWidget(m_departureTimeEdit);
    timeLayout->addRow("Отправление:*", departureLayout);
    
    // Прибытие
    QHBoxLayout *arrivalLayout = new QHBoxLayout;
    m_arrivalDateEdit = new QDateEdit(this);
    m_arrivalDateEdit->setCalendarPopup(true);
    m_arrivalDateEdit->setDate(QDate::currentDate().addDays(1));
    m_arrivalDateEdit->setMinimumDate(QDate::currentDate());
    m_arrivalDateEdit->setDisplayFormat("dd.MM.yyyy");
    
    m_arrivalTimeEdit = new QTimeEdit(this);
    m_arrivalTimeEdit->setTime(QTime(12, 0));
    m_arrivalTimeEdit->setDisplayFormat("HH:mm");
    
    arrivalLayout->addWidget(m_arrivalDateEdit);
    arrivalLayout->addWidget(new QLabel("в", this));
    arrivalLayout->addWidget(m_arrivalTimeEdit);
    timeLayout->addRow("Прибытие:*", arrivalLayout);
    
    timeGroup->setLayout(timeLayout);
    mainLayout->addWidget(timeGroup);
    
    // Группа "Дополнительно"
    QGroupBox *extraGroup = new QGroupBox("Дополнительно", this);
    QFormLayout *extraLayout = new QFormLayout(extraGroup);
    
    // Свободные места
    m_seatsSpin = new QSpinBox(this);
    m_seatsSpin->setRange(1, 1000);
    m_seatsSpin->setValue(50);
    m_seatsSpin->setSuffix(" мест");
    extraLayout->addRow("Свободные места:*", m_seatsSpin);
    
    // Цена
    m_priceSpin = new QDoubleSpinBox(this);
    m_priceSpin->setRange(0, 100000);
    m_priceSpin->setValue(2500.00);
    m_priceSpin->setPrefix("₽ ");
    m_priceSpin->setDecimals(2);
    extraLayout->addRow("Цена:*", m_priceSpin);
    
    // Статус
    m_statusCombo = new QComboBox(this);
    m_statusCombo->addItems(QStringList() << "scheduled" << "departed" << "arrived" << "delayed" << "cancelled");
    extraLayout->addRow("Статус:", m_statusCombo);
    
    extraGroup->setLayout(extraLayout);
    mainLayout->addWidget(extraGroup);
    
    // Информационные метки
    m_routeInfoLabel = new QLabel("", this);
    m_routeInfoLabel->setStyleSheet("color: gray; font-size: 9pt;");
    mainLayout->addWidget(m_routeInfoLabel);
    
    m_trainInfoLabel = new QLabel("", this);
    m_trainInfoLabel->setStyleSheet("color: gray; font-size: 9pt;");
    mainLayout->addWidget(m_trainInfoLabel);
    
    m_wagonTypeInfoLabel = new QLabel("", this);
    m_wagonTypeInfoLabel->setStyleSheet("color: gray; font-size: 9pt;");
    mainLayout->addWidget(m_wagonTypeInfoLabel);
    
    // Примечание
    QLabel *noteLabel = new QLabel("* - обязательные поля", this);
    noteLabel->setStyleSheet("color: gray; font-size: 10pt;");
    mainLayout->addWidget(noteLabel);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_okButton = new QPushButton(m_scheduleId == 0 ? "Добавить" : "Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Загружаем данные в комбобоксы
    loadComboBoxData();
    
    // Подключаем сигналы
    connect(m_okButton, &QPushButton::clicked, this, &AddScheduleDialog::validateAndAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_departureDateEdit, &QDateEdit::dateChanged, this, &AddScheduleDialog::updateArrivalDate);
    connect(m_departureTimeEdit, &QTimeEdit::timeChanged, this, &AddScheduleDialog::updateArrivalDate);
    
    // Валидация
    auto validateFields = [this]() {
        bool valid = m_routeCombo->currentIndex() >= 0 &&
                    m_trainCombo->currentIndex() >= 0 &&
                    m_wagonTypeCombo->currentIndex() >= 0;
        
        m_okButton->setEnabled(valid);
    };
    
    connect(m_routeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), validateFields);
    connect(m_trainCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), validateFields);
    connect(m_wagonTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), validateFields);
    
    m_okButton->setEnabled(false);
    setMinimumWidth(500);
}

void AddScheduleDialog::loadComboBoxData()
{
    // Загружаем маршруты
    QSqlQuery routeQuery("SELECT id, departure_city || ' - ' || arrival_city FROM routes WHERE status = 'active' ORDER BY departure_city");
    while (routeQuery.next()) {
        m_routeCombo->addItem(routeQuery.value(1).toString(), routeQuery.value(0));
    }
    
    // Загружаем поезды
    QSqlQuery trainQuery("SELECT id, name FROM trains WHERE status = 'active' ORDER BY name");
    while (trainQuery.next()) {
        m_trainCombo->addItem(trainQuery.value(1).toString(), trainQuery.value(0));
    }
    
    // Загружаем типы вагонов
    QSqlQuery wagonQuery("SELECT id, name FROM wagon_types ORDER BY name");
    while (wagonQuery.next()) {
        m_wagonTypeCombo->addItem(wagonQuery.value(1).toString(), wagonQuery.value(0));
    }
}

void AddScheduleDialog::loadScheduleData(int scheduleId)
{
    QSqlQuery query;
    query.prepare("SELECT route_id, train_id, wagon_type_id, departure_date, departure_time, "
                  "arrival_date, arrival_time, available_seats, price, status "
                  "FROM schedule WHERE id = ?");
    query.addBindValue(scheduleId);
    
    if (query.exec() && query.next()) {
        // Устанавливаем значения в комбобоксы
        int routeId = query.value(0).toInt();
        int routeIndex = m_routeCombo->findData(routeId);
        if (routeIndex >= 0) {
            m_routeCombo->setCurrentIndex(routeIndex);
        }
        
        int trainId = query.value(1).toInt();
        int trainIndex = m_trainCombo->findData(trainId);
        if (trainIndex >= 0) {
            m_trainCombo->setCurrentIndex(trainIndex);
        }
        
        int wagonTypeId = query.value(2).toInt();
        int wagonIndex = m_wagonTypeCombo->findData(wagonTypeId);
        if (wagonIndex >= 0) {
            m_wagonTypeCombo->setCurrentIndex(wagonIndex);
        }
        
        // Устанавливаем даты и время
        m_departureDateEdit->setDate(query.value(3).toDate());
        m_departureTimeEdit->setTime(query.value(4).toTime());
        m_arrivalDateEdit->setDate(query.value(5).toDate());
        m_arrivalTimeEdit->setTime(query.value(6).toTime());
        
        // Остальные поля
        m_seatsSpin->setValue(query.value(7).toInt());
        m_priceSpin->setValue(query.value(8).toDouble());
        
        QString status = query.value(9).toString();
        int statusIndex = m_statusCombo->findText(status);
        if (statusIndex >= 0) {
            m_statusCombo->setCurrentIndex(statusIndex);
        }
        
        m_okButton->setEnabled(true);
    }
}

int AddScheduleDialog::getRouteId() const
{
    return m_routeCombo->currentData().toInt();
}

int AddScheduleDialog::getTrainId() const
{
    return m_trainCombo->currentData().toInt();
}

int AddScheduleDialog::getWagonTypeId() const
{
    return m_wagonTypeCombo->currentData().toInt();
}

void AddScheduleDialog::validateAndAccept()
{
    if (!validateDates()) {
        QMessageBox::warning(this, "Ошибка", 
            "Дата и время прибытия должны быть позже даты и времени отправления");
        return;
    }
    
    if (m_seatsSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Количество мест должно быть положительным");
        return;
    }
    
    if (m_priceSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Цена должна быть положительной");
        return;
    }
    
    accept();
}

bool AddScheduleDialog::validateDates()
{
    QDateTime departure(m_departureDateEdit->date(), m_departureTimeEdit->time());
    QDateTime arrival(m_arrivalDateEdit->date(), m_arrivalTimeEdit->time());
    
    return arrival > departure;
}

void AddScheduleDialog::calculatePrice()
{
    // Можно реализовать автоматический расчет цены на основе базовой цены маршрута
    // и коэффициента типа вагона
}

void AddScheduleDialog::updateArrivalDate()
{
    // Автоматически устанавливаем дату прибытия такую же как отправления
    // если она меньше
    if (m_arrivalDateEdit->date() < m_departureDateEdit->date()) {
        m_arrivalDateEdit->setDate(m_departureDateEdit->date());
    }
}