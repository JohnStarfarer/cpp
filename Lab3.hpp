#ifndef LAB3_HPP
#define LAB3_HPP

#include <string>
#include <vector>
#include <iostream>

// Задание 1.4 (Время)
class Time {
public:
    Time(int totalSeconds);
    void print() const;
private:
    int secondsSinceMidnight;
};

// Задание 1.5 и 4.3 (Дом) 
class House {
public:
    House(int floors);
    void print() const;
private:
    const int floors; // нельзя изменить
};

// Задание 2.4 и 3.4 (Сотрудники и отделы) 
class Department;

class Employee {
public:
    Employee(const std::string& name, Department* dept);
    std::string getName() const;
    Department* getDepartment() const;
    void print() const;
private:
    std::string name;
    Department* department;
};

class Department {
public:
    Department(const std::string& name);
    void addEmployee(Employee* emp);
    void setBoss(Employee* emp);
    Employee* getBoss() const;
    std::string getName() const;
    const std::vector<Employee*>& getEmployees() const;
    void print() const;
private:
    std::string name;
    Employee* boss;
    std::vector<Employee*> employees;
};

// Задание 5.1 (Пистолет) 
class Gun {
public:
    Gun();               // 5 патронов
    Gun(int bullets);
    void shoot();
    void print() const;
private:
    int bullets;
};

#endif