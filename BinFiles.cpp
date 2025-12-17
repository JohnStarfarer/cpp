// BinFiles.cpp, ЧУЕ
// Description: lab5, var6
#include "BinFiles.hpp"
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>

// Делаем переменные статическими, чтобы избежать множественного определения
static const char* pFileName = "primary.bin";
static const char* oFileName = "output.bin";
static const char* toyFileName = "toys.bin";
static const char* txtFileName = "numbers.txt";
static const char* multiTxtFileName = "multi_numbers.txt";
static const char* textFileName = "text_file.txt";
static const char* textOutputFileName = "no_russian.txt";

    
void Files::genBin() {
    std::ofstream primFile(pFileName, std::ios::binary);
    if (!primFile) {
        throw std::runtime_error("Не удалось открыть первичный сгенерированный файл");
    }

    int count = 20;
    int minVal = 1;
    int maxVal = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    
    std::cout << "Содержание первичного файла " << pFileName << ": ";
    for (int i = 0; i < count; ++i) {
            int num = dist(gen);

            primFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
            std::cout << num << " ";
        }
        std::cout << "\n\n";

        primFile.close();
}

void Files::printBin(const std::string &filename) {
    std::ifstream readFile(filename, std::ios::binary);
    if (!readFile) {
        throw std::runtime_error("Не удалось открыть файл");
    }
    int num;
    
    std::cout << "Содержание файла " << filename << ": ";
    while (readFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    readFile.close();
}

void Files::multiplesK() {
    int k;
    
    while (true) {
        std::cout << "Введите целое число k (не 0): ";
        std::cin >> k;
        
        if (std::cin.fail() || k == 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Неверный ввод!" << std::endl;
        } else {
            break;
        }
    }

    std::ifstream primFile(pFileName, std::ios::binary);
    if (!primFile) {
        throw std::runtime_error("Не удалось открыть первичный файл");
    }

    std::ofstream outFile(oFileName, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Не удалось открыть выходной файл");
    }

    int num;
    std::cout << "Числа, кратные " << k << ": ";
    
    while (primFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        if (num % k == 0) {
            outFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;

    primFile.close();
    outFile.close();
}

void Files::binMatrix() {
    std::ifstream primFile(pFileName, std::ios::binary);
    if (!primFile) {
        throw std::runtime_error("Не удалось прочитать первичный файл");
    }
    
    std::vector<int> data;
    int num;
    
    while (primFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
        data.push_back(num);
    }

    primFile.close();
    
    int n;
    while (true) {
        std::cout << "Введите размер матрицы nXn (n > 0): ";
        std::cin >> n;
        
        if (std::cin.fail() || n <= 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Неверный ввод!" << std::endl;
        } else {
            break;
        }
    }
    
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    
    std::cout << "\nСоздаем квадратную матрицу " << n << "x" << n << ":" << std::endl;
    
    int dataInd = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dataInd < data.size()) {
                matrix[i][j] = data[dataInd];
                dataInd++;
            }
        }
    }
    
    std::cout << "\nИсходная матрица:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    std::vector<int> colSums(n, 0);
    int minSum = std::numeric_limits<int>::max();
    int minColInd = 0;
    
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            colSums[j] += matrix[i][j];
        }
        
        std::cout << "Сумма столбца " << j << ": " << colSums[j] << std::endl;
        
        if (colSums[j] < minSum) {
            minSum = colSums[j];
            minColInd = j;
        }
    }
    
    std::cout << "Столбец с минимальной суммой: " << minColInd << " (сумма = " << minSum << ")" << std::endl;
    
    std::vector<std::vector<int>> resultMatrix(n, std::vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultMatrix[i][j] = matrix[i][minColInd];
        }
    }
    
    std::cout << "\nИтоговая матрица:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << resultMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    
    std::ofstream outFile(oFileName, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Не удалось создать выходной файл");
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num = resultMatrix[i][j];
            outFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
        }
    }
    
    outFile.close();
    std::cout << "Матрица сохранена в файле: " << oFileName << "\n\n";
}

