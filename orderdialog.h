#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class OrderDialog;
}

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(QSqlRelationalTableModel *model, QWidget *parent = nullptr);
    explicit OrderDialog(QSqlRelationalTableModel *model, int row, QWidget *parent = nullptr);
    ~OrderDialog();

private slots:
    void onSaveClicked();
    void onCancelClicked();
    void onProductSelected(int index);
    void calculateTotal();

private:
    Ui::OrderDialog *ui;
    QSqlRelationalTableModel *m_orderModel;
    bool m_isEditMode;
    int m_currentOrderId;

    void setupUI();
    bool validateInput();
    void loadCouriers();
    void loadProducts();
    double getProductPrice(int productId);
};

#endif
