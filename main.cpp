#include "mainwindow.h"
#include "databasemanager.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем русскую локаль
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    // Инициализируем базу данных
    if (!DatabaseManager::instance().connect()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключиться к базе данных.");
        return 1;
    }

    MainWindow w;
    w.setWindowTitle("Курьер Менеджер");
    w.resize(1200, 700);
    w.show();

    return a.exec();
}
