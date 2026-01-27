#include "addwagontypedialog.h"
#include <QSqlQuery>
#include <QDebug>

AddWagonTypeDialog::AddWagonTypeDialog(QWidget *parent)
    : QDialog(parent)
    , m_wagonTypeId(0)
{
    setupUI();
    setWindowTitle("Добавить тип вагона");
}

AddWagonTypeDialog::AddWagonTypeDialog(int wagonTypeId, QWidget *parent)
    : QDialog(parent)
    , m_wagonTypeId(wagonTypeId)
{
    setupUI();
    setWindowTitle("Редактировать тип вагона");
    loadWagonTypeData(wagonTypeId);
}

void AddWagonTypeDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Форма
    QFormLayout *formLayout = new QFormLayout;
    
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText("Например: Купе, Плацкарт, СВ");
    formLayout->addRow("Название типа:", m_nameEdit);
    
    m_capacitySpin = new QSpinBox(this);
    m_capacitySpin->setRange(1, 200);
    m_capacitySpin->setValue(54);
    m_capacitySpin->setSuffix(" мест");
    formLayout->addRow("Вместимость:", m_capacitySpin);
    
    m_descEdit = new QTextEdit(this);
    m_descEdit->setMaximumHeight(100);
    m_descEdit->setPlaceholderText("Описание типа вагона...");
    formLayout->addRow("Описание:", m_descEdit);
    
    mainLayout->addLayout(formLayout);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_okButton = new QPushButton(m_wagonTypeId == 0 ? "Добавить" : "Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Подключаем сигналы
    connect(m_okButton, &QPushButton::clicked, this, &AddWagonTypeDialog::validateAndAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    // Валидация
    connect(m_nameEdit, &QLineEdit::textChanged, [this](const QString &text) {
        m_okButton->setEnabled(!text.isEmpty());
    });
    
    m_okButton->setEnabled(false);
    setMinimumWidth(400);
}

void AddWagonTypeDialog::loadWagonTypeData(int wagonTypeId)
{
    QSqlQuery query;
    query.prepare("SELECT name, capacity, description FROM wagon_types WHERE id = ?");
    query.addBindValue(wagonTypeId);
    
    if (query.exec() && query.next()) {
        m_nameEdit->setText(query.value(0).toString());
        m_capacitySpin->setValue(query.value(1).toInt());
        m_descEdit->setText(query.value(2).toString());
        m_okButton->setEnabled(true);
    }
}

void AddWagonTypeDialog::validateAndAccept()
{
    if (m_nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название типа вагона");
        return;
    }
    
    if (m_capacitySpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Вместимость должна быть положительной");
        return;
    }
    
    accept();
}