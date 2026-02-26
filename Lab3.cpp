#include "Lab3.hpp"
#include <iomanip>

// Задание 1.4 (Время)
Time::Time(int totalSeconds) : secondsSinceMidnight(totalSeconds) {}

void Time::print() const {
    int total = secondsSinceMidnight % (24 * 3600);
    int hours = total / 3600;
    int minutes = (total % 3600) / 60;
    int secs = total % 60;
    std::cout << std::setfill('0');
    std::cout << hours << ":"
              << std::setw(2) << minutes << ":"
              << std::setw(2) << secs;
    std::cout << std::setfill(' ');
}

// Задание 1.5 и 4.3 (Дом) 
House::House(int floors) : floors(floors) {}

void House::print() const {
    std::cout << "дом с " << floors << " ";
    int n = floors;
    if (n % 10 == 1 && n % 100 != 11)
        std::cout << "этажом";
    else
        std::cout << "этажами";
    std::cout << std::endl;
}

// Задание 2.4 и 3.4 (Сотрудники и отделы) 
Employee::Employee(const std::string& name, Department* dept)
    : name(name), department(dept) {
    if (department) {
        department->addEmployee(this);
    }
}

std::string Employee::getName() const { return name; }
Department* Employee::getDepartment() const { return department; }

void Employee::print() const {
    if (!department) {
        std::cout << name << " (не привязан к отделу)" << std::endl;
        return;
    }
    Employee* boss = department->getBoss();
    if (boss == this) {
        std::cout << name << " начальник отдела " << department->getName();
    } else {
        std::cout << name << " работает в отделе " << department->getName()
                  << ", начальник которого "
                  << (boss ? boss->getName() : "неизвестен");
    }
    std::cout << std::endl;
}

// Задание 2.4 и 3.4 (Сотрудники и отделы) 
Department::Department(const std::string& name) : name(name), boss(nullptr) {}

void Department::addEmployee(Employee* emp) {
    employees.push_back(emp);
}

void Department::setBoss(Employee* emp) {
    boss = emp;
}

Employee* Department::getBoss() const { return boss; }
std::string Department::getName() const { return name; }
const std::vector<Employee*>& Department::getEmployees() const { return employees; }

void Department::print() const {
    std::cout << "Отдел " << name << ", начальник: ";
    if (boss) std::cout << boss->getName();
    else std::cout << "не назначен";
    std::cout << ", сотрудников: " << employees.size() << std::endl;
}

// Gun 
Gun::Gun() : bullets(5) {}
Gun::Gun(int bullets) : bullets(bullets) {}

void Gun::shoot() {
    if (bullets > 0) {
        std::cout << "Бах!" << std::endl;
        --bullets;
    } else {
        std::cout << "Клац!" << std::endl;
    }
}

void Gun::print() const {
    std::cout << "Пистолет с " << bullets << " патрон";
    int n = bullets;
    if (n % 10 == 1 && n % 100 != 11)
        std::cout << "ом";
    else
        std::cout << "ами";
    std::cout << std::endl;
}