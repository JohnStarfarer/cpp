/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *courierTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *addCourierButton;
    QPushButton *editCourierButton;
    QPushButton *deleteCourierButton;
    QSpacerItem *horizontalSpacer;
    QCheckBox *activeCourierCheck;
    QLineEdit *searchCourierEdit;
    QPushButton *refreshCourierButton;
    QTableView *courierTableView;
    QWidget *productTab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addProductButton;
    QPushButton *editProductButton;
    QPushButton *deleteProductButton;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *searchProductEdit;
    QPushButton *refreshProductButton;
    QTableView *productTableView;
    QWidget *orderTab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addOrderButton;
    QPushButton *editOrderButton;
    QPushButton *deleteOrderButton;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *statusFilterCombo;
    QLineEdit *searchOrderEdit;
    QPushButton *refreshOrderButton;
    QTableView *orderTableView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        courierTab = new QWidget();
        courierTab->setObjectName("courierTab");
        verticalLayout_2 = new QVBoxLayout(courierTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addCourierButton = new QPushButton(courierTab);
        addCourierButton->setObjectName("addCourierButton");

        horizontalLayout->addWidget(addCourierButton);

        editCourierButton = new QPushButton(courierTab);
        editCourierButton->setObjectName("editCourierButton");

        horizontalLayout->addWidget(editCourierButton);

        deleteCourierButton = new QPushButton(courierTab);
        deleteCourierButton->setObjectName("deleteCourierButton");

        horizontalLayout->addWidget(deleteCourierButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        activeCourierCheck = new QCheckBox(courierTab);
        activeCourierCheck->setObjectName("activeCourierCheck");
        activeCourierCheck->setChecked(true);

        horizontalLayout->addWidget(activeCourierCheck);

        searchCourierEdit = new QLineEdit(courierTab);
        searchCourierEdit->setObjectName("searchCourierEdit");

        horizontalLayout->addWidget(searchCourierEdit);

        refreshCourierButton = new QPushButton(courierTab);
        refreshCourierButton->setObjectName("refreshCourierButton");

        horizontalLayout->addWidget(refreshCourierButton);


        verticalLayout_2->addLayout(horizontalLayout);

        courierTableView = new QTableView(courierTab);
        courierTableView->setObjectName("courierTableView");

        verticalLayout_2->addWidget(courierTableView);

        tabWidget->addTab(courierTab, QString());
        productTab = new QWidget();
        productTab->setObjectName("productTab");
        verticalLayout_3 = new QVBoxLayout(productTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addProductButton = new QPushButton(productTab);
        addProductButton->setObjectName("addProductButton");

        horizontalLayout_2->addWidget(addProductButton);

        editProductButton = new QPushButton(productTab);
        editProductButton->setObjectName("editProductButton");

        horizontalLayout_2->addWidget(editProductButton);

        deleteProductButton = new QPushButton(productTab);
        deleteProductButton->setObjectName("deleteProductButton");

        horizontalLayout_2->addWidget(deleteProductButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        searchProductEdit = new QLineEdit(productTab);
        searchProductEdit->setObjectName("searchProductEdit");

        horizontalLayout_2->addWidget(searchProductEdit);

        refreshProductButton = new QPushButton(productTab);
        refreshProductButton->setObjectName("refreshProductButton");

        horizontalLayout_2->addWidget(refreshProductButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        productTableView = new QTableView(productTab);
        productTableView->setObjectName("productTableView");

        verticalLayout_3->addWidget(productTableView);

        tabWidget->addTab(productTab, QString());
        orderTab = new QWidget();
        orderTab->setObjectName("orderTab");
        verticalLayout_4 = new QVBoxLayout(orderTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addOrderButton = new QPushButton(orderTab);
        addOrderButton->setObjectName("addOrderButton");

        horizontalLayout_3->addWidget(addOrderButton);

        editOrderButton = new QPushButton(orderTab);
        editOrderButton->setObjectName("editOrderButton");

        horizontalLayout_3->addWidget(editOrderButton);

        deleteOrderButton = new QPushButton(orderTab);
        deleteOrderButton->setObjectName("deleteOrderButton");

        horizontalLayout_3->addWidget(deleteOrderButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        statusFilterCombo = new QComboBox(orderTab);
        statusFilterCombo->addItem(QString());
        statusFilterCombo->addItem(QString());
        statusFilterCombo->addItem(QString());
        statusFilterCombo->addItem(QString());
        statusFilterCombo->addItem(QString());
        statusFilterCombo->addItem(QString());
        statusFilterCombo->addItem(QString());
        statusFilterCombo->addItem(QString());
        statusFilterCombo->setObjectName("statusFilterCombo");

        horizontalLayout_3->addWidget(statusFilterCombo);

        searchOrderEdit = new QLineEdit(orderTab);
        searchOrderEdit->setObjectName("searchOrderEdit");

        horizontalLayout_3->addWidget(searchOrderEdit);

        refreshOrderButton = new QPushButton(orderTab);
        refreshOrderButton->setObjectName("refreshOrderButton");

        horizontalLayout_3->addWidget(refreshOrderButton);


        verticalLayout_4->addLayout(horizontalLayout_3);

        orderTableView = new QTableView(orderTab);
        orderTableView->setObjectName("orderTableView");

        verticalLayout_4->addWidget(orderTableView);

        tabWidget->addTab(orderTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\232\321\203\321\200\321\214\320\265\321\200 \320\234\320\265\320\275\320\265\320\264\320\266\320\265\321\200", nullptr));
        addCourierButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        editCourierButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        deleteCourierButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        activeCourierCheck->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\320\273\321\214\320\272\320\276 \320\260\320\272\321\202\320\270\320\262\320\275\321\213\320\265", nullptr));
        searchCourierEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \321\204\320\260\320\274\320\270\320\273\320\270\320\270, \320\270\320\274\320\265\320\275\320\270, \321\202\320\265\320\273\320\265\321\204\320\276\320\275\321\203", nullptr));
        refreshCourierButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(courierTab), QCoreApplication::translate("MainWindow", "\320\232\321\203\321\200\321\214\320\265\321\200\321\213", nullptr));
        addProductButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        editProductButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        deleteProductButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        searchProductEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\321\216, \320\276\320\277\320\270\321\201\320\260\320\275\320\270\321\216, \320\260\321\200\321\202\320\270\320\272\321\203\320\273\321\203", nullptr));
        refreshProductButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(productTab), QCoreApplication::translate("MainWindow", "\320\242\320\276\320\262\320\260\321\200\321\213", nullptr));
        addOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        editOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        deleteOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        statusFilterCombo->setItemText(0, QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265 \321\201\321\202\320\260\321\202\321\203\321\201\321\213", nullptr));
        statusFilterCombo->setItemText(1, QCoreApplication::translate("MainWindow", "\320\275\320\276\320\262\321\213\320\271", nullptr));
        statusFilterCombo->setItemText(2, QCoreApplication::translate("MainWindow", "\320\262 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\265", nullptr));
        statusFilterCombo->setItemText(3, QCoreApplication::translate("MainWindow", "\321\201\320\276\320\261\320\270\321\200\320\260\320\265\321\202\321\201\321\217", nullptr));
        statusFilterCombo->setItemText(4, QCoreApplication::translate("MainWindow", "\320\263\320\276\321\202\320\276\320\262 \320\272 \320\276\321\202\320\277\321\200\320\260\320\262\320\272\320\265", nullptr));
        statusFilterCombo->setItemText(5, QCoreApplication::translate("MainWindow", "\320\262 \320\277\321\203\321\202\320\270", nullptr));
        statusFilterCombo->setItemText(6, QCoreApplication::translate("MainWindow", "\320\264\320\276\321\201\321\202\320\260\320\262\320\273\320\265\320\275", nullptr));
        statusFilterCombo->setItemText(7, QCoreApplication::translate("MainWindow", "\320\276\321\202\320\274\320\265\320\275\320\265\320\275", nullptr));

        searchOrderEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\267\320\260\320\272\320\260\320\267\321\207\320\270\320\272\321\203, \321\202\320\265\320\273\320\265\321\204\320\276\320\275\321\203, \320\260\320\264\321\200\320\265\321\201\321\203", nullptr));
        refreshOrderButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(orderTab), QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\260\320\267\321\213", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