void Files::genToyBin() {
    std::ofstream toyFile(toyFileName, std::ios::binary);
    if (!toyFile) {
        throw std::runtime_error("Не удалось открыть файл для записи игрушек");
    }

    const char* toyNames[] = {
        "Конструктор Lego Technic",
        "Конструктор Mega Bloks",
        "Конструктор металлический",
        "Мяч футбольный",
        "Кукла Барби",
        "Машинка на радиоуправлении",
        "Пазл 1000 элементов",
        "Настольная игра Монополия",
        "Робот-трансформер",
        "Конструктор деревянный",
        "Конструктор магнитный",
        "Кубики развивающие",
        "Набор для рисования",
        "Игрушечная кухня",
        "Конструктор пластиковый"
    };
    
    const int nameCount = sizeof(toyNames) / sizeof(toyNames[0]);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> nameDist(0, nameCount - 1);
    std::uniform_real_distribution<double> priceDist(100.0, 5000.0);
    std::uniform_int_distribution<int> minAgeDist(0, 6);
    
    std::cout << "Файл с игрушками " << toyFileName << ":\n";
    
    for (int i = 0; i < 15; ++i) {
        Toy toy;
        
        int nameIndex = nameDist(gen);
        strncpy(toy.name, toyNames[nameIndex], 49);
        toy.name[49] = '\0';
        
        toy.price = priceDist(gen);
        
        toy.minAge = minAgeDist(gen);
        
        toyFile.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));
        
        std::cout << "Игрушка " << (i+1) << ":\n";
        std::cout << "  Название: " << toy.name << "\n";
        std::cout << "  Стоимость: " << toy.price << " руб.\n";
        std::cout << "  Возраст: от " << toy.minAge << " лет\n";
        std::cout << "---------------------------------------------\n";
    }
    
    toyFile.close();
    std::cout << "Файл с игрушками успешно создан!\n\n";
}

void Files::printToyBin() {
    std::ifstream readFile(toyFileName, std::ios::binary);
    if (!readFile) {
        throw std::runtime_error("Не удалось открыть файл с игрушками");
    }
    
    Toy toy;
    int counter = 1;
    
    std::cout << "Содержание файла " << toyFileName << ":\n";
    
    while (readFile.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        std::cout << "Игрушка " << counter++ << ":\n";
        std::cout << "  Название: " << toy.name << "\n";
        std::cout << "  Стоимость: " << toy.price << " руб.\n";
        std::cout << "  Возраст: от " << toy.minAge << " лет\n";
    }
    
    readFile.close();
}

void Files::findMostExpensiveConstructor() {
    std::ifstream toyFile(toyFileName, std::ios::binary);
    if (!toyFile) {
        throw std::runtime_error("Не удалось открыть файл с игрушками");
    }
    
    Toy toy;
    double maxPrice = -1.0;
    Toy mostExpensive;
    int constructorCount = 0;
    
    std::cout << "Поиск самого дорогого конструктора:\n";

    while (toyFile.read(reinterpret_cast<char*>(&toy), sizeof(Toy))) {
        if (std::string(toy.name).find("Конструктор") != std::string::npos) {
            constructorCount++;
            
            std::cout << "Найден конструктор:\n";
            std::cout << "  Название: " << toy.name << "\n";
            std::cout << "  Стоимость: " << toy.price << " руб.\n";
            std::cout << "  Возраст: от " << toy.minAge << " лет\n";
            std::cout << "---------------------------------------------\n";
            
            if (toy.price > maxPrice) {
                maxPrice = toy.price;
                mostExpensive = toy;
            }
        }
    }
    
    toyFile.close();
    
    if (constructorCount == 0) {
        std::cout << "Конструкторы не найдены в файле!\n\n";
    } else {
        std::cout << "\nИТОГ:\n";
        std::cout << "Всего конструкторов найдено: " << constructorCount << "\n";
        std::cout << "Самый дорогой конструктор:\n";
        std::cout << "  Название: " << mostExpensive.name << "\n";
        std::cout << "  Стоимость: " << mostExpensive.price << " руб.\n";
        std::cout << "  Возраст: от " << mostExpensive.minAge << " лет\n\n";
    }
}

