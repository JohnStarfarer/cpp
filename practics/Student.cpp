#include "Student.h"

Student::Student()
{
    name = "Ivan";
    course = 1;
    gender = true;
}

Student::Student(const Student& student)
{
    // this->name = student.name;
    name = student.name;
    course = student.course;
    gender = student.gender;
}

Student::Student(std::string name, int course, bool gender)
{
    set_name(name);
    set_course(course);
    this->gender = gender;
}

std::string Student::get_name()
{
    return name;
}

int Student::get_course()
{
    return course;
}

bool Student::get_gender()
{
    return gender;
}

std::string Student::set_name(std::string name)
{
    this->name = name;
}

int Student::set_course(int course)
{
    if (course >= 1 && course <= 6) {
        this->course = course;
    } else {
        std::cout << "Nope" << std::endl;
        this->course = 1;
    }
    this->name = course;
}

void Student::Print()
{
    std::cout << name << " " << course << " курс " << gender << std::endl;
}

