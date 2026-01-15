#include "productdialog.h"
#include "ui_productdialog.h"
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

ProductDialog::ProductDialog(QSqlTableModel *model, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductDialog)
    , m_model(model)
    , m_mapper(nullptr)
    , m_isEditMode(false)
{
    ui->setupUi(this);
    setupUI();
    ui->headerLabel->setText("Добавить новый товар");
}

ProductDialog::ProductDialog(QSqlTableModel *model, int row, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductDialog)
    , m_model(model)
    , m_mapper(new QDataWidgetMapper(this))
    , m_isEditMode(true)
{
    ui->setupUi(this);
    setupUI();
    ui->headerLabel->setText("Редактировать товар");

    m_mapper->setModel(m_model);
    m_mapper->addMapping(ui->nameEdit, 1);
    m_mapper->addMapping(ui->descriptionEdit, 2);
    m_mapper->addMapping(ui->skuEdit, 3);
    m_mapper->addMapping(ui->quantitySpin, 4);
    m_mapper->addMapping(ui->unitEdit, 5);
    m_mapper->addMapping(ui->locationEdit, 6);
    m_mapper->addMapping(ui->reorderSpin, 7);
    m_mapper->addMapping(ui->priceSpin, 8);
    m_mapper->setCurrentIndex(row);
}

ProductDialog::~ProductDialog()
{
    delete ui;
}

void ProductDialog::setupUI()
{
    ui->unitEdit->setPlaceholderText("шт.");
    ui->locationEdit->setPlaceholderText("A-01");
    ui->skuEdit->setPlaceholderText("PROD-001");

    QPushButton *saveButton = ui->buttonBox->button(QDialogButtonBox::Save);
    QPushButton *cancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);

    if (saveButton) {
        saveButton->setText("Сохранить");
        connect(saveButton, &QPushButton::clicked, this, &ProductDialog::onSaveClicked);
    }
    if (cancelButton) {
        cancelButton->setText("Отмена");
        connect(cancelButton, &QPushButton::clicked, this, &ProductDialog::onCancelClicked);
    }
}

bool ProductDialog::validateInput()
{
    if (ui->nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название товара");
        ui->nameEdit->setFocus();
        return false;
    }

    if (ui->quantitySpin->value() < 0) {
        QMessageBox::warning(this, "Ошибка", "Количество не может быть отрицательным");
        ui->quantitySpin->setFocus();
        return false;
    }

    if (ui->priceSpin->value() < 0) {
        QMessageBox::warning(this, "Ошибка", "Цена не может быть отрицательной");
        ui->priceSpin->setFocus();
        return false;
    }

    return true;
}

void ProductDialog::onSaveClicked()
{
    if (!validateInput()) {
        return;
    }

    if (m_isEditMode && m_mapper) {
        int currentRow = m_mapper->currentIndex();

        if (currentRow >= 0) {
            QSqlQuery query(m_model->database());
            query.prepare("UPDATE products SET "
                          "name = :name, "
                          "description = :description, "
                          "sku = :sku, "
                          "quantity = :quantity, "
                          "unit = :unit, "
                          "location = :location, "
                          "reorder_level = :reorder_level, "
                          "price = :price "
                          "WHERE product_id = :id");

            query.bindValue(":name", ui->nameEdit->text());
            query.bindValue(":description", ui->descriptionEdit->toPlainText());
            query.bindValue(":sku", ui->skuEdit->text());
            query.bindValue(":quantity", ui->quantitySpin->value());
            query.bindValue(":unit", ui->unitEdit->text());
            query.bindValue(":location", ui->locationEdit->text());
            query.bindValue(":reorder_level", ui->reorderSpin->value());
            query.bindValue(":price", ui->priceSpin->value());
            query.bindValue(":id", m_model->data(m_model->index(currentRow, 0)));

            if (!query.exec()) {
                QMessageBox::critical(this, "Ошибка", "Не удалось обновить товар");
                return;
            }
        }
    } else {
        QSqlQuery query(m_model->database());
        query.prepare("INSERT INTO products (name, description, sku, quantity, unit, location, reorder_level, price) "
                      "VALUES (:name, :description, :sku, :quantity, :unit, :location, :reorder_level, :price)");

        query.bindValue(":name", ui->nameEdit->text());
        query.bindValue(":description", ui->descriptionEdit->toPlainText());
        query.bindValue(":sku", ui->skuEdit->text());
        query.bindValue(":quantity", ui->quantitySpin->value());
        query.bindValue(":unit", ui->unitEdit->text());
        query.bindValue(":location", ui->locationEdit->text());
        query.bindValue(":reorder_level", ui->reorderSpin->value());
        query.bindValue(":price", ui->priceSpin->value());

        if (!query.exec()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить товар");
            return;
        }
    }

    accept();
}

void ProductDialog::onCancelClicked()
{
    reject();
}
