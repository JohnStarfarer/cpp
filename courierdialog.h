#ifndef COURIERDIALOG_H
#define COURIERDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CourierDialog;
}

class CourierDialog : public QDialog
{
    Q_OBJECT

public:
    // Для добавления нового курьера
    explicit CourierDialog(QSqlTableModel *model, QWidget *parent = nullptr);
    // Для редактирования существующего
    explicit CourierDialog(QSqlTableModel *model, int row, QWidget *parent = nullptr);
    ~CourierDialog();

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    Ui::CourierDialog *ui;
    QSqlTableModel *m_model;
    QDataWidgetMapper *m_mapper;
    bool m_isEditMode;

    void setupUI();
    void setupValidators();
    bool validateInput();
};

#endif // COURIERDIALOG_H
