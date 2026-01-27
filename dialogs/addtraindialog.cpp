#include "addtraindialog.h"
#include "../database.h"
#include <QSqlQuery>
#include <QDebug>

AddTrainDialog::AddTrainDialog(QWidget *parent)
    : QDialog(parent)
    , m_trainId(0)
{
    setupUI();
    setWindowTitle("Добавить поезд");
}

AddTrainDialog::AddTrainDialog(int trainId, QWidget *parent)
    : QDialog(parent)
    , m_trainId(trainId)
{
    setupUI();
    setWindowTitle("Редактировать поезд");
    loadTrainData(trainId);
}

void AddTrainDialog::setupUI()
{
    // layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Форма с полями
    QFormLayout *formLayout = new QFormLayout;
    
    // Название поезда
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText("Например: Сапсан-001");
    formLayout->addRow("Название поезда:", m_nameEdit);
    
    // Статус
    m_statusCombo = new QComboBox(this);
    m_statusCombo->addItems(QStringList() << "active" << "maintenance" << "inactive");
    formLayout->addRow("Статус:", m_statusCombo);
    
    // Количество мест
    m_seatsSpin = new QSpinBox(this);
    m_seatsSpin->setRange(1, 1000);
    m_seatsSpin->setValue(500);
    m_seatsSpin->setSuffix(" мест");
    formLayout->addRow("Всего мест:", m_seatsSpin);
    
    mainLayout->addLayout(formLayout);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_okButton = new QPushButton(m_trainId == 0 ? "Добавить" : "Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Подключаем сигналы
    connect(m_okButton, &QPushButton::clicked, this, &AddTrainDialog::validateAndAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    // Валидация при вводе
    connect(m_nameEdit, &QLineEdit::textChanged, [this](const QString &text) {
        m_okButton->setEnabled(!text.isEmpty());
    });
    
    m_okButton->setEnabled(false);
    setMinimumWidth(400);
}

void AddTrainDialog::loadTrainData(int trainId)
{
    QSqlQuery query;
    query.prepare("SELECT name, status, total_seats FROM trains WHERE id = ?");
    query.addBindValue(trainId);
    
    if (query.exec() && query.next()) {
        m_nameEdit->setText(query.value(0).toString());
        
        QString status = query.value(1).toString();
        int index = m_statusCombo->findText(status);
        if (index >= 0) {
            m_statusCombo->setCurrentIndex(index);
        }
        
        m_seatsSpin->setValue(query.value(2).toInt());
        m_okButton->setEnabled(true);
    }
}

void AddTrainDialog::validateAndAccept()
{
    if (m_nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название поезда");
        return;
    }
    
    if (m_seatsSpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Количество мест должно быть положительным");
        return;
    }
    
    accept();
}
