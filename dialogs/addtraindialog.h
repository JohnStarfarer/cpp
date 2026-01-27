#ifndef ADDTRAINDIALOG_H
#define ADDTRAINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class AddTrainDialog : public QDialog
{
    Q_OBJECT
    
public:
    // Конструктор для добавления нового поезда
    explicit AddTrainDialog(QWidget *parent = nullptr);
    
    // Конструктор для редактирования существующего поезда
    AddTrainDialog(int trainId, QWidget *parent = nullptr);
    
    QString getName() const { return m_nameEdit->text(); }
    QString getStatus() const { return m_statusCombo->currentText(); }
    int getTotalSeats() const { return m_seatsSpin->value(); }
    
private slots:
    void validateAndAccept();
    
private:
    void setupUI();
    void loadTrainData(int trainId);
    
    // Виджеты
    QLineEdit *m_nameEdit;
    QComboBox *m_statusCombo;
    QSpinBox *m_seatsSpin;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    int m_trainId; // 0 для добавления, >0 для редактирования
};

#endif // ADDTRAINDIALOG_H