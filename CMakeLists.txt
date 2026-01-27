cmake_minimum_required(VERSION 3.16)
project(RZD_Control LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

set(SOURCE_FILES
    main.cpp
    database.cpp
    database.h
    mainwindow.cpp
    mainwindow.h
    
    # Модели
    models/trainmodel.cpp
    models/trainmodel.h
    models/wagontypemodel.cpp
    models/wagontypemodel.h
    models/routemodel.cpp
    models/routemodel.h
    models/passengermodel.cpp
    models/passengermodel.h
    models/schedulemodel.cpp
    models/schedulemodel.h
    models/ticketmodel.cpp
    models/ticketmodel.h
    models/scheduleviewmodel.cpp
    models/scheduleviewmodel.h
    models/ticketviewmodel.cpp
    models/ticketviewmodel.h
    
    # Диалоги
    dialogs/addtraindialog.cpp
    dialogs/addtraindialog.h
    dialogs/addwagontypedialog.cpp
    dialogs/addwagontypedialog.h
    dialogs/addroutedialog.cpp
    dialogs/addroutedialog.h
    dialogs/addpassengerdialog.cpp
    dialogs/addpassengerdialog.h
    dialogs/addscheduledialog.cpp
    dialogs/addscheduledialog.h
    dialogs/addticketdialog.cpp
    dialogs/addticketdialog.h
)

add_executable(RZD_Control ${SOURCE_FILES})

target_link_libraries(RZD_Control
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
)
