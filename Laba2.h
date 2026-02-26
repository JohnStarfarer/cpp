#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <iterator>
#include <fstream>
#include <string>

// Задание 1: вывести первую и вторую половины дека в обратном порядке
void PrintDequeHalvesReversed(std::deque<int>& d);

// Задание 2: вставить после каждого элемента вектора -1
void InsertMinusOneAfterEach(std::vector<int>& v);

// Задание 3: удалить средний элемент дека
void DeleteMiddleDeque(std::deque<int>& d);

// Задание 4: записать K символов '*' в файл
void WriteStarsToFile(const std::string& name, int K);

// Задание 5: продублировать последний элемент списка, совпадающий с элементом из первой половины вектора
void DuplicateLastMatching(std::list<int>& l, const std::vector<int>& v);

// Задание 6: циклический сдвиг списков L1 вправо, L2 влево на K позиций
void RotateLists(std::list<int>& L1, std::list<int>& L2, int K);

// Задание 7: вывести три наибольших элемента вектора в порядке убывания
void PrintTopThreeDescending(std::vector<int>& v);

// Задание 8: вычислить среднее арифметическое соседних пар списка
void AverageAdjacentPairs(std::list<int>& l);

// Задание 9: подсчитать количество векторов, содержащих все элементы V0 (без учета повторений)
void CountVectorsContainingAll(std::vector<int> v0, std::vector<std::vector<int>> vects);

// Задание 10: вывести суммарную длину слов по первой букве
void SumLengthByFirstLetter(std::vector<std::string> vect);