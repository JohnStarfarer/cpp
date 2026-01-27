#!/bin/bash

echo "Сборка приложения РЖД-Путь..."

# Создаем директорию для сборки если её нет
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# Запускаем CMake
echo "Запуск CMake..."
cmake ..

# Собираем проект
echo "Сборка проекта..."
make -j4

# Проверяем успешность сборки
if [ $? -eq 0 ]; then
    echo ""
    echo "Сборка успешно завершена!"
    echo ""
    
    # Запускаем приложение
    if [ -f "RZD_Control" ]; then
        echo "Запуск приложения..."
        echo "=========================================="
        ./RZD_Control
    else
        echo "Исполняемый файл не найден!"
        exit 1
    fi
else
    echo "Ошибка сборки!"
    exit 1
fi