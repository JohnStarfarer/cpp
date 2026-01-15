/********************************************************************************
** Form generated from reading UI file 'courierdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURIERDIALOG_H
#define UI_COURIERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CourierDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lastNameEdit;
    QLabel *label_2;
    QLineEdit *firstNameEdit;
    QLabel *label_3;
    QLineEdit *patronymicEdit;
    QLabel *label_4;
    QLineEdit *phoneEdit;
    QLabel *label_5;
    QComboBox *vehicleTypeCombo;
    QLabel *label_6;
    QLineEdit *vehiclePlateEdit;
    QLabel *label_7;
    QCheckBox *activeCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CourierDialog)
    {
        if (CourierDialog->objectName().isEmpty())
            CourierDialog->setObjectName("CourierDialog");
        CourierDialog->resize(400, 350);
        verticalLayout = new QVBoxLayout(CourierDialog);
        verticalLayout->setObjectName("verticalLayout");
        headerLabel = new QLabel(CourierDialog);
        headerLabel->setObjectName("headerLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        headerLabel->setFont(font);

        verticalLayout->addWidget(headerLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(CourierDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        lastNameEdit = new QLineEdit(CourierDialog);
        lastNameEdit->setObjectName("lastNameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lastNameEdit);

        label_2 = new QLabel(CourierDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        firstNameEdit = new QLineEdit(CourierDialog);
        firstNameEdit->setObjectName("firstNameEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, firstNameEdit);

        label_3 = new QLabel(CourierDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        patronymicEdit = new QLineEdit(CourierDialog);
        patronymicEdit->setObjectName("patronymicEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, patronymicEdit);

        label_4 = new QLabel(CourierDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        phoneEdit = new QLineEdit(CourierDialog);
        phoneEdit->setObjectName("phoneEdit");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, phoneEdit);

        label_5 = new QLabel(CourierDialog);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        vehicleTypeCombo = new QComboBox(CourierDialog);
        vehicleTypeCombo->setObjectName("vehicleTypeCombo");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, vehicleTypeCombo);

        label_6 = new QLabel(CourierDialog);
        label_6->setObjectName("label_6");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_6);

        vehiclePlateEdit = new QLineEdit(CourierDialog);
        vehiclePlateEdit->setObjectName("vehiclePlateEdit");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, vehiclePlateEdit);

        label_7 = new QLabel(CourierDialog);
        label_7->setObjectName("label_7");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_7);

        activeCheckBox = new QCheckBox(CourierDialog);
        activeCheckBox->setObjectName("activeCheckBox");
        activeCheckBox->setChecked(true);

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, activeCheckBox);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(CourierDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CourierDialog);

        QMetaObject::connectSlotsByName(CourierDialog);
    } // setupUi

    void retranslateUi(QDialog *CourierDialog)
    {
        CourierDialog->setWindowTitle(QCoreApplication::translate("CourierDialog", "\320\232\321\203\321\200\321\214\320\265\321\200", nullptr));
        headerLabel->setText(QCoreApplication::translate("CourierDialog", "\320\232\321\203\321\200\321\214\320\265\321\200", nullptr));
        label->setText(QCoreApplication::translate("CourierDialog", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 *:", nullptr));
        label_2->setText(QCoreApplication::translate("CourierDialog", "\320\230\320\274\321\217 *:", nullptr));
        label_3->setText(QCoreApplication::translate("CourierDialog", "\320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        label_4->setText(QCoreApplication::translate("CourierDialog", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275 *:", nullptr));
        label_5->setText(QCoreApplication::translate("CourierDialog", "\320\242\320\270\320\277 \321\202\321\200\320\260\320\275\321\201\320\277\320\276\321\200\321\202\320\260:", nullptr));
        label_6->setText(QCoreApplication::translate("CourierDialog", "\320\223\320\276\321\201\320\275\320\276\320\274\320\265\321\200:", nullptr));
        label_7->setText(QCoreApplication::translate("CourierDialog", "\320\220\320\272\321\202\320\270\320\262\320\265\320\275:", nullptr));
        activeCheckBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CourierDialog: public Ui_CourierDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURIERDIALOG_H
