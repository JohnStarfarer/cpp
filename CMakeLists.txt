cmake_minimum_required(VERSION 3.16)

project(CourierManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

# Список исходных файлов
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    databasemanager.cpp
    databasemanager.h
    courierdialog.cpp
    courierdialog.h
    courierdialog.ui
    productdialog.cpp
    productdialog.h
    productdialog.ui
    orderdialog.cpp
    orderdialog.h
    orderdialog.ui

)

# Создаем исполняемый файл
qt_add_executable(CourierManager
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    productdialog.h productdialog.cpp productdialog.ui
    orderdialog.h orderdialog.cpp orderdialog.ui
)

# Подключаем библиотеки Qt
target_link_libraries(CourierManager PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

# Свойства для macOS (необязательно для Linux)
set_target_properties(CourierManager PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Финализация для qt_add_executable
qt_finalize_executable(CourierManager)
