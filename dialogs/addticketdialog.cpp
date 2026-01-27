#include "addticketdialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

AddTicketDialog::AddTicketDialog(QWidget *parent)
    : QDialog(parent)
    , m_ticketId(0)
{
    setupUI();
    setWindowTitle("Добавить билет");
}

AddTicketDialog::AddTicketDialog(int ticketId, QWidget *parent)
    : QDialog(parent)
    , m_ticketId(ticketId)
{
    setupUI();
    setWindowTitle("Редактировать билет");
    loadTicketData(ticketId);
}

void AddTicketDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Группа "Основные данные"
    QGroupBox *mainGroup = new QGroupBox("Основные данные", this);
    QFormLayout *formLayout = new QFormLayout(mainGroup);
    
    // Рейс
    m_scheduleCombo = new QComboBox(this);
    formLayout->addRow("Рейс:*", m_scheduleCombo);
    
    // Пассажир
    m_passengerCombo = new QComboBox(this);
    formLayout->addRow("Пассажир:*", m_passengerCombo);
    
    // Номер вагона и места
    QHBoxLayout *seatLayout = new QHBoxLayout;
    m_wagonSpin = new QSpinBox(this);
    m_wagonSpin->setRange(1, 20);
    m_wagonSpin->setValue(1);
    m_wagonSpin->setSuffix(" вагон");
    
    m_seatSpin = new QSpinBox(this);
    m_seatSpin->setRange(1, 100);
    m_seatSpin->setValue(1);
    m_seatSpin->setSuffix(" место");
    
    m_checkSeatButton = new QPushButton("Проверить", this);
    m_checkSeatButton->setMaximumWidth(80);
    
    seatLayout->addWidget(m_wagonSpin);
    seatLayout->addWidget(m_seatSpin);
    seatLayout->addWidget(m_checkSeatButton);
    formLayout->addRow("Место:", seatLayout);
    
    mainGroup->setLayout(formLayout);
    mainLayout->addWidget(mainGroup);
    
    // Групка "Стоимость и статус"
    QGroupBox *priceGroup = new QGroupBox("Стоимость и статус", this);
    QFormLayout *priceLayout = new QFormLayout(priceGroup);
    
    // Цена
    QHBoxLayout *priceRowLayout = new QHBoxLayout;
    m_priceSpin = new QDoubleSpinBox(this);
    m_priceSpin->setRange(0, 100000);
    m_priceSpin->setValue(2500.00);
    m_priceSpin->setPrefix("₽ ");
    m_priceSpin->setDecimals(2);
    
    m_autoPriceCheck = new QCheckBox("Авто", this);
    m_autoPriceCheck->setChecked(true);
    
    priceRowLayout->addWidget(m_priceSpin);
    priceRowLayout->addWidget(m_autoPriceCheck);
    priceLayout->addRow("Цена:*", priceRowLayout);
    
    // Статус
    m_statusCombo = new QComboBox(this);
    m_statusCombo->addItems(QStringList() << "active" << "cancelled" << "refunded" << "used");
    priceLayout->addRow("Статус:", m_statusCombo);
    
    priceGroup->setLayout(priceLayout);
    mainLayout->addWidget(priceGroup);
    
    // Информационные метки
    m_scheduleInfoLabel = new QLabel("", this);
    m_scheduleInfoLabel->setStyleSheet("color: gray; font-size: 9pt;");
    mainLayout->addWidget(m_scheduleInfoLabel);
    
    m_passengerInfoLabel = new QLabel("", this);
    m_passengerInfoLabel->setStyleSheet("color: gray; font-size: 9pt;");
    mainLayout->addWidget(m_passengerInfoLabel);
    
    m_seatStatusLabel = new QLabel("Статус места не проверен", this);
    m_seatStatusLabel->setStyleSheet("color: orange; font-size: 9pt;");
    mainLayout->addWidget(m_seatStatusLabel);
    
    m_availableSeatsLabel = new QLabel("", this);
    m_availableSeatsLabel->setStyleSheet("color: blue; font-size: 9pt;");
    mainLayout->addWidget(m_availableSeatsLabel);
    
    // Примечание
    QLabel *noteLabel = new QLabel("* - обязательные поля", this);
    noteLabel->setStyleSheet("color: gray; font-size: 10pt;");
    mainLayout->addWidget(noteLabel);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_okButton = new QPushButton(m_ticketId == 0 ? "Добавить" : "Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Загружаем данные в комбобоксы
    loadComboBoxData();
    
    // Подключаем сигналы
    connect(m_okButton, &QPushButton::clicked, this, &AddTicketDialog::validateAndAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_checkSeatButton, &QPushButton::clicked, this, &AddTicketDialog::checkSeatAvailability);
    connect(m_scheduleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddTicketDialog::onScheduleChanged);
    connect(m_passengerCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AddTicketDialog::onPassengerChanged);
    connect(m_autoPriceCheck, &QCheckBox::stateChanged, this, &AddTicketDialog::updatePrice);
    
    // Валидация
    auto validateFields = [this]() {
        bool valid = m_scheduleCombo->currentIndex() >= 0 &&
                    m_passengerCombo->currentIndex() >= 0;
        
        m_okButton->setEnabled(valid);
    };
    
    connect(m_scheduleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), validateFields);
    connect(m_passengerCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), validateFields);
    
    m_okButton->setEnabled(false);
    setMinimumWidth(500);
}

