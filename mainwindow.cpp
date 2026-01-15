#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"
#include "courierdialog.h"
#include "productdialog.h"
#include "orderdialog.h"

#include <QTableView>
#include <QMessageBox>
#include <QSqlError>
#include <QMenuBar>
#include <QStatusBar>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_courierModel(nullptr)
    , m_productModel(nullptr)
    , m_orderModel(nullptr)
{
    ui->setupUi(this);

    QMenu *fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction("Выход", this, &QMainWindow::close);

    QMenu *helpMenu = menuBar()->addMenu("Справка");
    helpMenu->addAction("О программе", []() {
        QMessageBox::about(nullptr, "О программе", "Курьер Менеджер v1.0");
    });

    statusBar()->showMessage("Готово");
    setupModels();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModels()
{
    // Модель для курьеров
    m_courierModel = new QSqlTableModel(this, DatabaseManager::instance().database());
    m_courierModel->setTable("couriers");
    m_courierModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_courierModel->select();

    m_courierModel->setHeaderData(1, Qt::Horizontal, "Фамилия");
    m_courierModel->setHeaderData(2, Qt::Horizontal, "Имя");
    m_courierModel->setHeaderData(3, Qt::Horizontal, "Отчество");
    m_courierModel->setHeaderData(4, Qt::Horizontal, "Телефон");
    m_courierModel->setHeaderData(5, Qt::Horizontal, "Транспорт");
    m_courierModel->setHeaderData(6, Qt::Horizontal, "Номер");
    m_courierModel->setHeaderData(7, Qt::Horizontal, "Активен");
    m_courierModel->setHeaderData(8, Qt::Horizontal, "Дата регистрации");

    ui->courierTableView->setModel(m_courierModel);
    ui->courierTableView->hideColumn(0);
    ui->courierTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->courierTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->courierTableView->setAlternatingRowColors(true);
    ui->courierTableView->horizontalHeader()->setStretchLastSection(true);
    ui->courierTableView->setSortingEnabled(true);

    // Модель для товаров
    m_productModel = new QSqlTableModel(this, DatabaseManager::instance().database());
    m_productModel->setTable("products");
    m_productModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_productModel->select();

    m_productModel->setHeaderData(1, Qt::Horizontal, "Название");
    m_productModel->setHeaderData(2, Qt::Horizontal, "Описание");
    m_productModel->setHeaderData(3, Qt::Horizontal, "Артикул");
    m_productModel->setHeaderData(4, Qt::Horizontal, "Количество");
    m_productModel->setHeaderData(5, Qt::Horizontal, "Ед. изм.");
    m_productModel->setHeaderData(6, Qt::Horizontal, "Место");
    m_productModel->setHeaderData(7, Qt::Horizontal, "Порог");
    m_productModel->setHeaderData(8, Qt::Horizontal, "Цена");

    ui->productTableView->setModel(m_productModel);
    ui->productTableView->hideColumn(0);
    ui->productTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->productTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->productTableView->setAlternatingRowColors(true);
    ui->productTableView->horizontalHeader()->setStretchLastSection(true);
    ui->productTableView->setSortingEnabled(true);

    // Модель для заказов (теперь это order_items)
    m_orderModel = new QSqlRelationalTableModel(this, DatabaseManager::instance().database());
    m_orderModel->setTable("order_items");
    m_orderModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    m_orderModel->setRelation(4, QSqlRelation("products", "product_id", "name"));
    m_orderModel->setRelation(8, QSqlRelation("couriers", "courier_id", "last_name"));

    m_orderModel->setHeaderData(1, Qt::Horizontal, "Заказчик");
    m_orderModel->setHeaderData(2, Qt::Horizontal, "Телефон");
    m_orderModel->setHeaderData(3, Qt::Horizontal, "Адрес");
    m_orderModel->setHeaderData(4, Qt::Horizontal, "Товар");
    m_orderModel->setHeaderData(5, Qt::Horizontal, "Количество");
    m_orderModel->setHeaderData(6, Qt::Horizontal, "Цена");
    m_orderModel->setHeaderData(7, Qt::Horizontal, "Статус");
    m_orderModel->setHeaderData(8, Qt::Horizontal, "Курьер");
    m_orderModel->setHeaderData(9, Qt::Horizontal, "Сумма");
    m_orderModel->setHeaderData(10, Qt::Horizontal, "Создан");

    m_orderModel->select();

    ui->orderTableView->setModel(m_orderModel);
    ui->orderTableView->hideColumn(0);
    ui->orderTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->orderTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->orderTableView->setAlternatingRowColors(true);
    ui->orderTableView->horizontalHeader()->setStretchLastSection(true);
    ui->orderTableView->setSortingEnabled(true);
}

void MainWindow::setupConnections()
{
    // Курьеры
    connect(ui->addCourierButton, &QPushButton::clicked, this, &MainWindow::onAddCourier);
    connect(ui->editCourierButton, &QPushButton::clicked, this, &MainWindow::onEditCourier);
    connect(ui->deleteCourierButton, &QPushButton::clicked, this, &MainWindow::onDeleteCourier);
    connect(ui->refreshCourierButton, &QPushButton::clicked, this, &MainWindow::refreshCouriers);
    connect(ui->activeCourierCheck, &QCheckBox::checkStateChanged, this, &MainWindow::filterCouriersByActive);
    connect(ui->searchCourierEdit, &QLineEdit::textChanged, this, &MainWindow::searchCouriers);

    // Товары
    connect(ui->addProductButton, &QPushButton::clicked, this, &MainWindow::onAddProduct);
    connect(ui->editProductButton, &QPushButton::clicked, this, &MainWindow::onEditProduct);
    connect(ui->deleteProductButton, &QPushButton::clicked, this, &MainWindow::onDeleteProduct);
    connect(ui->refreshProductButton, &QPushButton::clicked, this, &MainWindow::refreshProducts);
    connect(ui->searchProductEdit, &QLineEdit::textChanged, this, &MainWindow::searchProducts);

    // Заказы
    connect(ui->addOrderButton, &QPushButton::clicked, this, &MainWindow::onAddOrder);
    connect(ui->editOrderButton, &QPushButton::clicked, this, &MainWindow::onEditOrder);
    connect(ui->deleteOrderButton, &QPushButton::clicked, this, &MainWindow::onDeleteOrder);
    connect(ui->refreshOrderButton, &QPushButton::clicked, this, &MainWindow::refreshOrders);
    connect(ui->searchOrderEdit, &QLineEdit::textChanged, this, &MainWindow::searchOrders);
    connect(ui->statusFilterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        if (index == 0) {
            m_orderModel->setFilter("");
        } else {
            m_orderModel->setFilter(QString("status = '%1'").arg(ui->statusFilterCombo->currentText()));
        }
        m_orderModel->select();
    });
}