std::string Files::toLowerString(const char *str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void Files::genTxtFile() {
        std::ofstream txtFile(txtFileName);
        if (!txtFile) {
            throw std::runtime_error("Не удалось открыть текстовый файл для записи");
        }

        int count = 25;
        int minVal = 0;
        int maxVal = 50;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(minVal, maxVal);
        
        std::cout << "Генерация текстового файла " << txtFileName << ":\n";
        std::cout << "Содержание файла (число -> индекс):\n";
        
        for (int i = 0; i < count; ++i) {
            int num = dist(gen);
            txtFile << num << "\n";
            
            std::cout << num << " (индекс: " << i << ")\n";
        }
        
        txtFile.close();
        std::cout << "\nТекстовый файл успешно создан!\n\n";
}

void Files::printTxtFile() {
    std::ifstream readFile(txtFileName);
    if (!readFile) {
        throw std::runtime_error("Не удалось открыть текстовый файл");
    }
    
    std::string line;
    int index = 0;
    
    std::cout << "Содержание текстового файла " << txtFileName << ":\n";
    std::cout << "Индекс | Значение\n";
    std::cout << "-----------------\n";
    
    while (std::getline(readFile, line)) {
        if (!line.empty()) {
            std::cout << index << "      | " << line << "\n";
            index++;
        }
    }
    
    readFile.close();
    std::cout << "\n";
}

void Files::sumEqualIndex() {
    std::ifstream inFile(txtFileName);
    if (!inFile) {
        throw std::runtime_error("Не удалось открыть текстовый файл");
    }
    
    std::string line;
    int index = 0;
    int sum = 0;
    std::vector<int> matchingIndices;
    std::vector<int> matchingValues;
    
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            int value = std::stoi(line);
            
            if (value == index) {
                sum += value;
                matchingIndices.push_back(index);
                matchingValues.push_back(value);
                
                std::cout << "Совпадение! Индекс " << index << " = значение " << value << "\n";
            }
            
            index++;
        }
    }
    
    inFile.close();
    
    if (matchingIndices.empty()) {
        std::cout << "Элементы, равные своему индексу, не найдены.\n";
    } else {
        std::cout << "Найдено совпадений: " << matchingIndices.size() << "\n";
        std::cout << "Индексы и значения:\n";
        
        for (size_t i = 0; i < matchingIndices.size(); i++) {
            std::cout << "  Индекс " << matchingIndices[i] << " = " << matchingValues[i] << "\n";
        }
        
        std::cout << "\nСумма найденных элементов: " << sum << "\n";
    }
    
    std::cout << "\n";
}

void Files::genMultiTxtFile() {
    std::ofstream txtFile(multiTxtFileName);
    if (!txtFile) {
        throw std::runtime_error("Не удалось открыть текстовый файл для записи");
    }

    int totalNumbers = 30;
    int minVal = 1;
    int maxVal = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> numDist(minVal, maxVal);
    std::uniform_int_distribution<int> countDist(2, 5);
    
    std::cout << "Генерация текстового файла " << multiTxtFileName << ":\n";
    std::cout << "Содержание файла (несколько чисел в строке):\n";
    
    int numbersWritten = 0;
    int lineNumber = 1;
    
    while (numbersWritten < totalNumbers) {
        int numbersInLine = countDist(gen);
        if (numbersWritten + numbersInLine > totalNumbers) {
            numbersInLine = totalNumbers - numbersWritten;
        }
        
        std::cout << "Строка " << lineNumber << ": ";
        
        for (int i = 0; i < numbersInLine; i++) {
            int num = numDist(gen);
            txtFile << num;
            
            std::cout << num;
            
            if (i < numbersInLine - 1) {
                txtFile << " ";
                std::cout << " ";
            }
            
            numbersWritten++;
        }
        
        txtFile << "\n";
        std::cout << "\n";
        lineNumber++;
    }
    
    txtFile.close();
    std::cout << "\nТекстовый файл с несколькими числами в строке успешно создан!\n";
    std::cout << "Всего чисел: " << totalNumbers << "\n\n";
}

void Files::printMultiTxtFile() {
    std::ifstream readFile(multiTxtFileName);
    if (!readFile) {
        throw std::runtime_error("Не удалось открыть текстовый файл");
    }
    
    std::string line;
    int lineNumber = 1;
    
    std::cout << "Содержание файла " << multiTxtFileName << " (несколько чисел в строке):\n";
    std::cout << "Номер строки | Содержимое\n";
    std::cout << "---------------------------\n";
    
    while (readFile >> line) {
        std::cout << lineNumber << "           | " << line << "\n";
        }
    
    readFile.close();
    std::cout << "\n";
}

