#ifndef ADDPASSENGERDIALOG_H
#define ADDPASSENGERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class AddPassengerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddPassengerDialog(QWidget *parent = nullptr);
    AddPassengerDialog(int passengerId, QWidget *parent = nullptr);
    
    QString getLastName() const { return m_lastNameEdit->text(); }
    QString getFirstName() const { return m_firstNameEdit->text(); }
    QString getMiddleName() const { return m_middleNameEdit->text(); }
    QDate getBirthDate() const { return m_birthDateEdit->date(); }
    QString getGender() const { return m_genderCombo->currentText(); }
    QString getDocumentType() const { return m_docTypeCombo->currentText(); }
    QString getDocumentNumber() const { return m_docNumberEdit->text(); }
    QString getPhone() const { return m_phoneEdit->text(); }
    QString getEmail() const { return m_emailEdit->text(); }
    
private slots:
    void validateAndAccept();
    
private:
    void setupUI();
    void loadPassengerData(int passengerId);
    bool isValidEmail(const QString &email);
    bool isValidPhone(const QString &phone);
    
    QLineEdit *m_lastNameEdit;
    QLineEdit *m_firstNameEdit;
    QLineEdit *m_middleNameEdit;
    QDateEdit *m_birthDateEdit;
    QComboBox *m_genderCombo;
    QComboBox *m_docTypeCombo;
    QLineEdit *m_docNumberEdit;
    QLineEdit *m_phoneEdit;
    QLineEdit *m_emailEdit;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    int m_passengerId;
};

#endif // ADDPASSENGERDIALOG_H
