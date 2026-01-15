/********************************************************************************
** Form generated from reading UI file 'orderdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERDIALOG_H
#define UI_ORDERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OrderDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *customerNameEdit;
    QLabel *label_2;
    QLineEdit *customerPhoneEdit;
    QLabel *label_3;
    QTextEdit *customerAddressEdit;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QComboBox *productCombo;
    QSpinBox *quantitySpin;
    QLabel *label_5;
    QLabel *priceLabel;
    QLabel *label_6;
    QComboBox *statusCombo;
    QLabel *label_7;
    QComboBox *courierCombo;
    QLabel *totalLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OrderDialog)
    {
        if (OrderDialog->objectName().isEmpty())
            OrderDialog->setObjectName("OrderDialog");
        OrderDialog->resize(500, 450);
        verticalLayout = new QVBoxLayout(OrderDialog);
        verticalLayout->setObjectName("verticalLayout");
        headerLabel = new QLabel(OrderDialog);
        headerLabel->setObjectName("headerLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        headerLabel->setFont(font);

        verticalLayout->addWidget(headerLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(OrderDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        customerNameEdit = new QLineEdit(OrderDialog);
        customerNameEdit->setObjectName("customerNameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, customerNameEdit);

        label_2 = new QLabel(OrderDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        customerPhoneEdit = new QLineEdit(OrderDialog);
        customerPhoneEdit->setObjectName("customerPhoneEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, customerPhoneEdit);

        label_3 = new QLabel(OrderDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        customerAddressEdit = new QTextEdit(OrderDialog);
        customerAddressEdit->setObjectName("customerAddressEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, customerAddressEdit);

        label_4 = new QLabel(OrderDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        productCombo = new QComboBox(OrderDialog);
        productCombo->setObjectName("productCombo");

        horizontalLayout->addWidget(productCombo);

        quantitySpin = new QSpinBox(OrderDialog);
        quantitySpin->setObjectName("quantitySpin");
        quantitySpin->setMaximum(9999);
        quantitySpin->setValue(1);

        horizontalLayout->addWidget(quantitySpin);


        formLayout->setLayout(3, QFormLayout::ItemRole::FieldRole, horizontalLayout);

        label_5 = new QLabel(OrderDialog);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        priceLabel = new QLabel(OrderDialog);
        priceLabel->setObjectName("priceLabel");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, priceLabel);

        label_6 = new QLabel(OrderDialog);
        label_6->setObjectName("label_6");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_6);

        statusCombo = new QComboBox(OrderDialog);
        statusCombo->setObjectName("statusCombo");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, statusCombo);

        label_7 = new QLabel(OrderDialog);
        label_7->setObjectName("label_7");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_7);

        courierCombo = new QComboBox(OrderDialog);
        courierCombo->setObjectName("courierCombo");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, courierCombo);


        verticalLayout->addLayout(formLayout);

        totalLabel = new QLabel(OrderDialog);
        totalLabel->setObjectName("totalLabel");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        totalLabel->setFont(font1);

        verticalLayout->addWidget(totalLabel);

        buttonBox = new QDialogButtonBox(OrderDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(OrderDialog);

        QMetaObject::connectSlotsByName(OrderDialog);
    } // setupUi

    void retranslateUi(QDialog *OrderDialog)
    {
        OrderDialog->setWindowTitle(QCoreApplication::translate("OrderDialog", "\320\227\320\260\320\272\320\260\320\267", nullptr));
        headerLabel->setText(QCoreApplication::translate("OrderDialog", "\320\227\320\260\320\272\320\260\320\267", nullptr));
        label->setText(QCoreApplication::translate("OrderDialog", "\320\227\320\260\320\272\320\260\320\267\321\207\320\270\320\272 *:", nullptr));
        label_2->setText(QCoreApplication::translate("OrderDialog", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275 *:", nullptr));
        label_3->setText(QCoreApplication::translate("OrderDialog", "\320\220\320\264\321\200\320\265\321\201 *:", nullptr));
        label_4->setText(QCoreApplication::translate("OrderDialog", "\320\242\320\276\320\262\320\260\321\200 *:", nullptr));
        label_5->setText(QCoreApplication::translate("OrderDialog", "\320\246\320\265\320\275\320\260:", nullptr));
        priceLabel->setText(QCoreApplication::translate("OrderDialog", "\320\246\320\265\320\275\320\260: 0 \321\200\321\203\320\261.", nullptr));
        label_6->setText(QCoreApplication::translate("OrderDialog", "\320\241\321\202\320\260\321\202\321\203\321\201:", nullptr));
        label_7->setText(QCoreApplication::translate("OrderDialog", "\320\232\321\203\321\200\321\214\320\265\321\200:", nullptr));
        totalLabel->setText(QCoreApplication::translate("OrderDialog", "\320\230\321\202\320\276\320\263\320\276: 0 \321\200\321\203\320\261.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderDialog: public Ui_OrderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERDIALOG_H
