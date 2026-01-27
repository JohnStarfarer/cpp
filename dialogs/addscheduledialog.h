#ifndef ADDSCHEDULEDIALOG_H
#define ADDSCHEDULEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>

class AddScheduleDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddScheduleDialog(QWidget *parent = nullptr);
    AddScheduleDialog(int scheduleId, QWidget *parent = nullptr);
    
    int getRouteId() const;
    int getTrainId() const;
    int getWagonTypeId() const;
    QDate getDepartureDate() const { return m_departureDateEdit->date(); }
    QTime getDepartureTime() const { return m_departureTimeEdit->time(); }
    QDate getArrivalDate() const { return m_arrivalDateEdit->date(); }
    QTime getArrivalTime() const { return m_arrivalTimeEdit->time(); }
    int getAvailableSeats() const { return m_seatsSpin->value(); }
    double getPrice() const { return m_priceSpin->value(); }
    QString getStatus() const { return m_statusCombo->currentText(); }
    
private slots:
    void validateAndAccept();
    void calculatePrice();
    void updateArrivalDate();
    
private:
    void setupUI();
    void loadScheduleData(int scheduleId);
    void loadComboBoxData();
    bool validateDates();
    
    QComboBox *m_routeCombo;
    QComboBox *m_trainCombo;
    QComboBox *m_wagonTypeCombo;
    QDateEdit *m_departureDateEdit;
    QTimeEdit *m_departureTimeEdit;
    QDateEdit *m_arrivalDateEdit;
    QTimeEdit *m_arrivalTimeEdit;
    QSpinBox *m_seatsSpin;
    QDoubleSpinBox *m_priceSpin;
    QComboBox *m_statusCombo;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    QLabel *m_routeInfoLabel;
    QLabel *m_trainInfoLabel;
    QLabel *m_wagonTypeInfoLabel;
    
    int m_scheduleId;
};

#endif // ADDSCHEDULEDIALOG_H