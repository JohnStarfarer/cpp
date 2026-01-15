#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Курьеры
    void onAddCourier();
    void onEditCourier();
    void onDeleteCourier();
    void refreshCouriers();
    void filterCouriersByActive(int state);
    void searchCouriers(const QString &text);

    // Товары
    void onAddProduct();
    void onEditProduct();
    void onDeleteProduct();
    void refreshProducts();
    void searchProducts(const QString &text);

    // Заказы
    void onAddOrder();
    void onEditOrder();
    void onDeleteOrder();
    void refreshOrders();
    void searchOrders(const QString &text);

private:
    Ui::MainWindow *ui;
    QSqlTableModel *m_courierModel;
    QSqlTableModel *m_productModel;
    QSqlRelationalTableModel *m_orderModel;

    void setupModels();
    void setupConnections();
};

#endif // MAINWINDOW_H
