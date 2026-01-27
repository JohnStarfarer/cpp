#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // стиль приложения
    app.setStyle(QStyleFactory::create("Fusion"));
    
    // инфа о приложении
    app.setApplicationName("RZD-Control");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("RZD");
    
    // подключение к бд
    if (!Database::testConnection()) {
        QMessageBox::critical(nullptr, "Ошибка подключения",
            "Не удалось подключиться к базе данных.\n"
            "Убедитесь, что:\n"
            "1. PostgreSQL запущен\n"
            "2. База данных 'rzd_control' существует\n"
            "3. Пользователь 'rzd_admin' с паролем 'admin123' создан\n\n"
            "Для установки базы данных запустите скрипт install.sh");
        return 1;
    }
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
