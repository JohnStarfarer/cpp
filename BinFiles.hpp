// BinFiles.hpp, ЧУЕ
// Description: lab5, var6
#ifndef BINFILES
#define BINFILES

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>
#include <cstring>

struct Toy {
    char name[50];
    double price;
    int minAge;
    
    Toy() : price(0.0), minAge(0) {
        name[0] = '\0';
    }
    
    Toy(const char* n, double p, int min) : price(p), minAge(min) {
        strncpy(name, n, 49);
        name[49] = '\0';
    }
};

class Files {
public:
    // 1-2.6 генератор
    static void genBin();

    // 1-2.6 вывод int bin'ов
    static void printBin(const std::string &filename);

    // 1.6 Кратные k
    static void multiplesK();

    // 2.6 Матрица
    static void binMatrix();

    // 3.6 генератор игрушек
    static void genToyBin();

    // 3.6 вывод файла с игрушками
    static void printToyBin();

    // 3.6 поиск самого дорогого конструктора
    static void findMostExpensiveConstructor();
    
    // 3.6 приведения строки к нижнему регистру
    static std::string toLowerString(const char* str);

    // 4.6 генерация текстового файла со случайными числами
    static void genTxtFile();

    // 4.6 вывод текстового файла
    static void printTxtFile();

    // 4.6 поиск суммы элементов, равных своему индексу
    static void sumEqualIndex();
    
    // 5.6 генератор текстового файла с несколькими числами в строке
    static void genMultiTxtFile();

    // 5.6 вывод текстового файла с несколькими числами в строке
    static void printMultiTxtFile();

    // 5.6 произведение элементов, кратных заданному k
    static void productMultiplesK();

    // 6.6 генератор текстового файла с текстом
    static void genTextFile();

    // 6.6 вывод текстового файла
    static void printTextFile();

    // 6.6 проверка, содержит ли строка русские буквы
    static bool hasRussianLetters(const std::string& str);

    // 6.6 фильтрация строк без русских букв
    static void filterNoRussianLines();
    
private:
};

#endif