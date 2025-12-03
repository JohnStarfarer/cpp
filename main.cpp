// main.cpp, ЧЕИ
// Description: lab5, var6

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

class Files {
public:
static void genBin() {
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

            // "читай первый адрес '&num' не как начало 'int', а как начало массива из 'count' char'ов"
            // "затем запиши в файл 'count' байтов, начиная с первого адреса '&num'"
            primFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
            std::cout << num << " ";
        }
        std::cout << "\n\n";

        primFile.close();
    }

static void printBin(const std::string& filename = pFileName) {
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

    // 1.6 Переписать в другой файл последовательного доступа те элементы, которые кратны k.
    static void multiplesK(const std::string& filename = oFileName) {
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

        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Не удалось открыть выходной файл");
        }

        int num;
        std::cout << "Числа, кратные " << k << ": ";
        
        // читаем из исходного файла
        while (primFile.read(reinterpret_cast<char*>(&num), sizeof(int))) {
            // проверка кратности k
            if (num % k == 0) {
                // записываем в выходной файл
                outFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
                std::cout << num << " ";
            }
        }
        std::cout << std::endl;

        primFile.close();
        outFile.close();
    }

    static void binMatrix(const std::string& filename = oFileName) {
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
        
        std::ofstream outFile(filename, std::ios::binary);
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
        std::cout << "Матрица сохранена в файле: " << filename << "\n\n";
    }

private:
    static const char* pFileName;
    static const char* oFileName;
};

const char* Files::pFileName = "primary.bin";
const char* Files::oFileName = "output.bin";

int main() {
    try {
        Files::genBin();
        Files::multiplesK("1.6.bin");
        Files::printBin("1.6.bin");
        Files::binMatrix("2.6.bin");
        Files::printBin("2.6.bin");
    }
    catch (const std::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }
    
}