void Files::productMultiplesK() {
    int k;
    while (true) {
        std::cout << "Введите целое число k (не 0): ";
        std::cin >> k;
        
        if (std::cin.fail() || k == 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Неверный ввод! k должно быть целым числом и не равно 0." << std::endl;
        } else {
            break;
        }
    }

    std::ifstream inFile(multiTxtFileName);
    if (!inFile) {
        throw std::runtime_error("Не удалось открыть текстовый файл");
    }
    
    std::string line;
    long long product = 1;
    int count = 0;
    std::vector<int> foundNumbers;
    
    int lineNumber = 1;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            std::stringstream ss(line);
            int num;
            
            while (ss >> num) {
                if (num % k == 0) {
                    std::cout << "Найдено: число " << num << " в строке " << lineNumber << " кратно " << k << "\n";
                    product *= num;
                    count++;
                    foundNumbers.push_back(num);
                }
            }
            
            lineNumber++;
        }
    }
    
    inFile.close();
    
    if (count == 0) {
        std::cout << "Чисел, кратных " << k << ", не найдено.\n";
    } else {
        std::cout << "Найдено чисел, кратных " << k << ": " << count << "\n";
        std::cout << "Найденные числа: ";
        
        for (size_t i = 0; i < foundNumbers.size(); i++) {
            std::cout << foundNumbers[i];
            if (i < foundNumbers.size() - 1) {
                std::cout << ", ";
            }
        }
        
        std::cout << "\nПроизведение найденных чисел: " << product << "\n";
        
    }
    
    std::cout << "\n";
}

void Files::genTextFile() {
    std::ofstream textFile(textFileName);
    if (!textFile) {
        throw std::runtime_error("Не удалось открыть текстовый файл для записи");
    }

    const char* lines[] = {
        "Hello world!",
        "Привет мир!",
        "This is a sample text.",
        "Это пример текста на русском.",
        "12345 67890",
        "Смешанный mixed текст text",
        "Only English here.",
        "Только русский текст здесь.",
        "Text with цифрами 123 and символами !@#",
        "Another English line without Russian.",
        "123 + 456 = 579",
        "Line with special characters: @#$%",
        "Строка с пунктуацией: запятые, точки.",
    };
    
    const int lineCount = sizeof(lines) / sizeof(lines[0]);
    
    std::cout << "Генерация текстового файла " << textFileName << ":\n";
    std::cout << "Содержание файла:\n";
    
    for (int i = 0; i < lineCount; ++i) {
        textFile << lines[i] << "\n";
        std::cout << "Строка " << (i+1) << ": " << lines[i] << "\n";
    }
    
    textFile.close();
    std::cout << "\nТекстовый файл успешно создан!\n";
}

void Files::printTextFile() {
    std::ifstream readFile(textFileName);
    if (!readFile) {
        throw std::runtime_error("Не удалось открыть текстовый файл");
    }
    
    std::string line;
    int lineNumber = 1;
    
    std::cout << "Содержание текстового файла " << textFileName << ":\n";
    std::cout << "Номер строки | Содержимое\n";
    std::cout << "---------------------------\n";
    
    while (std::getline(readFile, line)) {
        if (!line.empty()) {
            std::cout << lineNumber << "           | " << line << "\n";
            lineNumber++;
        }
    }
    
    readFile.close();
    std::cout << "\n";
}

bool Files::hasRussianLetters(const std::string &str) {
    std::string russianLetters = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    
    for (char c : str) {
        if (russianLetters.find(c) != std::string::npos) {
            return true;
        }
    }
    
    return false;
}

void Files::filterNoRussianLines() {
    std::ifstream inFile(textFileName);
    if (!inFile) {
        throw std::runtime_error("Не удалось открыть исходный текстовый файл");
    }

    std::ofstream outFile(textOutputFileName);
    if (!outFile) {
        throw std::runtime_error("Не удалось создать выходной файл");
    }
    
    std::string line;
    int lineNumber = 1;
    int writtenCount = 0;
    
    std::cout << "Анализ строк:\n";
    
    while (std::getline(inFile, line)) {
        bool hasRussian = hasRussianLetters(line);
        
        std::cout << "Строка " << lineNumber << ": \"" << line << "\" - ";
        
        if (hasRussian) {
            std::cout << "содержит русские буквы (пропуск)\n";
        } else {
            std::cout << "не содержит русских букв (записываем)\n";
            outFile << line << "\n";
            writtenCount++;
        }
        
        lineNumber++;
    }
    
    inFile.close();
    outFile.close();
    
    std::cout << "Результат сохранен в файле: " << textOutputFileName << "\n\n";
    
    std::cout << "Содержимое выходного файла " << textOutputFileName << ":\n";
    
    std::ifstream resultFile(textOutputFileName);
    if (resultFile) {
        lineNumber = 1;
        while (resultFile >> line) {
            std::cout << "Строка " << lineNumber << ": " << line << "\n";
            lineNumber++;
        }
        resultFile.close();
    }
    std::cout << "\n";
}