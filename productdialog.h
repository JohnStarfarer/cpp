#ifndef PRODUCTDIALOG_H
#define PRODUCTDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class ProductDialog;
}

class ProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductDialog(QSqlTableModel *model, QWidget *parent = nullptr);
    explicit ProductDialog(QSqlTableModel *model, int row, QWidget *parent = nullptr);
    ~ProductDialog();

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    Ui::ProductDialog *ui;
    QSqlTableModel *m_model;
    QDataWidgetMapper *m_mapper;
    bool m_isEditMode;

    void setupUI();
    bool validateInput();
};

#endif
