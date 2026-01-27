#ifndef ADDROUTEDIALOG_H
#define ADDROUTEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class AddRouteDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddRouteDialog(QWidget *parent = nullptr);
    AddRouteDialog(int routeId, QWidget *parent = nullptr);
    
    QString getDeparture() const { return m_departureEdit->text(); }
    QString getArrival() const { return m_arrivalEdit->text(); }
    double getBasePrice() const { return m_priceSpin->value(); }
    QString getStatus() const { return m_statusCombo->currentText(); }
    int getDistance() const { return m_distanceSpin->value(); }
    
private slots:
    void validateAndAccept();
    
private:
    void setupUI();
    void loadRouteData(int routeId);
    
    QLineEdit *m_departureEdit;
    QLineEdit *m_arrivalEdit;
    QSpinBox *m_distanceSpin;
    QDoubleSpinBox *m_priceSpin;
    QComboBox *m_statusCombo;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    int m_routeId;
};

#endif // ADDROUTEDIALOG_H