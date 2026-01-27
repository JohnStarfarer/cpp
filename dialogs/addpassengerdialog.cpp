#include "addpassengerdialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

AddPassengerDialog::AddPassengerDialog(QWidget *parent)
    : QDialog(parent)
    , m_passengerId(0)
{
    setupUI();
    setWindowTitle("Добавить пассажира");
}

AddPassengerDialog::AddPassengerDialog(int passengerId, QWidget *parent)
    : QDialog(parent)
    , m_passengerId(passengerId)
{
    setupUI();
    setWindowTitle("Редактировать пассажира");
    loadPassengerData(passengerId);
}

void AddPassengerDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;
    
    // ФИО
    m_lastNameEdit = new QLineEdit(this);
    m_lastNameEdit->setPlaceholderText("Иванов");
    formLayout->addRow("Фамилия:*", m_lastNameEdit);
    
    m_firstNameEdit = new QLineEdit(this);
    m_firstNameEdit->setPlaceholderText("Иван");
    formLayout->addRow("Имя:*", m_firstNameEdit);
    
    m_middleNameEdit = new QLineEdit(this);
    m_middleNameEdit->setPlaceholderText("Иванович (необязательно)");
    formLayout->addRow("Отчество:", m_middleNameEdit);
    
    // Дата рождения
    m_birthDateEdit = new QDateEdit(this);
    m_birthDateEdit->setCalendarPopup(true);
    m_birthDateEdit->setDate(QDate::currentDate().addYears(-30));
    m_birthDateEdit->setMaximumDate(QDate::currentDate());
    m_birthDateEdit->setDisplayFormat("dd.MM.yyyy");
    formLayout->addRow("Дата рождения:*", m_birthDateEdit);
    
    // Пол
    m_genderCombo = new QComboBox(this);
    m_genderCombo->addItems(QStringList() << "М" << "Ж");
    formLayout->addRow("Пол:*", m_genderCombo);
    
    // Тип документа
    m_docTypeCombo = new QComboBox(this);
    m_docTypeCombo->addItems(QStringList() << "паспорт" << "загранпаспорт" << "свидетельство о рождении");
    formLayout->addRow("Тип документа:*", m_docTypeCombo);
    
    // Номер документа
    m_docNumberEdit = new QLineEdit(this);
    m_docNumberEdit->setPlaceholderText("4510123456");
    formLayout->addRow("Номер документа:*", m_docNumberEdit);
    
    // Телефон
    m_phoneEdit = new QLineEdit(this);
    m_phoneEdit->setPlaceholderText("+79161234567");
    m_phoneEdit->setInputMask("+7(999)999-99-99");
    formLayout->addRow("Телефон:", m_phoneEdit);
    
    // Email
    m_emailEdit = new QLineEdit(this);
    m_emailEdit->setPlaceholderText("example@mail.ru");
    formLayout->addRow("Email:", m_emailEdit);
    
    mainLayout->addLayout(formLayout);
    
    // Примечание
    QLabel *noteLabel = new QLabel("* - обязательные поля", this);
    noteLabel->setStyleSheet("color: gray; font-size: 10pt;");
    mainLayout->addWidget(noteLabel);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_okButton = new QPushButton(m_passengerId == 0 ? "Добавить" : "Сохранить", this);
    m_cancelButton = new QPushButton("Отмена", this);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Подключаем сигналы
    connect(m_okButton, &QPushButton::clicked, this, &AddPassengerDialog::validateAndAccept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    // Валидация
    auto validateFields = [this]() {
        bool valid = !m_lastNameEdit->text().isEmpty() &&
                    !m_firstNameEdit->text().isEmpty() &&
                    !m_docNumberEdit->text().isEmpty() &&
                    m_birthDateEdit->date().isValid();
        
        m_okButton->setEnabled(valid);
    };
    
    connect(m_lastNameEdit, &QLineEdit::textChanged, validateFields);
    connect(m_firstNameEdit, &QLineEdit::textChanged, validateFields);
    connect(m_docNumberEdit, &QLineEdit::textChanged, validateFields);
    
    m_okButton->setEnabled(false);
    setMinimumWidth(450);
}

void AddPassengerDialog::loadPassengerData(int passengerId)
{
    QSqlQuery query;
    query.prepare("SELECT last_name, first_name, middle_name, birth_date, gender, "
                  "document_type, document_number, phone, email FROM passengers WHERE id = ?");
    query.addBindValue(passengerId);
    
    if (query.exec() && query.next()) {
        m_lastNameEdit->setText(query.value(0).toString());
        m_firstNameEdit->setText(query.value(1).toString());
        m_middleNameEdit->setText(query.value(2).toString());
        m_birthDateEdit->setDate(query.value(3).toDate());
        
        QString gender = query.value(4).toString();
        int genderIndex = m_genderCombo->findText(gender);
        if (genderIndex >= 0) {
            m_genderCombo->setCurrentIndex(genderIndex);
        }
        
        QString docType = query.value(5).toString();
        int docTypeIndex = m_docTypeCombo->findText(docType);
        if (docTypeIndex >= 0) {
            m_docTypeCombo->setCurrentIndex(docTypeIndex);
        }
        
        m_docNumberEdit->setText(query.value(6).toString());
        m_phoneEdit->setText(query.value(7).toString());
        m_emailEdit->setText(query.value(8).toString());
        
        m_okButton->setEnabled(true);
    }
}

void AddPassengerDialog::validateAndAccept()
{
    // Проверка ФИО
    if (m_lastNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите фамилию");
        return;
    }
    
    if (m_firstNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя");
        return;
    }
    
    // Проверка даты рождения (только совершеннолетние)
    int age = m_birthDateEdit->date().daysTo(QDate::currentDate()) / 365;
    if (age < 18) {
        QMessageBox::warning(this, "Ошибка", "Пассажир должен быть совершеннолетним (18+)");
        return;
    }
    
    // Проверка номера документа
    if (m_docNumberEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите номер документа");
        return;
    }
    
    // Проверка email (если указан)
    if (!m_emailEdit->text().isEmpty() && !isValidEmail(m_emailEdit->text())) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат email");
        return;
    }
    
    // Проверка телефона (если указан)
    if (!m_phoneEdit->text().isEmpty() && !isValidPhone(m_phoneEdit->text())) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат телефона");
        return;
    }
    
    accept();
}

bool AddPassengerDialog::isValidEmail(const QString &email)
{
    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex.match(email).hasMatch();
}

bool AddPassengerDialog::isValidPhone(const QString &phone)
{
    // Убираем все символы кроме цифр и проверяем длину
    QString digits = phone;
    digits.remove(QRegularExpression("[^0-9]"));
    return digits.length() >= 10;
}