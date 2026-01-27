#!/bin/bash

echo "=============================================="
echo "Установка базы данных РЖД-Путь (управление)"
echo "=============================================="

# Проверка PostgreSQL
if ! command -v psql &> /dev/null; then
    echo "❌ PostgreSQL не установлен!"
    echo "Установите: sudo apt install postgresql"
    exit 1
fi

DB_NAME="rzd_control"
DB_USER="rzd_admin"
DB_PASSWORD="admin123"

echo "1. Создание базы данных '$DB_NAME'..."
sudo -u postgres psql -c "DROP DATABASE IF EXISTS $DB_NAME;" 2>/dev/null
sudo -u postgres psql -c "CREATE DATABASE $DB_NAME;" 2>/dev/null

if [ $? -ne 0 ]; then
    echo "❌ Ошибка создания базы данных!"
    exit 1
fi

echo "2. Создание пользователя '$DB_USER'..."
sudo -u postgres psql -c "DROP USER IF EXISTS $DB_USER;" 2>/dev/null
sudo -u postgres psql -c "CREATE USER $DB_USER WITH PASSWORD '$DB_PASSWORD';" 2>/dev/null
sudo -u postgres psql -c "ALTER USER $DB_USER WITH SUPERUSER;" 2>/dev/null

echo "3. Создание структуры таблиц..."
sudo -u postgres psql -d $DB_NAME -f create_database.sql 2>/dev/null

if [ $? -ne 0 ]; then
    echo "❌ Ошибка создания таблиц!"
    exit 1
fi

echo "4. Заполнение тестовыми данными..."
sudo -u postgres psql -d $DB_NAME -f insert_test_data.sql 2>/dev/null

if [ $? -ne 0 ]; then
    echo "❌ Ошибка заполнения данных!"
    exit 1
fi

echo "5. Настройка прав доступа..."
sudo -u postgres psql -d $DB_NAME -c "
    GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO $DB_USER;
    GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO $DB_USER;
    GRANT EXECUTE ON ALL FUNCTIONS IN SCHEMA public TO $DB_USER;
" 2>/dev/null

echo "6. Проверка подключения..."
PGPASSWORD=$DB_PASSWORD psql -U $DB_USER -d $DB_NAME -c "
    SELECT '✅ База успешно создана!' as message;
    SELECT 'Таблицы:' as table_list;
    SELECT table_name FROM information_schema.tables 
    WHERE table_schema = 'public' ORDER BY table_name;
" 2>/dev/null

echo ""
echo "=============================================="
echo "Установка завершена!"
echo "=============================================="
echo "Данные для подключения:"
echo "  Хост: localhost"
echo "  Порт: 5432"
echo "  База: $DB_NAME"
echo "  Пользователь: $DB_USER"
echo "  Пароль: $DB_PASSWORD"
echo ""
echo "Для подключения:"
echo "  psql -U $DB_USER -d $DB_NAME"
echo ""
echo "Для Qt приложения используйте настройки:"
echo "  host: localhost"
echo "  database: $DB_NAME"
echo "  username: $DB_USER"
echo "  password: $DB_PASSWORD"
echo "=============================================="