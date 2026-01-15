/********************************************************************************
** Form generated from reading UI file 'productdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTDIALOG_H
#define UI_PRODUCTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProductDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QLabel *label_2;
    QTextEdit *descriptionEdit;
    QLabel *label_3;
    QLineEdit *skuEdit;
    QLabel *label_4;
    QSpinBox *quantitySpin;
    QLabel *label_5;
    QLineEdit *unitEdit;
    QLabel *label_6;
    QLineEdit *locationEdit;
    QLabel *label_7;
    QSpinBox *reorderSpin;
    QLabel *label_8;
    QDoubleSpinBox *priceSpin;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProductDialog)
    {
        if (ProductDialog->objectName().isEmpty())
            ProductDialog->setObjectName("ProductDialog");
        ProductDialog->resize(500, 500);
        verticalLayout = new QVBoxLayout(ProductDialog);
        verticalLayout->setObjectName("verticalLayout");
        headerLabel = new QLabel(ProductDialog);
        headerLabel->setObjectName("headerLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        headerLabel->setFont(font);

        verticalLayout->addWidget(headerLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(ProductDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        nameEdit = new QLineEdit(ProductDialog);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameEdit);

        label_2 = new QLabel(ProductDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        descriptionEdit = new QTextEdit(ProductDialog);
        descriptionEdit->setObjectName("descriptionEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, descriptionEdit);

        label_3 = new QLabel(ProductDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        skuEdit = new QLineEdit(ProductDialog);
        skuEdit->setObjectName("skuEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, skuEdit);

        label_4 = new QLabel(ProductDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        quantitySpin = new QSpinBox(ProductDialog);
        quantitySpin->setObjectName("quantitySpin");
        quantitySpin->setMaximum(999999);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, quantitySpin);

        label_5 = new QLabel(ProductDialog);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        unitEdit = new QLineEdit(ProductDialog);
        unitEdit->setObjectName("unitEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, unitEdit);

        label_6 = new QLabel(ProductDialog);
        label_6->setObjectName("label_6");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_6);

        locationEdit = new QLineEdit(ProductDialog);
        locationEdit->setObjectName("locationEdit");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, locationEdit);

        label_7 = new QLabel(ProductDialog);
        label_7->setObjectName("label_7");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_7);

        reorderSpin = new QSpinBox(ProductDialog);
        reorderSpin->setObjectName("reorderSpin");
        reorderSpin->setMaximum(9999);

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, reorderSpin);

        label_8 = new QLabel(ProductDialog);
        label_8->setObjectName("label_8");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, label_8);

        priceSpin = new QDoubleSpinBox(ProductDialog);
        priceSpin->setObjectName("priceSpin");
        priceSpin->setMaximum(9999999.990000000223517);
        priceSpin->setDecimals(2);

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, priceSpin);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(ProductDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ProductDialog);

        QMetaObject::connectSlotsByName(ProductDialog);
    } // setupUi

    void retranslateUi(QDialog *ProductDialog)
    {
        ProductDialog->setWindowTitle(QCoreApplication::translate("ProductDialog", "\320\242\320\276\320\262\320\260\321\200", nullptr));
        headerLabel->setText(QCoreApplication::translate("ProductDialog", "\320\242\320\276\320\262\320\260\321\200", nullptr));
        label->setText(QCoreApplication::translate("ProductDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 *:", nullptr));
        label_2->setText(QCoreApplication::translate("ProductDialog", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265:", nullptr));
        label_3->setText(QCoreApplication::translate("ProductDialog", "\320\220\321\200\321\202\320\270\320\272\321\203\320\273:", nullptr));
        label_4->setText(QCoreApplication::translate("ProductDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        label_5->setText(QCoreApplication::translate("ProductDialog", "\320\225\320\264\320\270\320\275\320\270\321\206\320\260 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", nullptr));
        label_6->setText(QCoreApplication::translate("ProductDialog", "\320\234\320\265\321\201\321\202\320\276 \321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217:", nullptr));
        label_7->setText(QCoreApplication::translate("ProductDialog", "\320\237\320\276\321\200\320\276\320\263 \320\267\320\260\320\272\320\260\320\267\320\260:", nullptr));
        label_8->setText(QCoreApplication::translate("ProductDialog", "\320\246\320\265\320\275\320\260:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductDialog: public Ui_ProductDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTDIALOG_H
