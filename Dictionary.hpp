#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <fstream>

template<typename KeyType, typename ValueType>
class Dictionary {
public:
    Dictionary(int initialCapacity = 16) 
        : capacity_(initialCapacity), size_(0) {
        table = new KeyValuePair*[capacity_]();
        for (int i = 0; i < capacity_; i++) {
            table[i] = nullptr;
        }
    }
    
    Dictionary(const Dictionary& other) 
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
    
    ~Dictionary() {
        clear();
        delete[] table;
    }
    
    Dictionary& operator=(const Dictionary& other) {
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
    
    void Add(const KeyType& key, const ValueType& value) {
        if (ContainsKey(key)) {
            // Ключ уже существует - обновляем значение
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
    
    bool Remove(const KeyType& key) {
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
    
    bool ContainsKey(const KeyType& key) const {
        return findPair(key) != nullptr;
    }
    
    ValueType* Get(const KeyType& key) {
        KeyValuePair* pair = findPair(key);
        return pair ? &pair->value : nullptr;
    }
    
    const ValueType* Get(const KeyType& key) const {
        KeyValuePair* pair = findPair(key);
        return pair ? &pair->value : nullptr;
    }
    
    int size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    void clear() {
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
    
    void Print() const {
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

private:
    struct KeyValuePair {
        KeyType key;
        ValueType value;
        KeyValuePair* next;
        
        KeyValuePair(const KeyType& k, const ValueType& v) 
            : key(k), value(v), next(nullptr) {}
    };
    
    KeyValuePair** table;
    int capacity_;
    int size_;
    
    int hash(const KeyType& key) const {
        std::hash<KeyType> hasher;
        return hasher(key) % capacity_;
    }
    
    void rehash() {
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
    

    
private:
    KeyValuePair* findPair(const KeyType& key) const {
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
};

// информация о ученике
struct Student {
    std::string lastName;
    std::string firstName;
    int schoolNumber;
    int score;
    
    Student() : schoolNumber(0), score(0) {}
    Student(const std::string& ln, const std::string& fn, int sn, int s)
        : lastName(ln), firstName(fn), schoolNumber(sn), score(s) {}
};

// статистики о школе
struct SchoolStats {
    double totalScore;
    int studentCount;
    
    SchoolStats() : totalScore(0), studentCount(0) {}
    void addScore(double score) {
        totalScore += score;
        studentCount++;
    }
    double averageScore() const {
        return studentCount > 0 ? totalScore / studentCount : 0;
    }
};

#endif