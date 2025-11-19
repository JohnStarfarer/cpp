// main.cpp, ЧУЕ
// Description: lab4.cpp
#include "QuadraticEquation.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "");
    std::cout << "QuadraticEquation\nВычисление  корней  квадратного уравнения.\nРезультат  должен  быть массивом величин типа double (в нем от 0 до  2-х  элементов,  в  зависимости  от количества корней)." << std::endl;
    std::cout << "Введите \'99\' для справки." << std::endl;

    QuadraticEquation quadeq;
    bool userInput = true;

    while (userInput) {
        std::cout << "\n" << quadeq << std::endl;
        int userChoice = 0;
        std::cout << "Номер функции программы: ";
        std::cin >> userChoice;
        
        if (userChoice == -1) break;

        switch (userChoice) {
            case 99: {
                std::cout << "-1. Завершение работы программы." << std::endl; 
                std::cout << "== МЕТОДЫ [1-2] ==" << std::endl;
                std::cout << "1. Задать значения коэффициентам a, b, c (double)." << std::endl;
                std::cout << "2. Вычисление корней (массив величин типа double)." << std::endl;
                std::cout << "== УНАРНЫЕ ОПЕРАЦИИ [3-6] ==" << std::endl;
                std::cout << "3. Увеличить коэффициенты уравнения на 1 (префикс)." << std::endl;
                std::cout << "4. Увеличить коэффициенты уравнения на 1 (постфикс)." << std::endl;
                std::cout << "5. Уменьшить коэффициенты уравнения на 1 (префикс)." << std::endl;
                std::cout << "6. Уменьшить коэффициенты уравнения на 1 (постфикс)." << std::endl;
                std::cout << "== ОПЕРАЦИИ ПРИВИДЕНИЯ ТИПА [7-8] ==" << std::endl;
                std::cout << "7. Приведение к double (неявному виду) дискриминант уравнения." << std::endl;
                std::cout << "8. Приведение к bool (явному виду) существование корней." << std::endl;
                std::cout << "== БИНАРНЫЕ ОПЕРАЦИИ [9-10] ==" << std::endl;
                std::cout << "9. Уравнения равны, если равны их коэффициенты (QE == QE)." << std::endl;
                std::cout << "10. Уравнения НЕ равны, если НЕ равны их коэффициенты (QE != QE)." << std::endl;
                break;
            }
            // case -1: {
            //     userInput = false;
            //     break;
            // }
            case 1: {
                double a = 0, b = 0, c = 0;
                std::cout << "Введите a: ";
                std::cin >> a;
                std::cout << "Введите b: ";
                std::cin >> b;
                std::cout << "Введите c: ";
                std::cin >> c;

                QuadraticEquation temp = QuadraticEquation(a, b, c);
                quadeq = temp;

                break;
            }
            case 2: {
                std::cout << "Корни уравнения: [ ";
                std::vector vRoots = quadeq.roots();
                for (double root : vRoots) {
                    std::cout << root << " ";
                }
                std::cout << "]" << std::endl;
                break;
            }
            case 3: {
                std::cout << ++quadeq << std::endl;
                break;
            }
            case 4: {
                std::cout << quadeq++ << std::endl;
                break;
            }
            case 5: {
                std::cout << --quadeq << std::endl;
                break;
            }
            case 6: {
                std::cout << quadeq-- << std::endl;
                break;
            }
            case 7: {
                std::cout << "Приведение к double (неявному виду) дискриминант уравнения: " << double(quadeq);
                std::cout << std::endl;
                break;
            }
            case 8:{
                std::cout << "Приведение к bool (явному виду) существование корней: " << std::boolalpha << (bool)quadeq << std::endl;
                break;
            }
            case 9: {
                std::cout << "Введите коэффициенты нового уравнения: " << std::endl;
                double a = 0, b = 0, c = 0;
                std::cout << "Введите a: ";
                std::cin >> a;
                std::cout << "Введите b: ";
                std::cin >> b;
                std::cout << "Введите c: ";
                std::cin >> c;
                QuadraticEquation quadeqSecond = QuadraticEquation(a, b, c);
                std::cout << quadeqSecond << std::endl;
                std::cout << "Уравнения равны? " << std::boolalpha << (quadeq == quadeqSecond) << std::endl;
                break;
            }
            case 10: {
                std::cout << "Введите коэффициенты нового уравнения: " << std::endl;
                double a = 0, b = 0, c = 0;
                std::cout << "Введите a: ";
                std::cin >> a;
                std::cout << "Введите b: ";
                std::cin >> b;
                std::cout << "Введите c: ";
                std::cin >> c;
                QuadraticEquation quadeqSecond = QuadraticEquation(a, b, c);
                std::cout << quadeqSecond << std::endl;
                std::cout << "Уравнения НЕ равны? " << std::boolalpha << (quadeq != quadeqSecond) << std::endl;
                break;
            }
            default: {
                std::cout << "Неверный ввод! Для справки введите \'99\'." << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                break;
            }
        }
    }

    return 0;
}