// Функции для товаров
void MainWindow::onAddProduct()
{
    ProductDialog dialog(m_productModel, this);
    if (dialog.exec() == QDialog::Accepted) {
        m_productModel->select();
        statusBar()->showMessage("Товар добавлен", 2000);
    }
}

void MainWindow::onEditProduct()
{
    QModelIndexList selected = ui->productTableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Выберите товар для редактирования");
        return;
    }
    int row = selected.first().row();
    ProductDialog dialog(m_productModel, row, this);
    if (dialog.exec() == QDialog::Accepted) {
        m_productModel->select();
        statusBar()->showMessage("Изменения сохранены", 2000);
    }
}

void MainWindow::onDeleteProduct()
{
    QModelIndexList selected = ui->productTableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Выберите товар для удаления");
        return;
    }
    int row = selected.first().row();
    QString name = m_productModel->data(m_productModel->index(row, 1)).toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Подтверждение", QString("Удалить товар '%1'?").arg(name),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_productModel->removeRow(row)) {
            m_productModel->submitAll();
            statusBar()->showMessage("Товар удален", 2000);
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить товар");
        }
    }
}

void MainWindow::refreshProducts()
{
    m_productModel->select();
    statusBar()->showMessage("Таблица товаров обновлена", 2000);
}

void MainWindow::searchProducts(const QString &text)
{
    if (text.isEmpty()) {
        m_productModel->setFilter("");
    } else {
        QString filter = QString("name ILIKE '%%1%' OR description ILIKE '%%1%' OR sku ILIKE '%%1%'").arg(text);
        m_productModel->setFilter(filter);
    }
    m_productModel->select();
}

