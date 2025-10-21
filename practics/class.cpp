#include <iostream>
#include "Student.h"

int main() {
    setlocale(LC_ALL, "rus");

    Student student1;
    Student student2("Oleg", 3, true);
    Student student3(student2);

    student1.Print();
    student2.Print();
    student3.Print();

    std::string name;
    int course;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Course: ";
    std::cin >> course;
    Student student4(name, course, false);
    student4.Print();

    return 0;
}