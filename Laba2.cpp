// Laba2.cpp
#include "Laba2.h"

// Задание 1: вывести первую половину дека в обратном порядке, затем вторую половину в обратном порядке
void PrintDequeHalvesReversed(std::deque<int>& d) {
    int n = d.size();
    int half = n / 2;
    auto mid = d.begin() + half;

    std::cout << "Первая половина в обратном порядке: ";
    for (auto it = std::reverse_iterator<decltype(mid)>(mid); it != std::reverse_iterator<decltype(d.begin())>(d.begin()); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\nВторая половина в обратном порядке: ";
    for (auto it = d.rbegin(); it != std::reverse_iterator<decltype(mid)>(mid); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Задание 2: вставить после каждого элемента вектора -1
void InsertMinusOneAfterEach(std::vector<int>& v) {
    for (auto i = v.begin(); i != v.end(); ++i) {
        i = v.insert(++i, -1);
    }
}

// Задание 3: удалить средний элемент дека
void DeleteMiddleDeque(std::deque<int>& d) {
    auto it = d.begin() + d.size() / 2;
    d.erase(it);
}

// Задание 4: записать K символов '*' в файл
void WriteStarsToFile(const std::string& name, int K) {
    std::ofstream file(name);
    if (!file) {
        std::cerr << "Не удалось открыть файл\n";
        return;
    }
    std::fill_n(std::ostream_iterator<char>(file), K, '*');
    file.close();
    std::cout << "Записано " << K << " символов '*' в файл " << name << std::endl;
}

// Задание 5: продублировать последний элемент списка, совпадающий с элементом из первой половины вектора
void DuplicateLastMatching(std::list<int>& l, const std::vector<int>& v) {
    auto v_mid = v.begin() + v.size() / 2;
    auto rit = std::find_first_of(l.rbegin(), l.rend(), v.begin(), v_mid);
    if (rit != l.rend()) {
        auto it = rit.base();
        l.insert(it, *rit);
    }
}

// Задание 6: циклический сдвиг списков
void RotateLists(std::list<int>& L1, std::list<int>& L2, int K) {
    if (!L1.empty()) {
        auto it1 = L1.begin();
        std::advance(it1, L1.size() - K);
        std::rotate(L1.begin(), it1, L1.end());
    }
    if (!L2.empty()) {
        auto it2 = L2.begin();
        std::advance(it2, K);
        std::rotate(L2.begin(), it2, L2.end());
    }
}

// Задание 7: вывести три наибольших элемента вектора в порядке убывания
void PrintTopThreeDescending(std::vector<int>& v) {
    std::partial_sort(v.begin(), v.begin() + 3, v.end(), std::greater<int>());
    std::cout << "Три наибольших элемента в порядке убывания: ";
    std::copy(v.begin(), v.begin() + 3, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

// Задание 8: среднее арифметическое соседних пар списка
void AverageAdjacentPairs(std::list<int>& l) {
    std::vector<double> V(l.size());
    std::adjacent_difference(l.begin(), l.end(), V.begin(),
                             [](int a, int b) { return (a + b) / 2.0; });
    V.erase(V.begin());
    std::cout << "Результат: ";
    for (double d : V) std::cout << d << " ";
    std::cout << std::endl;
}

// Задание 9: количество векторов, содержащих все элементы V0 (без учета повторений)
void CountVectorsContainingAll(std::vector<int> v0, std::vector<std::vector<int>> vects) {
    std::set<int> s0(v0.begin(), v0.end());
    int cnt = 0;
    for (const auto& vec : vects) {
        std::set<int> s(vec.begin(), vec.end());
        if (std::includes(s.begin(), s.end(), s0.begin(), s0.end()))
            ++cnt;
    }
    std::cout << "Количество векторов, содержащих все элементы V0: " << cnt << std::endl;
}

// Задание 10: суммарная длина слов по первой букве
void SumLengthByFirstLetter(std::vector<std::string> vect) {
    std::map<char, int> M;
    for (const auto& w : vect) {
        if (!w.empty())
            M[w[0]] += w.size();
    }
    std::cout << "Результат (буква и суммарная длина):\n";
    for (const auto& p : M) {
        std::cout << p.first << " " << p.second << std::endl;
    }
}