void AddTicketDialog::loadComboBoxData()
{
    // Загружаем расписание
    QSqlQuery scheduleQuery("SELECT s.id, r.departure_city || ' - ' || r.arrival_city || ' (' || "
                           "TO_CHAR(s.departure_date, 'DD.MM.YYYY') || ' ' || "
                           "TO_CHAR(s.departure_time, 'HH24:MI') || ')' "
                           "FROM schedule s "
                           "JOIN routes r ON s.route_id = r.id "
                           "WHERE s.available_seats > 0 AND s.status = 'scheduled' "
                           "ORDER BY s.departure_date, s.departure_time");
    
    while (scheduleQuery.next()) {
        m_scheduleCombo->addItem(scheduleQuery.value(1).toString(), scheduleQuery.value(0));
    }
    
    // Загружаем пассажиров
    QSqlQuery passengerQuery("SELECT id, last_name || ' ' || first_name || ' ' || COALESCE(middle_name, '') "
                            "FROM passengers ORDER BY last_name, first_name");
    
    while (passengerQuery.next()) {
        m_passengerCombo->addItem(passengerQuery.value(1).toString().trimmed(), passengerQuery.value(0));
    }
}

void AddTicketDialog::loadTicketData(int ticketId)
{
    QSqlQuery query;
    query.prepare("SELECT schedule_id, passenger_id, wagon_number, seat_number, price, status "
                  "FROM tickets WHERE id = ?");
    query.addBindValue(ticketId);
    
    if (query.exec() && query.next()) {
        // Устанавливаем значения в комбобоксы
        int scheduleId = query.value(0).toInt();
        int scheduleIndex = m_scheduleCombo->findData(scheduleId);
        if (scheduleIndex >= 0) {
            m_scheduleCombo->setCurrentIndex(scheduleIndex);
        }
        
        int passengerId = query.value(1).toInt();
        int passengerIndex = m_passengerCombo->findData(passengerId);
        if (passengerIndex >= 0) {
            m_passengerCombo->setCurrentIndex(passengerIndex);
        }
        
        // Остальные поля
        m_wagonSpin->setValue(query.value(2).toInt());
        m_seatSpin->setValue(query.value(3).toInt());
        m_priceSpin->setValue(query.value(4).toDouble());
        m_autoPriceCheck->setChecked(false);
        
        QString status = query.value(5).toString();
        int statusIndex = m_statusCombo->findText(status);
        if (statusIndex >= 0) {
            m_statusCombo->setCurrentIndex(statusIndex);
        }
        
        m_okButton->setEnabled(true);
    }
}

int AddTicketDialog::getScheduleId() const
{
    return m_scheduleCombo->currentData().toInt();
}

int AddTicketDialog::getPassengerId() const
{
    return m_passengerCombo->currentData().toInt();
}

void AddTicketDialog::validateAndAccept()
{
    if (m_wagonSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Номер вагона должен быть положительным");
        return;
    }
    
    if (m_seatSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Номер места должен быть положительным");
        return;
    }
    
    if (m_priceSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Цена должна быть положительной");
        return;
    }
    
    // Проверяем доступность места
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM tickets "
                  "WHERE schedule_id = ? AND wagon_number = ? AND seat_number = ? "
                  "AND status = 'active'");
    query.addBindValue(getScheduleId());
    query.addBindValue(m_wagonSpin->value());
    query.addBindValue(m_seatSpin->value());
    
    if (query.exec() && query.next() && query.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Ошибка", 
            "Это место уже занято. Пожалуйста, выберите другое место.");
        return;
    }
    
    accept();
}

