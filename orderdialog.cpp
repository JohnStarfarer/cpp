#include "orderdialog.h"
#include "ui_orderdialog.h"
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>

OrderDialog::OrderDialog(QSqlRelationalTableModel *model, QWidget *parent)
    : QDialog(parent), ui(new Ui::OrderDialog), m_orderModel(model), m_isEditMode(false), m_currentOrderId(-1)
{
    ui->setupUi(this);
    setupUI();
    ui->headerLabel->setText("Создать новый заказ");
    loadCouriers();
    loadProducts();
}

OrderDialog::OrderDialog(QSqlRelationalTableModel *model, int row, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OrderDialog)
    , m_orderModel(model)
    , m_isEditMode(true)
    , m_currentOrderId(model->data(model->index(row, 0)).toInt())
{
    ui->setupUi(this);
    setupUI();
    ui->headerLabel->setText("Редактировать заказ");

    QSqlRecord record = m_orderModel->record(row);
    ui->customerNameEdit->setText(record.value("customer_name").toString());
    ui->customerPhoneEdit->setText(record.value("customer_phone").toString());
    ui->customerAddressEdit->setPlainText(record.value("customer_address").toString());
    ui->statusCombo->setCurrentText(record.value("status").toString());
    ui->quantitySpin->setValue(record.value("quantity").toInt());

    loadCouriers();
    loadProducts();

    int productId = record.value("product_id").toInt();
    for (int i = 0; i < ui->productCombo->count(); ++i) {
        if (ui->productCombo->itemData(i).toInt() == productId) {
            ui->productCombo->setCurrentIndex(i);
            break;
        }
    }

    int courierId = record.value("assigned_courier_id").toInt();
    for (int i = 0; i < ui->courierCombo->count(); ++i) {
        if (ui->courierCombo->itemData(i).toInt() == courierId) {
            ui->courierCombo->setCurrentIndex(i);
            break;
        }
    }

    calculateTotal();
}

OrderDialog::~OrderDialog()
{
    delete ui;
}

void OrderDialog::setupUI()
{
    QStringList statuses = {"новый", "в обработке", "собирается", "готов к отправке", "в пути", "доставлен", "отменен"};
    ui->statusCombo->addItems(statuses);

    QPushButton *saveButton = ui->buttonBox->button(QDialogButtonBox::Save);
    QPushButton *cancelButton = ui->buttonBox->button(QDialogButtonBox::Cancel);

    if (saveButton) {
        saveButton->setText("Сохранить");
        connect(saveButton, &QPushButton::clicked, this, &OrderDialog::onSaveClicked);
    }
    if (cancelButton) {
        cancelButton->setText("Отмена");
        connect(cancelButton, &QPushButton::clicked, this, &OrderDialog::onCancelClicked);
    }

    connect(ui->productCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &OrderDialog::onProductSelected);
    connect(ui->quantitySpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &OrderDialog::calculateTotal);
}

void OrderDialog::loadCouriers()
{
    ui->courierCombo->clear();
    ui->courierCombo->addItem("Не назначен", QVariant());

    QSqlQuery query;
    query.prepare("SELECT courier_id, last_name || ' ' || first_name FROM couriers WHERE is_active = TRUE ORDER BY last_name");
    if (query.exec()) {
        while (query.next()) {
            ui->courierCombo->addItem(query.value(1).toString(), query.value(0));
        }
    }
}

void OrderDialog::loadProducts()
{
    ui->productCombo->clear();

    QSqlQuery query;
    query.prepare("SELECT product_id, name, quantity, price FROM products WHERE quantity > 0 ORDER BY name");
    if (query.exec()) {
        while (query.next()) {
            QString text = QString("%1 (остаток: %2, цена: %3 руб.)")
                               .arg(query.value(1).toString())
                               .arg(query.value(2).toInt())
                               .arg(query.value(3).toDouble());
            ui->productCombo->addItem(text, query.value(0));
        }
    }
}

