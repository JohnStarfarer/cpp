#ifndef ADDTICKETDIALOG_H
#define ADDTICKETDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QDateTimeEdit>

class AddTicketDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddTicketDialog(QWidget *parent = nullptr);
    AddTicketDialog(int ticketId, QWidget *parent = nullptr);
    
    int getScheduleId() const;
    int getPassengerId() const;
    int getWagonNumber() const { return m_wagonSpin->value(); }
    int getSeatNumber() const { return m_seatSpin->value(); }
    double getPrice() const { return m_priceSpin->value(); }
    QString getStatus() const { return m_statusCombo->currentText(); }
    
private slots:
    void validateAndAccept();
    void checkSeatAvailability();
    void onScheduleChanged();
    void onPassengerChanged();
    
private:
    void setupUI();
    void loadTicketData(int ticketId);
    void loadComboBoxData();
    void updatePrice();
    void updateAvailableSeats();
    
    QComboBox *m_scheduleCombo;
    QComboBox *m_passengerCombo;
    QSpinBox *m_wagonSpin;
    QSpinBox *m_seatSpin;
    QDoubleSpinBox *m_priceSpin;
    QComboBox *m_statusCombo;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    QPushButton *m_checkSeatButton;
    
    QLabel *m_scheduleInfoLabel;
    QLabel *m_passengerInfoLabel;
    QLabel *m_seatStatusLabel;
    QLabel *m_availableSeatsLabel;
    
    QCheckBox *m_autoPriceCheck;
    
    int m_ticketId;
};

#endif // ADDTICKETDIALOG_H