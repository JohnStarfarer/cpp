// main.cpp, ЧЕИ
// Description: lab3v6

#include "Lab3.hpp"
#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <vector>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "Rus");

    int choice = -1;
    while (true) {
        std::cout << "Лабораторная работа №3, Вариант 6\n";
        std::cout << "1 - Задание 1 (Время и Дом)\n";
        std::cout << "2 - Задание 2 (Сотрудники и отделы)\n";
        std::cout << "3 - Задание 3 (Список сотрудников)\n";
        std::cout << "4 - Задание 4 (Дом с const этажами)\n";
        std::cout << "5 - Задание 5 (Пистолет)\n";
        std::cout << "0 - Выход\n";
        std::cout << "\nВведите номер задания (0 для выхода): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 0 || choice > 5) {
            clearInput();
            std::cout << "Ошибка ввода. Попробуйте снова.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::cout << "\n Задание 1.4 (Время) \n";
                std::cout << "Введите три значения времени в секундах (целые числа):\n";

                int t1_val, t2_val, t3_val;

                while (true) {
                    std::cout << "Введите 1-е значение (например, 10): ";
                    std::cin >> t1_val;
                    if (std::cin.fail() || t1_val <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                
                while (true) {
                    std::cout << "Введите 2-е значение (например, 10000): ";
                    std::cin >> t2_val;
                    if (std::cin.fail() || t2_val <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                while (true) {
                    std::cout << "Введите 3-е значение (например, 100000): ";
                    std::cin >> t3_val;
                    if (std::cin.fail() || t3_val <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                Time t1(t1_val);
                Time t2(t2_val);
                Time t3(t3_val);

                std::cout << t1_val << " секунд:      "; t1.print(); std::cout << "\n";
                std::cout << t2_val << " секунд:   "; t2.print(); std::cout << "\n";
                std::cout << t3_val << " секунд:  "; t3.print(); std::cout << "\n";

                std::cout << "\n Задание 1.5 (Дом) \n";
                std::cout << "Введите три значения для количества этажей:\n";

                int floors1, floors2, floors3;

                while (true) {
                    std::cout << "Введите 1-е количество этажей (например, 1): ";
                    std::cin >> floors1;
                    if (std::cin.fail() || floors1 <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                while (true) {
                    std::cout << "Введите 2-е количество этажей (например, 5): ";
                    std::cin >> floors2;
                    if (std::cin.fail() || floors2 <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                while (true) {
                    std::cout << "Введите 3-е количество этажей (например, 23): ";
                    std::cin >> floors3;
                    if (std::cin.fail() || floors3 <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                House h1(floors1);
                House h2(floors2);
                House h3(floors3);
                h1.print();
                h2.print();
                h3.print();
                break;
            }
            case 2: {
                std::cout << "\n Задание 2.4 (Сотрудники и отделы) \n";
                std::string deptName, name1, name2, name3;

                while (true) {
                    std::cout << "Введите название отдела (например, IT): ";
                    std::cin >> deptName;
                    if (std::cin.fail() || deptName.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }

                Department dept(deptName);

                while (true) {
                    std::cout << "Введите имя первого сотрудника (например, Петров): ";
                    std::cin >> name1;
                    if (std::cin.fail() || name1.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }
                Employee emp1(name1, &dept);

                while (true) {
                    std::cout << "Введите имя второго сотрудника (например, Козлов): ";
                    std::cin >> name2;
                    if (std::cin.fail() || name2.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }
                Employee emp2(name2, &dept);

                while (true) {
                    std::cout << "Введите имя третьего сотрудника (например, Сидоров): ";
                    std::cin >> name3;
                    if (std::cin.fail() || name3.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }
                Employee emp3(name3, &dept);

                dept.setBoss(&emp2);

                std::cout << "Информация об отделе: ";
                dept.print();
                std::cout << "\nСотрудники:\n";
                emp1.print();
                emp2.print();
                emp3.print();
                break;
            }
            case 3: {
                std::cout << "\n Задание 3.4 (Список сотрудников отдела) \n";
                std::string deptName, name1, name2, name3;

                while (true) {
                    std::cout << "Введите название отдела (например, IT): ";
                    std::cin >> deptName;
                    if (std::cin.fail() || deptName.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }
                Department dept(deptName);

                while (true) {
                    std::cout << "Введите имя первого сотрудника: ";
                    std::cin >> name1;
                    if (std::cin.fail() || name1.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }
                Employee emp1(name1, &dept);

                while (true) {
                    std::cout << "Введите имя второго сотрудника: ";
                    std::cin >> name2;
                    if (std::cin.fail() || name2.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }
                Employee emp2(name2, &dept);

                while (true) {
                    std::cout << "Введите имя третьего сотрудника: ";
                    std::cin >> name3;
                    if (std::cin.fail() || name3.empty()) {
                        std::cout << "Ошибка: введите непустую строку.\n";
                        clearInput();
                    } else break;
                }
                Employee emp3(name3, &dept);

                dept.setBoss(&emp2);

                std::cout << "Информация о сотрудниках:\n";
                emp1.print();
                emp2.print();
                emp3.print();

                std::cout << "\nПолучение списка всех сотрудников отдела через сотрудника " << emp1.getName() << ":\n";
                Department* deptPtr = emp1.getDepartment();
                if (deptPtr) {
                    for (const auto& emp : deptPtr->getEmployees()) {
                        std::cout << "  - " << emp->getName() << "\n";
                    }
                }
                break;
            }
            case 4: {
                std::cout << "\n Задание 4.3 (Дом с const этажами) \n";
                std::cout << "Введите три значения для количества этажей:\n";

                int floors1, floors2, floors3;

                while (true) {
                    std::cout << "Введите 1-е количество этажей (например, 2): ";
                    std::cin >> floors1;
                    if (std::cin.fail() || floors1 <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                while (true) {
                    std::cout << "Введите 2-е количество этажей (например, 35): ";
                    std::cin >> floors2;
                    if (std::cin.fail() || floors2 <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                while (true) {
                    std::cout << "Введите 3-е количество этажей (например, 91): ";
                    std::cin >> floors3;
                    if (std::cin.fail() || floors3 <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                House house1(floors1);
                House house2(floors2);
                House house3(floors3);
                house1.print();
                house2.print();
                house3.print();

                std::cout << "// house1.floors = 10;  // компилято вызовет ошибку: присвоение члену с квалификатором const\n";
                break;
            }
            case 5: {
                std::cout << "\n Задание 5.1 (Пистолет) \n";
                int bullets, shots;

                while (true) {
                    std::cout << "Введите начальное количество патронов (например, 3): ";
                    std::cin >> bullets;
                    if (std::cin.fail() || bullets <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                while (true) {
                    std::cout << "Сколько раз выстрелить? (например, 5): ";
                    std::cin >> shots;
                    if (std::cin.fail() || shots <= 0) {
                        std::cout << "Ошибка: введите положительное целое число.\n";
                        clearInput();
                    } else break;
                }

                Gun gun(bullets);
                std::cout << "Стреляем " << shots << " раз:\n";
                for (int i = 0; i < shots; ++i) {
                    gun.shoot();
                }
                gun.print();
                break;
            }
            default:
                std::cout << "Неизвестный пункт\n";
        }
    }
    return 0;
}