double OrderDialog::getProductPrice(int productId)
{
    QSqlQuery query;
    query.prepare("SELECT price FROM products WHERE product_id = :id");
    query.bindValue(":id", productId);
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

void OrderDialog::onProductSelected(int index)
{
    if (index < 0) return;

    int productId = ui->productCombo->itemData(index).toInt();
    QSqlQuery query;
    query.prepare("SELECT quantity FROM products WHERE product_id = :id");
    query.bindValue(":id", productId);
    if (query.exec() && query.next()) {
        int available = query.value(0).toInt();
        ui->quantitySpin->setMaximum(available);
        ui->priceLabel->setText(QString("Цена: %1 руб.").arg(getProductPrice(productId)));
    }
    calculateTotal();
}

void OrderDialog::calculateTotal()
{
    int productIndex = ui->productCombo->currentIndex();
    if (productIndex < 0) {
        ui->totalLabel->setText("Итого: 0 руб.");
        return;
    }

    int productId = ui->productCombo->itemData(productIndex).toInt();
    double price = getProductPrice(productId);
    int quantity = ui->quantitySpin->value();
    double total = price * quantity;

    ui->totalLabel->setText(QString("Итого: %1 руб.").arg(total, 0, 'f', 2));
}

bool OrderDialog::validateInput()
{
    if (ui->customerNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя заказчика");
        ui->customerNameEdit->setFocus();
        return false;
    }
    if (ui->customerPhoneEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите телефон заказчика");
        ui->customerPhoneEdit->setFocus();
        return false;
    }
    if (ui->customerAddressEdit->toPlainText().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите адрес доставки");
        ui->customerAddressEdit->setFocus();
        return false;
    }
    if (ui->productCombo->currentIndex() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите товар");
        return false;
    }
    if (ui->quantitySpin->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Количество должно быть больше 0");
        ui->quantitySpin->setFocus();
        return false;
    }
    return true;
}

void OrderDialog::onSaveClicked()
{
    if (!validateInput()) {
        return;
    }

    QSqlDatabase db = m_orderModel->database();
    db.transaction();

    try {
        int productId = ui->productCombo->itemData(ui->productCombo->currentIndex()).toInt();
        int quantity = ui->quantitySpin->value();
        double price = getProductPrice(productId);

        if (m_isEditMode) {
            // Получаем старые данные для восстановления остатков
            QSqlQuery oldQuery;
            oldQuery.prepare("SELECT product_id, quantity FROM order_items WHERE order_id = :id");
            oldQuery.bindValue(":id", m_currentOrderId);
            if (oldQuery.exec() && oldQuery.next()) {
                int oldProductId = oldQuery.value(0).toInt();
                int oldQuantity = oldQuery.value(1).toInt();

                // Вернуть старый товар на склад
                QSqlQuery returnQuery;
                returnQuery.prepare("UPDATE products SET quantity = quantity + :quantity WHERE product_id = :id");
                returnQuery.bindValue(":quantity", oldQuantity);
                returnQuery.bindValue(":id", oldProductId);
                if (!returnQuery.exec()) {
                    throw std::runtime_error("Не удалось вернуть старый товар на склад: " + returnQuery.lastError().text().toStdString());
                }
            }

            QSqlQuery query;
            query.prepare("UPDATE order_items SET "
                          "customer_name = :name, "
                          "customer_phone = :phone, "
                          "customer_address = :address, "
                          "product_id = :product_id, "
                          "quantity = :quantity, "
                          "price = :price, "
                          "status = :status, "
                          "assigned_courier_id = :courier_id "
                          "WHERE order_id = :id");

            query.bindValue(":name", ui->customerNameEdit->text());
            query.bindValue(":phone", ui->customerPhoneEdit->text());
            query.bindValue(":address", ui->customerAddressEdit->toPlainText());
            query.bindValue(":product_id", productId);
            query.bindValue(":quantity", quantity);
            query.bindValue(":price", price);
            query.bindValue(":status", ui->statusCombo->currentText());
            query.bindValue(":courier_id", ui->courierCombo->currentData().isNull() ? QVariant() : ui->courierCombo->currentData());
            query.bindValue(":id", m_currentOrderId);

            if (!query.exec()) {
                throw std::runtime_error("Не удалось обновить заказ: " + query.lastError().text().toStdString());
            }
        } else {
            QSqlQuery query;
            query.prepare("INSERT INTO order_items (customer_name, customer_phone, customer_address, product_id, quantity, price, status, assigned_courier_id) "
                          "VALUES (:name, :phone, :address, :product_id, :quantity, :price, :status, :courier_id) RETURNING order_id");

            query.bindValue(":name", ui->customerNameEdit->text());
            query.bindValue(":phone", ui->customerPhoneEdit->text());
            query.bindValue(":address", ui->customerAddressEdit->toPlainText());
            query.bindValue(":product_id", productId);
            query.bindValue(":quantity", quantity);
            query.bindValue(":price", price);
            query.bindValue(":status", ui->statusCombo->currentText());
            query.bindValue(":courier_id", ui->courierCombo->currentData().isNull() ? QVariant() : ui->courierCombo->currentData());

            if (!query.exec()) {
                throw std::runtime_error("Не удалось создать заказ: " + query.lastError().text().toStdString());
            }

            if (!query.next()) {
                throw std::runtime_error("Не удалось получить ID созданного заказа");
            }

            m_currentOrderId = query.value(0).toInt();
        }

        // Обновляем остатки на складе (вычитаем количество)
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE products SET quantity = quantity - :quantity WHERE product_id = :id");
        updateQuery.bindValue(":quantity", quantity);
        updateQuery.bindValue(":id", productId);
        if (!updateQuery.exec()) {
            throw std::runtime_error("Не удалось обновить остатки товара: " + updateQuery.lastError().text().toStdString());
        }

        db.commit();
        qDebug() << "Заказ успешно сохранен, ID:" << m_currentOrderId;
    } catch (const std::exception &e) {
        db.rollback();
        QMessageBox::critical(this, "Ошибка", QString::fromStdString(e.what()));
        qDebug() << "Ошибка при сохранении заказа:" << e.what();
        return;
    }

    accept();
}

void OrderDialog::onCancelClicked()
{
    reject();
}