void AddTicketDialog::checkSeatAvailability()
{
    int scheduleId = getScheduleId();
    int wagonNumber = m_wagonSpin->value();
    int seatNumber = m_seatSpin->value();
    
    if (scheduleId <= 0) {
        m_seatStatusLabel->setText("Сначала выберите рейс");
        m_seatStatusLabel->setStyleSheet("color: orange;");
        return;
    }
    
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM tickets "
                  "WHERE schedule_id = ? AND wagon_number = ? AND seat_number = ? "
                  "AND status = 'active'");
    query.addBindValue(scheduleId);
    query.addBindValue(wagonNumber);
    query.addBindValue(seatNumber);
    
    if (query.exec() && query.next()) {
        if (query.value(0).toInt() > 0) {
            m_seatStatusLabel->setText("❌ Место уже занято");
            m_seatStatusLabel->setStyleSheet("color: red; font-weight: bold;");
        } else {
            m_seatStatusLabel->setText("✅ Место свободно");
            m_seatStatusLabel->setStyleSheet("color: green; font-weight: bold;");
        }
    }
}

void AddTicketDialog::onScheduleChanged()
{
    int scheduleId = getScheduleId();
    if (scheduleId <= 0) return;
    
    // Получаем информацию о рейсе
    QSqlQuery query;
    query.prepare("SELECT r.departure_city || ' - ' || r.arrival_city || ', ' || "
                  "TO_CHAR(s.departure_date, 'DD.MM.YYYY') || ' ' || "
                  "TO_CHAR(s.departure_time, 'HH24:MI') || ', ' || "
                  "t.name || ', ' || wt.name || ', цена: ' || s.price || '₽' "
                  "FROM schedule s "
                  "JOIN routes r ON s.route_id = r.id "
                  "JOIN trains t ON s.train_id = t.id "
                  "JOIN wagon_types wt ON s.wagon_type_id = wt.id "
                  "WHERE s.id = ?");
    query.addBindValue(scheduleId);
    
    if (query.exec() && query.next()) {
        m_scheduleInfoLabel->setText("Рейс: " + query.value(0).toString());
    }
    
    // Обновляем доступные места
    updateAvailableSeats();
    
    // Обновляем цену если включен авторежим
    if (m_autoPriceCheck->isChecked()) {
        updatePrice();
    }
}

void AddTicketDialog::onPassengerChanged()
{
    int passengerId = getPassengerId();
    if (passengerId <= 0) return;
    
    QSqlQuery query;
    query.prepare("SELECT last_name || ' ' || first_name || ' ' || COALESCE(middle_name, '') || ', ' || "
                  "document_type || ': ' || document_number "
                  "FROM passengers WHERE id = ?");
    query.addBindValue(passengerId);
    
    if (query.exec() && query.next()) {
        m_passengerInfoLabel->setText("Пассажир: " + query.value(0).toString());
    }
}

void AddTicketDialog::updatePrice()
{
    if (!m_autoPriceCheck->isChecked()) return;
    
    int scheduleId = getScheduleId();
    if (scheduleId <= 0) return;
    
    QSqlQuery query;
    query.prepare("SELECT price FROM schedule WHERE id = ?");
    query.addBindValue(scheduleId);
    
    if (query.exec() && query.next()) {
        m_priceSpin->setValue(query.value(0).toDouble());
    }
}

void AddTicketDialog::updateAvailableSeats()
{
    int scheduleId = getScheduleId();
    if (scheduleId <= 0) return;
    
    QSqlQuery query;
    query.prepare("SELECT available_seats FROM schedule WHERE id = ?");
    query.addBindValue(scheduleId);
    
    if (query.exec() && query.next()) {
        int available = query.value(0).toInt();
        m_availableSeatsLabel->setText(QString("Свободных мест: %1").arg(available));
        
        if (available <= 0) {
            m_availableSeatsLabel->setStyleSheet("color: red; font-weight: bold;");
        } else if (available <= 10) {
            m_availableSeatsLabel->setStyleSheet("color: orange; font-weight: bold;");
        } else {
            m_availableSeatsLabel->setStyleSheet("color: green;");
        }
    }
}