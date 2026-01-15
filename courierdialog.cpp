#include "courierdialog.h"
#include "ui_courierdialog.h"

#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QSqlQuery>

CourierDialog::CourierDialog(QSqlTableModel *model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CourierDialog)
    , m_model(model)
    , m_mapper(nullptr)
    , m_isEditMode(false)
{
    ui->setupUi(this);
    setupUI();
    setupValidators();
    ui->headerLabel->setText("Добавить нового курьера");
}

CourierDialog::CourierDialog(QSqlTableModel *model, int row, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CourierDialog)
    , m_model(model)
    , m_mapper(new QDataWidgetMapper(this))
    , m_isEditMode(true)
{
    ui->setupUi(this);
    setupUI();
    setupValidators();
    ui->headerLabel->setText("Редактировать курьера");
    m_mapper->setModel(m_model);
    m_mapper->addMapping(ui->lastNameEdit, 1);
    m_mapper->addMapping(ui->firstNameEdit, 2);
    m_mapper->addMapping(ui->patronymicEdit, 3);
    m_mapper->addMapping(ui->phoneEdit, 4);
    m_mapper->addMapping(ui->vehicleTypeCombo, 5);
    m_mapper->addMapping(ui->vehiclePlateEdit, 6);
    m_mapper->addMapping(ui->activeCheckBox, 7);
    m_mapper->setCurrentIndex(row);
}

CourierDialog::~CourierDialog()
{
    delete ui;
}

void CourierDialog::setupUI()
{
    QStringList vehicleTypes = {"Пеший", "Велосипед", "Мотоцикл", "Автомобиль"};
    ui->vehicleTypeCombo->addItems(vehicleTypes);
    ui->phoneEdit->setPlaceholderText("+79161234567");
    ui->vehiclePlateEdit->setPlaceholderText("А123ВС77");
    QPushButton *saveButton = ui->buttonBox->button(QDialogButtonBox::Save);
    QPushButton *cancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);
    if (saveButton) {
        saveButton->setText("Сохранить");
        connect(saveButton, &QPushButton::clicked, this, &CourierDialog::onSaveClicked);
    }
    if (cancelButton) {
        cancelButton->setText("Отмена");
        connect(cancelButton, &QPushButton::clicked, this, &CourierDialog::onCancelClicked);
    }
}

void CourierDialog::setupValidators()
{
    QRegularExpression nameRegex("^[А-ЯЁ][а-яё]*(-[А-ЯЁ][а-яё]*)?$");
    ui->lastNameEdit->setValidator(new QRegularExpressionValidator(nameRegex, this));
    ui->firstNameEdit->setValidator(new QRegularExpressionValidator(nameRegex, this));
    ui->patronymicEdit->setValidator(new QRegularExpressionValidator(nameRegex, this));
    QRegularExpression phoneRegex("^\\+7\\d{10}$");
    ui->phoneEdit->setValidator(new QRegularExpressionValidator(phoneRegex, this));
    QRegularExpression plateRegex("^[А-ЯA-Z]\\d{3}[А-ЯA-Z]{2}\\d{2,3}$");
    ui->vehiclePlateEdit->setValidator(new QRegularExpressionValidator(plateRegex, this));
}

bool CourierDialog::validateInput()
{
    if (ui->lastNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите фамилию");
        ui->lastNameEdit->setFocus();
        return false;
    }
    if (ui->firstNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя");
        ui->firstNameEdit->setFocus();
        return false;
    }
    if (!ui->phoneEdit->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Телефон должен быть в формате +7XXXXXXXXXX (11 цифр)");
        ui->phoneEdit->setFocus();
        return false;
    }
    if (!ui->vehiclePlateEdit->text().isEmpty() && !ui->vehiclePlateEdit->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Госномер должен быть в формате А123ВС77 или X123XX123");
        ui->vehiclePlateEdit->setFocus();
        return false;
    }
    return true;
}

void CourierDialog::onSaveClicked()
{
    if (!validateInput()) {
        return;
    }

    if (m_isEditMode && m_mapper) {
        // Сохраняем изменения через маппер
        m_mapper->submit();

        // Получаем текущий индекс из маппера
        int currentRow = m_mapper->currentIndex();

        if (currentRow >= 0 && currentRow < m_model->rowCount()) {
            // Обновляем значения в модели вручную
            QSqlRecord record = m_model->record(currentRow);
            record.setValue("last_name", ui->lastNameEdit->text());
            record.setValue("first_name", ui->firstNameEdit->text());
            record.setValue("patronymic",
                            ui->patronymicEdit->text().isEmpty() ? QVariant() : ui->patronymicEdit->text());
            record.setValue("phone", ui->phoneEdit->text());
            record.setValue("vehicle_type", ui->vehicleTypeCombo->currentText());
            record.setValue("vehicle_plate",
                            ui->vehiclePlateEdit->text().isEmpty() ? QVariant() : ui->vehiclePlateEdit->text());
            record.setValue("is_active", ui->activeCheckBox->isChecked());

            // Обновляем запись в модели
            m_model->setRecord(currentRow, record);
        }

        // Сохраняем изменения в БД
        if (!m_model->submitAll()) {
            QSqlError error = m_model->lastError();
            QString errorMsg = QString("Не удалось обновить данные:\n%1\n%2")
                                   .arg(error.databaseText())
                                   .arg(error.driverText());
            QMessageBox::critical(this, "Ошибка", errorMsg);
            return;
        }
    } else {
        QSqlQuery query(m_model->database());
        query.prepare("INSERT INTO couriers (last_name, first_name, patronymic, phone, vehicle_type, vehicle_plate, is_active) "
                      "VALUES (:last_name, :first_name, :patronymic, :phone, :vehicle_type, :vehicle_plate, :is_active)");
        query.bindValue(":last_name", ui->lastNameEdit->text());
        query.bindValue(":first_name", ui->firstNameEdit->text());
        query.bindValue(":patronymic", ui->patronymicEdit->text().isEmpty() ? QVariant() : ui->patronymicEdit->text());
        query.bindValue(":phone", ui->phoneEdit->text());
        query.bindValue(":vehicle_type", ui->vehicleTypeCombo->currentText());
        query.bindValue(":vehicle_plate", ui->vehiclePlateEdit->text().isEmpty() ? QVariant() : ui->vehiclePlateEdit->text());
        query.bindValue(":is_active", ui->activeCheckBox->isChecked());

        if (!query.exec()) {
            QSqlError error = query.lastError();
            QString errorMsg = QString("Не удалось добавить курьера:\n%1\n%2")
                                   .arg(error.databaseText())
                                   .arg(error.driverText());
            QMessageBox::critical(this, "Ошибка", errorMsg);
            return;
        }
    }

    accept();
}

void CourierDialog::onCancelClicked()
{
    reject();
}
