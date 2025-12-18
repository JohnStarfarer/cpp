#ifndef UNORDEREDLIST_HPP
#define UNORDEREDLIST_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>

/// <summary>
/// Шаблонный класс для реализации неупорядоченного списка с уникальными элементами.
/// </summary>
/// <typeparam name="T">Тип элементов списка.</typeparam>
/// <remarks>
/// Класс реализует функционал неупорядоченного списка, который может содержать
/// только уникальные элементы. Обращение к элементам по индексу не предусмотрено.
/// </remarks>
template<typename T>
class UnorderedList {
public:
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="UnorderedList{T}"/> с начальной емкостью 10.
    /// </summary>
    UnorderedList();
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="UnorderedList{T}"/> с заданной емкостью.
    /// </summary>
    /// <param name="capacity">Начальная емкость списка.</param>
    /// <exception cref="std::invalid_argument">Вызывается, если capacity <= 0.</exception>
    UnorderedList(int capacity);
    
    /// <summary>
    /// Инициализирует новый экземпляр класса <see cref="UnorderedList{T}"/>, который является копией указанного списка.
    /// </summary>
    /// <param name="list">Список для копирования.</param>
    UnorderedList(const UnorderedList& list);
    
    /// <summary>
    /// Освобождает все ресурсы, используемые классом <see cref="UnorderedList{T}"/>.
    /// </summary>
    ~UnorderedList();

    /// <summary>
    /// Присваивает текущему списку значения другого списка.
    /// </summary>
    /// <param name="other">Список для присваивания.</param>
    /// <returns>Ссылка на текущий объект.</returns>
    UnorderedList<T>& operator=(const UnorderedList<T>& other);

    /// <summary>
    /// Добавляет элемент в список.
    /// </summary>
    /// <param name="item">Элемент для добавления.</param>
    /// <remarks>
    /// Если элемент уже существует в списке, он не добавляется.
    /// </remarks>
    void Add(const T& item);
    
    /// <summary>
    /// Удаляет элемент из списка.
    /// </summary>
    /// <param name="item">Элемент для удаления.</param>
    /// <returns>true, если элемент был найден и удален; в противном случае — false.</returns>
    bool Remove(const T& item);
    
    /// <summary>
    /// Проверяет наличие элемента в списке.
    /// </summary>
    /// <param name="item">Элемент для проверки.</param>
    /// <returns>true, если элемент существует в списке; в противном случае — false.</returns>
    bool Contains(const T& item) const;

    /// <summary>
    /// Объединяет два списка.
    /// </summary>
    /// <param name="list">Список для объединения.</param>
    /// <returns>Новый список-результат объединения.</returns>
    /// <remarks>
    /// Создает новый список, содержащий все уникальные элементы из текущего
    /// списка и списка-аргумента.
    /// </remarks>
    UnorderedList<T> Union(const UnorderedList<T>& list) const;
    
    /// <summary>
    /// Вычитает элементы другого списка из текущего.
    /// </summary>
    /// <param name="list">Список для вычитания.</param>
    /// <returns>Новый список-результат вычитания.</returns>
    /// <remarks>
    /// Создает новый список, содержащий элементы текущего списка,
    /// которых нет в списке-аргументе.
    /// </remarks>
    UnorderedList<T> Except(const UnorderedList<T>& list) const;
    
    /// <summary>
    /// Находит пересечение двух списков.
    /// </summary>
    /// <param name="list">Список для нахождения пересечения.</param>
    /// <returns>Новый список-результат пересечения.</returns>
    /// <remarks>
    /// Создает новый список, содержащий элементы, которые есть
    /// и в текущем списке, и в списке-аргументе.
    /// </remarks>
    UnorderedList<T> Intersect(const UnorderedList<T>& list) const;

    /// <summary>
    /// Возвращает количество элементов в списке.
    /// </summary>
    /// <returns>Количество элементов.</returns>
    int count() const { return count_; };
    
    /// <summary>
    /// Возвращает текущую емкость списка.
    /// </summary>
    /// <returns>Емкость списка.</returns>
    int capacity() const { return capacity_; };

