// main.cpp, ЧЕИ
// Description: lab5, var6
// g++ main.cpp BinFiles.cpp -o lab5.out -std=c++11 -Wall -Wextra

#include "BinFiles.hpp"
#include <iostream>

int main() {
    try {
        setlocale(LC_ALL, "");
        std::cout << "Бинарные файлы. Выполнить все задания в одном проекте в виде статических методов одного класса." << std::endl;
        std::cout << "Введите \'99\' для справки." << std::endl;

        bool userInput = true;
        
        while (userInput) {
            int userChoice = 0;
            std::cout << "Номер функции программы: ";
            std::cin >> userChoice;
            
            if (userChoice == -1) break;

            switch (userChoice) {
                case 99: {
                    std::cout << "Справка по функциям:\n";
                    std::cout << "-1. Завершение работы программы.\n";
                    std::cout << " 1. Фильтрация кратных k.\n";
                    std::cout << " 2. Работа с матрицей из int.\n";
                    std::cout << " 3. Работа со структурами (игрушки).\n";
                    std::cout << " 4. Работа с текстовым файлом (числа равные индексу).\n";
                    std::cout << " 5. Работа с текстовым файлом (несколько чисел в строке).\n";
                    std::cout << " 6. Работа с текстовым файлом (фильтрация строк без русских букв).\n";
                    std::cout << "99. Вывод этой справки.\n";
                    break;
                }
                case 1: {
                     std::cout << "\n=== Фильтрация кратных k ===\n\n";
                    Files::genBin();
                    Files::multiplesK();
                    Files::printBin("output.bin");
                    break;
                }
                case 2: {
                     std::cout << "\n=== Работа с матрицей из int ===\n\n";
                    Files::genBin();
                    Files::binMatrix();
                    Files::printBin("output.bin");
                    break;
                }
                case 3: {
                    std::cout << "\n=== Работа со структурами (игрушки) ===\n\n";
                    Files::genToyBin();
                    Files::printToyBin();
                    Files::findMostExpensiveConstructor();
                    break;
                    break;
                }
                 case 4: {
                    std::cout << "\n=== Работа с текстовым файлом (числа равные индексу) ===\n\n";
                    Files::genTxtFile();
                    Files::printTxtFile();
                    Files::sumEqualIndex();
                    break;
                }
                case 5: {
                    std::cout << "\n=== Работа с текстовым файлом (несколько чисел в строке) ===\n\n";
                    Files::genMultiTxtFile();
                    Files::printMultiTxtFile();
                    Files::productMultiplesK();
                    break;
                }
                case 6: {
                    std::cout << "\n=== Работа с текстовым файлом (фильтрация строк без русских букв) ===\n\n";
                    Files::genTextFile();
                    Files::printTextFile();
                    Files::filterNoRussianLines();
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
    }
    catch (const std::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }
}