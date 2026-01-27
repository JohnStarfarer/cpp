#!/bin/bash

echo "Удаление базы данных РЖД-Путь..."

DB_NAME="rzd_control"
DB_USER="rzd_admin"

read -p "Вы уверены? (y/N): " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Отмена."
    exit 1
fi

echo "1. Удаление базы данных '$DB_NAME'..."
sudo -u postgres psql -c "DROP DATABASE IF EXISTS $DB_NAME;" 2>/dev/null

echo "2. Удаление пользователя '$DB_USER'..."
sudo -u postgres psql -c "DROP USER IF EXISTS $DB_USER;" 2>/dev/null

echo "База данных удалена!"