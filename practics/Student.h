#ifndef FUNC_H
#define FUNC_H

#include <iostream>

class Student {
  private:
    std::string name;
    int course;
    bool gender;

  public:
    // конструкторы
    // по умолчанию
    Student();
    
    // копирования
    Student(const Student&);

    // с параметрами
    Student(std::string,int,bool);

    // свойства
    std::string get_name();
    int get_course();
    bool get_gender();
    std::string set_name(std::string);
    int set_course(int);

    // методы
    void Print();
    void DeleteStudent();

};
#endif