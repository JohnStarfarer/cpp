#ifndef ADDWAGONTYPEDIALOG_H
#define ADDWAGONTYPEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class AddWagonTypeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddWagonTypeDialog(QWidget *parent = nullptr);
    AddWagonTypeDialog(int wagonTypeId, QWidget *parent = nullptr);
    
    QString getName() const { return m_nameEdit->text(); }
    int getCapacity() const { return m_capacitySpin->value(); }
    QString getDescription() const { return m_descEdit->toPlainText(); }
    
private slots:
    void validateAndAccept();
    
private:
    void setupUI();
    void loadWagonTypeData(int wagonTypeId);
    
    QLineEdit *m_nameEdit;
    QSpinBox *m_capacitySpin;
    QTextEdit *m_descEdit;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    int m_wagonTypeId;
};

#endif // ADDWAGONTYPEDIALOG_H