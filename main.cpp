// main.cpp
#include "Laba2.h"

int main() {
    setlocale(LC_ALL, "Rus");

    bool flag = 1;
    int numTask = 0;
    std::cout << "Вариант №6" << std::endl;
    std::cout << "Список заданий: " << std::endl;
    std::cout << "------------------------------------- " << std::endl;
    std::cout << "|#1: 6 |#2: 7 |#3: 1 |#4: 7 |#5:  6 | " << std::endl;
    std::cout << "------------------------------------- " << std::endl;
    std::cout << "|#6: 6 |#7: 3 |#8: 1 |#9: 1 |#10: 2 | " << std::endl;
    std::cout << "------------------------------------- " << std::endl;

    while (flag) {
        std::cout << "\nЧтобы выйти укажите -1" << std::endl;
        std::cout << "Введите номер задания - ";
        std::cin >> numTask;

        if (numTask == -1) {
            break;
        }

        switch (numTask) {
            case 1: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 1: Дан дек с четным количеством элементов." << std::endl;
                std::cout << "Вывести первую половину в обратном порядке, затем вторую половину в обратном порядке." << std::endl;

                int n = 0;
                std::cout << "Введите четное количество элементов: ";
                while (!(std::cin >> n) || n <= 0 || n % 2 != 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное четное число: ";
                }

                std::deque<int> d(n);
                std::cout << "Заполните дек:" << std::endl;
                for (auto& x : d) std::cin >> x;

                PrintDequeHalvesReversed(d);
                break;
            }
            case 2: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 2: Вставить после каждого элемента вектора число -1." << std::endl;

                int n;
                std::cout << "Введите размер вектора: ";
                while (!(std::cin >> n) || n <= 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное число: ";
                }

                std::vector<int> v(n);
                std::cout << "Заполните вектор:" << std::endl;
                for (auto& x : v) std::cin >> x;

                InsertMinusOneAfterEach(v);

                std::cout << "Результат: ";
                for (int x : v) std::cout << x << " ";
                std::cout << std::endl;
                break;
            }
            case 3: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 3: Удалить средний элемент дека (нечетное количество элементов)." << std::endl;

                int n;
                std::cout << "Введите нечетное количество элементов (>=3): ";
                while (!(std::cin >> n) || n < 3 || n % 2 == 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите нечетное число >=3: ";
                }

                std::deque<int> d(n);
                std::cout << "Заполните дек:" << std::endl;
                for (auto& x : d) std::cin >> x;

                DeleteMiddleDeque(d);

                std::cout << "Результат: ";
                for (int x : d) std::cout << x << " ";
                std::cout << std::endl;
                break;
            }
            case 4: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 4: Записать в файл K символов '*'. Использовать алгоритм fill_n." << std::endl;

                std::string filename;
                int K;
                std::cout << "Введите имя файла: ";
                std::cin >> filename;
                std::cout << "Введите K (>0): ";
                while (!(std::cin >> K) || K <= 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное число: ";
                }

                WriteStarsToFile(filename, K);
                break;
            }
            case 5: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 5: Продублировать последний элемент списка, совпадающий с элементом из первой половины вектора." << std::endl;

                int nv, nl;
                std::cout << "Введите размер вектора (четный): ";
                while (!(std::cin >> nv) || nv <= 0 || nv % 2 != 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное четное число: ";
                }
                std::vector<int> v(nv);
                std::cout << "Заполните вектор:" << std::endl;
                for (auto& x : v) std::cin >> x;

                std::cout << "Введите размер списка: ";
                while (!(std::cin >> nl) || nl <= 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное число: ";
                }
                std::list<int> l(nl);
                std::cout << "Заполните список:" << std::endl;
                for (auto& x : l) std::cin >> x;

                DuplicateLastMatching(l, v);

                std::cout << "Результат (список): ";
                for (int x : l) std::cout << x << " ";
                std::cout << std::endl;
                break;
            }
            case 6: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 6: Циклический сдвиг списков L1 вправо, L2 влево на K позиций." << std::endl;

                int K;
                std::cout << "Введите K (0<K<10): ";
                while (!(std::cin >> K) || K <= 0 || K >= 10) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите число от 1 до 9: ";
                }

                int n1, n2;
                std::cout << "Введите размер первого списка (>=10): ";
                while (!(std::cin >> n1) || n1 < 10) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите число >=10: ";
                }
                std::list<int> L1(n1);
                std::cout << "Заполните L1:" << std::endl;
                for (auto& x : L1) std::cin >> x;

                std::cout << "Введите размер второго списка (>=10): ";
                while (!(std::cin >> n2) || n2 < 10) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите число >=10: ";
                }
                std::list<int> L2(n2);
                std::cout << "Заполните L2:" << std::endl;
                for (auto& x : L2) std::cin >> x;

                RotateLists(L1, L2, K);

                std::cout << "L1 после сдвига вправо: ";
                for (int x : L1) std::cout << x << " ";
                std::cout << "\nL2 после сдвига влево: ";
                for (int x : L2) std::cout << x << " ";
                std::cout << std::endl;
                break;
            }
            case 7: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 7: Вывести три наибольших элемента вектора в порядке убывания." << std::endl;

                int n;
                std::cout << "Введите размер вектора (>=3): ";
                while (!(std::cin >> n) || n < 3) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите число >=3: ";
                }
                std::vector<int> v(n);
                std::cout << "Заполните вектор:" << std::endl;
                for (auto& x : v) std::cin >> x;

                PrintTopThreeDescending(v);
                break;
            }
            case 8: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 8: Получить вектор средних арифметических соседних пар списка." << std::endl;

                int n;
                std::cout << "Введите размер списка (>=2): ";
                while (!(std::cin >> n) || n < 2) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите число >=2: ";
                }
                std::list<int> l(n);
                std::cout << "Заполните список:" << std::endl;
                for (auto& x : l) std::cin >> x;

                AverageAdjacentPairs(l);
                break;
            }
            case 9: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 9: Найти количество векторов из набора, содержащих все элементы V0 (без учета повторений)." << std::endl;

                int n0;
                std::cout << "Введите размер вектора V0: ";
                while (!(std::cin >> n0) || n0 <= 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное число: ";
                }
                std::vector<int> v0(n0);
                std::cout << "Заполните V0:" << std::endl;
                for (auto& x : v0) std::cin >> x;

                int N;
                std::cout << "Введите количество векторов в наборе N (>0): ";
                while (!(std::cin >> N) || N <= 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное число: ";
                }
                std::vector<std::vector<int>> vects(N);
                for (int i = 0; i < N; ++i) {
                    int sz;
                    std::cout << "Введите размер вектора V" << i+1 << " (не меньше " << n0 << "): ";
                    while (!(std::cin >> sz) || sz < n0) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Ошибка. Размер должен быть не меньше " << n0 << ": ";
                    }
                    vects[i].resize(sz);
                    std::cout << "Заполните V" << i+1 << ":" << std::endl;
                    for (auto& x : vects[i]) std::cin >> x;
                }

                CountVectorsContainingAll(v0, vects);
                break;
            }
            case 10: {
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Задание 10: Определить суммарную длину слов по первой букве." << std::endl;

                int n;
                std::cout << "Введите количество слов: ";
                while (!(std::cin >> n) || n <= 0) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка. Введите положительное число: ";
                }
                std::vector<std::string> words(n);
                std::cout << "Введите слова заглавными английскими буквами:" << std::endl;
                for (auto& w : words) std::cin >> w;

                SumLengthByFirstLetter(words);
                break;
            }
            default: {
                std::cout << "Такого задания нет." << std::endl;
            }
        }
    }
    return 0;
}