    /// <summary>
    /// Выводит содержимое списка в стандартный вывод.
    /// </summary>
    void Print() const;
    
private:
    T* items_;
    int count_;
    int capacity_;

    /// <summary>
    /// Увеличивает емкость массива при необходимости.
    /// </summary>
    /// <remarks>
    /// Удваивает емкость массива, если текущее количество элементов
    /// достигло предельной емкости.
    /// </remarks>
    void AddCapacity();
};

template<typename T>
UnorderedList<T>::UnorderedList() : count_(0), capacity_(10) 
{
    items_ = new T[capacity_];
}

template<typename T>
UnorderedList<T>::UnorderedList(int capacity) : count_(0), capacity_(capacity)
{
    if (capacity <= 0) {
        throw std::invalid_argument("Размер списка должен быть > 0");
    }
    items_ = new T[capacity_];
}

template<typename T>
UnorderedList<T>::UnorderedList(const UnorderedList& list) : count_(list.count_), capacity_(list.capacity_)
{
    items_ = new T[capacity_];
    for (int i = 0; i < count_; i++) {
        items_[i] = list.items_[i];
    }
}

template<typename T>
UnorderedList<T>::~UnorderedList()
{
    delete[] items_;
}

template<typename T>
void UnorderedList<T>::AddCapacity()
{
    if (count_ >= capacity_) {
        int new_cap = capacity_ * 2;
        T* new_items = new T[new_cap];

        for (int i = 0; i < count_; i++) {
            new_items[i] = items_[i];
        }

        delete[] items_;

        items_ = new_items;
        capacity_ = new_cap;
    }
}

template<typename T>
void UnorderedList<T>::Add(const T& item)
{
    if (Contains(item)) {
        return;
    }

    AddCapacity();
    items_[count_] = item;
    count_++;
}

template<typename T>
bool UnorderedList<T>::Remove(const T& item)
{
    for (int i = 0; i < count_; i++) {
        if (items_[i] == item) {
            for (int j = i; j < count_ - 1; j++) {
                items_[j] = items_[j + 1];
            }
            items_[count_ - 1] = T();
            count_--;
            return true;
        }
    }
    return false;
}

template<typename T>
bool UnorderedList<T>::Contains(const T& item) const
{
    for (int i = 0; i < count_; i++) {
        if (items_[i] == item) {
            return true;
        }
    }
    return false;
}

template<typename T>
UnorderedList<T> UnorderedList<T>::Union(const UnorderedList<T>& list) const
{
    UnorderedList<T> res(count_ + list.count_);

    for (int i = 0; i < count_; i++) {
        res.Add(items_[i]);
    }

    for (int i = 0; i < list.count_; i++) {
        res.Add(list.items_[i]);
    }

    return res;
}

template<typename T>
UnorderedList<T> UnorderedList<T>::Except(const UnorderedList<T>& list) const
{
    UnorderedList<T> res(count_);

    for (int i = 0; i < count_; i++) {
        if (!list.Contains(items_[i])) {
            res.Add(items_[i]);
        }
    }
    return res;
}

template<typename T>
UnorderedList<T> UnorderedList<T>::Intersect(const UnorderedList<T>& list) const
{
    UnorderedList<T> res(std::min(count_, list.count_));

    for (int i = 0; i < count_; ++i) {
        if (list.Contains(items_[i])) {
            res.Add(items_[i]);
        }
    }
    return res;
}

template<typename T>
void UnorderedList<T>::Print() const {
    std::cout << "[";
    for (int i = 0; i < count_; i++) {
        std::cout << items_[i];
        if (i < count_ - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

template<typename T>
UnorderedList<T>& UnorderedList<T>::operator=(const UnorderedList<T>& list) {
    if (this != &list) {
        delete[] items_;
        count_ = list.count_;
        capacity_ = list.capacity_;
        items_ = new T[capacity_];
        for (int i = 0; i < count_; i++) {
            items_[i] = list.items_[i];
        }
    }
    return *this;
}

#endif