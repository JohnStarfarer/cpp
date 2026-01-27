#include "addroutedialog.h"
#include <QSqlQuery>
#include <QDebug>

AddRouteDialog::AddRouteDialog(QWidget *parent)
    : QDialog(parent)
    , m_routeId(0)
{
    setupUI();
    setWindowTitle("Добавить маршрут");
}

AddRouteDialog::AddRouteDialog(int routeId, QWidget *parent)
    : QDialog(parent)
    , m_routeId(routeId)
{
    setupUI();
    setWindowTitle("Редактировать маршрут");
    loadRouteData(routeId);
}

void AddRouteDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;
    
    // Пункт отправления
    m_departureEdit = new QLineEdit(this);
    m_departureEdit->setPlaceholderText("Например: Москва");
    formLayout->addRow("Пункт отправления:", m_departureEdit);
    
    // Пункт прибытия
    m_arrivalEdit = new QLineEdit(this);
    m_arrivalEdit->setPlaceholderText("Например: Санкт-Петербург");
    formLayout->addRow("Пункт прибытия:", m_arrivalEdit);
    
    // Дистанция
    m_distanceSpin = new QSpinBox(this);
    m_distanceSpin->setRange(0, 10000);
    m_distanceSpin->setValue(650);
    m_distanceSpin->setSuffix(" км");
    formLayout->addRow("Дистанция:", m_distanceSpin);
    
    // Базовая цена
    m_priceSpin = new QDoubleSpinBox(this);
    m_priceSpin->setRange(0, 100000);
    m_priceSpin->setValue(2500.00);
    m_priceSpin->setPrefix("₽ ");
    m_priceSpin->setDecimals(2);
    formLayout->addRow("Базовая цена:", m_priceSpin);
    
    // Статус
    m_statusCombo = new QComboBox(this);
    m_statusCombo->addItems(QStringList() << "active" << "inactive" << "seasonal" << "maintenance");
    formLayout->addRow("Статус:", m_statusCombo);
    
    mainLayout->addLayout(formLayout);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_okButton = new QPushButton(m_routeId == 0 ? "Добавить" : "Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Подключаем сигналы
    connect(m_okButton, &QPushButton::clicked, this, &AddRouteDialog::validateAndAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    // Валидация
    connect(m_departureEdit, &QLineEdit::textChanged, [this]() {
        bool valid = !m_departureEdit->text().isEmpty() && !m_arrivalEdit->text().isEmpty();
        m_okButton->setEnabled(valid);
    });
    
    connect(m_arrivalEdit, &QLineEdit::textChanged, [this]() {
        bool valid = !m_departureEdit->text().isEmpty() && !m_arrivalEdit->text().isEmpty();
        m_okButton->setEnabled(valid);
    });
    
    m_okButton->setEnabled(false);
    setMinimumWidth(400);
}

void AddRouteDialog::loadRouteData(int routeId)
{
    QSqlQuery query;
    query.prepare("SELECT departure_city, arrival_city, distance_km, base_price, status FROM routes WHERE id = ?");
    query.addBindValue(routeId);
    
    if (query.exec() && query.next()) {
        m_departureEdit->setText(query.value(0).toString());
        m_arrivalEdit->setText(query.value(1).toString());
        m_distanceSpin->setValue(query.value(2).toInt());
        m_priceSpin->setValue(query.value(3).toDouble());
        
        QString status = query.value(4).toString();
        int index = m_statusCombo->findText(status);
        if (index >= 0) {
            m_statusCombo->setCurrentIndex(index);
        }
        
        m_okButton->setEnabled(true);
    }
}

void AddRouteDialog::validateAndAccept()
{
    if (m_departureEdit->text().isEmpty() || m_arrivalEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните пункты отправления и прибытия");
        return;
    }
    
    if (m_departureEdit->text() == m_arrivalEdit->text()) {
        QMessageBox::warning(this, "Ошибка", "Пункты отправления и прибытия не должны совпадать");
        return;
    }
    
    if (m_priceSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Цена должна быть положительной");
        return;
    }
    
    accept();
}