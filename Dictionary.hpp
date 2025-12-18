// Dictionary.hpp, ЧЕИ
// Description: lab6, var6
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <fstream>

/// <summary>
/// Шаблонный класс для реализации словаря (хэш-таблицы) с уникальными ключами.
/// </summary>
/// <typeparam name="KeyType">Тип ключей словаря.</typeparam>
/// <typeparam name="ValueType">Тип значений словаря.</typeparam>
/// <remarks>
/// Класс реализует словарь на основе хэш-таблицы.
/// Поддерживает основные операции: добавление, удаление, поиск.
/// </remarks>
template<typename KeyType, typename ValueType>
class Dictionary {
public:
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="Dictionary{KeyType, ValueType}"/> с указанной начальной емкостью.
    /// </summary>
    /// <param name="initialCapacity">Начальная емкость хэш-таблицы.</param>
    Dictionary(int initialCapacity = 16);
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="Dictionary{KeyType, ValueType}"/>, который является копией указанного словаря.
    /// </summary>
    /// <param name="other">Словарь для копирования.</param>
    Dictionary(const Dictionary& other);
    
    /// <summary>
    /// Освобождает все ресурсы, используемые классом <see cref="Dictionary{KeyType, ValueType}"/>.
    /// </summary>
    ~Dictionary();
    
    /// <summary>
    /// Присваивает текущему словарю значения другого словаря.
    /// </summary>
    /// <param name="other">Словарь для присваивания.</param>
    /// <returns>Ссылка на текущий объект.</returns>
    Dictionary& operator=(const Dictionary& other);
    
    /// <summary>
    /// Добавляет пару ключ-значение в словарь.
    /// </summary>
    /// <param name="key">Ключ для добавления.</param>
    /// <param name="value">Значение для добавления.</param>
    /// <remarks>
    /// Если ключ уже существует, обновляет его значение.
    /// </remarks>
    void Add(const KeyType& key, const ValueType& value);
    
    /// <summary>
    /// Удаляет пару ключ-значение из словаря.
    /// </summary>
    /// <param name="key">Ключ для удаления.</param>
    /// <returns>true, если ключ был найден и удален; в противном случае — false.</returns>
    bool Remove(const KeyType& key);
    
    /// <summary>
    /// Проверяет наличие ключа в словаре.
    /// </summary>
    /// <param name="key">Ключ для проверки.</param>
    /// <returns>true, если ключ существует; в противном случае — false.</returns>
    bool ContainsKey(const KeyType& key) const;
    
    /// <summary>
    /// Возвращает значение по ключу.
    /// </summary>
    /// <param name="key">Ключ для поиска.</param>
    /// <returns>Указатель на значение или nullptr, если ключ не найден.</returns>
    ValueType* Get(const KeyType& key);
    
    /// <summary>
    /// Возвращает значение по ключу (константная версия).
    /// </summary>
    /// <param name="key">Ключ для поиска.</param>
    /// <returns>Указатель на значение или nullptr, если ключ не найден.</returns>
    const ValueType* Get(const KeyType& key) const;
    
    /// <summary>
    /// Возвращает количество элементов в словаре.
    /// </summary>
    /// <returns>Количество элементов.</returns>
    int size() const { return size_; }
    
    /// <summary>
    /// Проверяет, пуст ли словарь.
    /// </summary>
    /// <returns>true, если словарь пуст; в противном случае — false.</returns>
    bool empty() const { return size_ == 0; }
    
    /// <summary>
    /// Очищает словарь.
    /// </summary>
    void clear();
    
    /// <summary>
    /// Выводит содержимое словаря в стандартный вывод.
    /// </summary>
    void Print() const;

private:
    /// <summary>
    /// Структура для хранения пары ключ-значение.
    /// </summary>
    struct KeyValuePair {
        KeyType key;
        ValueType value;
        KeyValuePair* next;
        
        /// <summary>
        /// Инициализирует новый экземпляр структуры <see cref="KeyValuePair"/>.
        /// </summary>
        /// <param name="k">Ключ.</param>
        /// <param name="v">Значение.</param>
        KeyValuePair(const KeyType& k, const ValueType& v);
    };
    
    KeyValuePair** table;
    int capacity_;
    int size_;
    
    /// <summary>
    /// Вычисляет хэш ключа.
    /// </summary>
    /// <param name="key">Ключ для хэширования.</param>
    /// <returns>Индекс в таблице.</returns>
    int hash(const KeyType& key) const;
    
    /// <summary>
    /// Перехэширует таблицу при достижении коэффициента загрузки 0.75.
    /// </summary>
    void rehash();
    