// Функции для курьеров
void MainWindow::onAddCourier()
{
    CourierDialog dialog(m_courierModel, this);
    if (dialog.exec() == QDialog::Accepted) {
        m_courierModel->select();
        statusBar()->showMessage("Курьер добавлен", 2000);
    }
}

void MainWindow::onEditCourier()
{
    QModelIndexList selected = ui->courierTableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Выберите курьера для редактирования");
        return;
    }
    int row = selected.first().row();
    CourierDialog dialog(m_courierModel, row, this);
    if (dialog.exec() == QDialog::Accepted) {
        m_courierModel->select();
        statusBar()->showMessage("Изменения сохранены", 2000);
    }
}

void MainWindow::onDeleteCourier()
{
    QModelIndexList selected = ui->courierTableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Выберите курьера для удаления");
        return;
    }
    int row = selected.first().row();
    QString name = m_courierModel->data(m_courierModel->index(row, 1)).toString() + " " +
                   m_courierModel->data(m_courierModel->index(row, 2)).toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Подтверждение", QString("Удалить курьера %1?").arg(name),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_courierModel->removeRow(row)) {
            m_courierModel->submitAll();
            statusBar()->showMessage("Курьер удален", 2000);
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить курьера");
        }
    }
}

void MainWindow::refreshCouriers()
{
    m_courierModel->select();
    statusBar()->showMessage("Таблица курьеров обновлена", 2000);
}

void MainWindow::filterCouriersByActive(int state)
{
    if (state == Qt::Checked) {
        m_courierModel->setFilter("is_active = TRUE");
    } else if (state == Qt::Unchecked) {
        m_courierModel->setFilter("is_active = FALSE");
    } else {
        m_courierModel->setFilter("");
    }
    m_courierModel->select();
}

void MainWindow::searchCouriers(const QString &text)
{
    if (text.isEmpty()) {
        m_courierModel->setFilter("");
    } else {
        QString filter = QString("last_name ILIKE '%%1%' OR first_name ILIKE '%%1%' OR phone ILIKE '%%1%'").arg(text);
        m_courierModel->setFilter(filter);
    }
    m_courierModel->select();
}

// Функции для заказов
void MainWindow::onAddOrder()
{
    OrderDialog dialog(m_orderModel, this);
    if (dialog.exec() == QDialog::Accepted) {
        m_orderModel->select();
        statusBar()->showMessage("Заказ добавлен", 2000);
    }
}

void MainWindow::onEditOrder()
{
    QModelIndexList selected = ui->orderTableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Выберите заказ для редактирования");
        return;
    }
    int row = selected.first().row();
    OrderDialog dialog(m_orderModel, row, this);
    if (dialog.exec() == QDialog::Accepted) {
        m_orderModel->select();
        statusBar()->showMessage("Изменения сохранены", 2000);
    }
}

void MainWindow::onDeleteOrder()
{
    QModelIndexList selected = ui->orderTableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Выберите заказ для удаления");
        return;
    }
    int row = selected.first().row();
    QString name = m_orderModel->data(m_orderModel->index(row, 1)).toString();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Подтверждение", QString("Удалить заказ '%1'?").arg(name),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_orderModel->removeRow(row)) {
            m_orderModel->submitAll();
            statusBar()->showMessage("Заказ удален", 2000);
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить заказ");
        }
    }
}

void MainWindow::refreshOrders()
{
    m_orderModel->select();
    statusBar()->showMessage("Таблица заказов обновлена", 2000);
}

void MainWindow::searchOrders(const QString &text)
{
    if (text.isEmpty()) {
        m_orderModel->setFilter("");
    } else {
        QString filter = QString("customer_name ILIKE '%%1%' OR customer_phone ILIKE '%%1%' OR customer_address ILIKE '%%1%'").arg(text);
        m_orderModel->setFilter(filter);
    }
    m_orderModel->select();
}