    /// <summary>
    /// Находит пару ключ-значение по ключу.
    /// </summary>
    /// <param name="key">Ключ для поиска.</param>
    /// <returns>Указатель на найденную пару или nullptr.</returns>
    KeyValuePair* findPair(const KeyType& key) const;
};

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::Dictionary(int initialCapacity) 
    : capacity_(initialCapacity), size_(0) {
    table = new KeyValuePair*[capacity_]();
    for (int i = 0; i < capacity_; i++) {
        table[i] = nullptr;
    }
}

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::Dictionary(const Dictionary& other) 
    : capacity_(other.capacity_), size_(0) {
    table = new KeyValuePair*[capacity_]();
    for (int i = 0; i < capacity_; i++) {
        table[i] = nullptr;
    }
    
    for (int i = 0; i < other.capacity_; i++) {
        KeyValuePair* current = other.table[i];
        while (current) {
            Add(current->key, current->value);
            current = current->next;
        }
    }
}

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::~Dictionary() {
    clear();
    delete[] table;
}

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>& Dictionary<KeyType, ValueType>::operator=(const Dictionary& other) {
    if (this != &other) {
        clear();
        delete[] table;
        
        capacity_ = other.capacity_;
        size_ = 0;
        table = new KeyValuePair*[capacity_]();
        for (int i = 0; i < capacity_; i++) {
            table[i] = nullptr;
        }
        
        for (int i = 0; i < other.capacity_; i++) {
            KeyValuePair* current = other.table[i];
            while (current) {
                Add(current->key, current->value);
                current = current->next;
            }
        }
    }
    return *this;
}

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::KeyValuePair::KeyValuePair(const KeyType& k, const ValueType& v) 
    : key(k), value(v), next(nullptr) {}

template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::Add(const KeyType& key, const ValueType& value) {
    if (ContainsKey(key)) {
        KeyValuePair* pair = findPair(key);
        if (pair) {
            pair->value = value;
        }
        return;
    }
    
    if (size_ >= capacity_ * 0.75) {
        rehash();
    }
    
    int index = hash(key);
    KeyValuePair* newPair = new KeyValuePair(key, value);
    newPair->next = table[index];
    table[index] = newPair;
    size_++;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Remove(const KeyType& key) {
    int index = hash(key);
    KeyValuePair* current = table[index];
    KeyValuePair* prev = nullptr;
    
    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table[index] = current->next;
            }
            delete current;
            size_--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::ContainsKey(const KeyType& key) const {
    return findPair(key) != nullptr;
}

template<typename KeyType, typename ValueType>
ValueType* Dictionary<KeyType, ValueType>::Get(const KeyType& key) {
    KeyValuePair* pair = findPair(key);
    return pair ? &pair->value : nullptr;
}

template<typename KeyType, typename ValueType>
const ValueType* Dictionary<KeyType, ValueType>::Get(const KeyType& key) const {
    KeyValuePair* pair = findPair(key);
    return pair ? &pair->value : nullptr;
}

template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::clear() {
    for (int i = 0; i < capacity_; i++) {
        KeyValuePair* current = table[i];
        while (current) {
            KeyValuePair* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    size_ = 0;
}

template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::Print() const {
    std::cout << "Dictionary (size: " << size_ << "):\n";
    for (int i = 0; i < capacity_; i++) {
        KeyValuePair* current = table[i];
        while (current) {
            std::cout << "Key: " << current->key 
                      << ", Value: " << current->value << std::endl;
            current = current->next;
        }
    }
}

template<typename KeyType, typename ValueType>
int Dictionary<KeyType, ValueType>::hash(const KeyType& key) const {
    std::hash<KeyType> hasher;
    return hasher(key) % capacity_;
}

template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::rehash() {
    int oldCapacity = capacity_;
    capacity_ *= 2;
    KeyValuePair** newTable = new KeyValuePair*[capacity_]();
    
    for (int i = 0; i < oldCapacity; i++) {
        KeyValuePair* current = table[i];
        while (current) {
            KeyValuePair* next = current->next;
            int newIndex = hash(current->key);
            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            current = next;
        }
    }
    
    delete[] table;
    table = newTable;
}

template<typename KeyType, typename ValueType>
typename Dictionary<KeyType, ValueType>::KeyValuePair* 
Dictionary<KeyType, ValueType>::findPair(const KeyType& key) const {
    int index = hash(key);
    KeyValuePair* current = table[index];
    
    while (current) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

/// <summary>
/// Структура для хранения информации об ученике.
/// </summary>
struct Student {
    std::string lastName;
    std::string firstName;
    int schoolNumber;
    int score;
    
    /// <summary>
    /// Инициализирует новый экземпляр структуры <see cref="Student"/>.
    /// </summary>
    Student();
    
    /// <summary>
    /// Инициализирует новый экземпляр структуры <see cref="Student"/> с указанными значениями.
    /// </summary>
    /// <param name="ln">Фамилия.</param>
    /// <param name="fn">Имя.</param>
    /// <param name="sn">Номер школы.</param>
    /// <param name="s">Балл.</param>
    Student(const std::string& ln, const std::string& fn, int sn, int s);
};

/// <summary>
/// Структура для хранения статистики школы.
/// </summary>
struct SchoolStats {
    double totalScore;
    int studentCount;
    
    /// <summary>
    /// Инициализирует новый экземпляр структуры <see cref="SchoolStats"/>.
    /// </summary>
    SchoolStats();
    
    /// <summary>
    /// Добавляет балл ученика в статистику.
    /// </summary>
    /// <param name="score">Балл ученика.</param>
    void addScore(double score);
    
    /// <summary>
    /// Вычисляет средний балл школы.
    /// </summary>
    /// <returns>Средний балл или 0, если нет учеников.</returns>
    double averageScore() const;
};

inline Student::Student() : schoolNumber(0), score(0) {}

inline Student::Student(const std::string& ln, const std::string& fn, int sn, int s)
    : lastName(ln), firstName(fn), schoolNumber(sn), score(s) {}

inline SchoolStats::SchoolStats() : totalScore(0), studentCount(0) {}

inline void SchoolStats::addScore(double score) {
    totalScore += score;
    studentCount++;
}

inline double SchoolStats::averageScore() const {
    return studentCount > 0 ? totalScore / studentCount : 0;
}

#endif