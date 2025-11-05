//#include <iostream>
//using namespace std;
//
//class Person {
//    int id;
//    char name[100];
//
//public:
//    void set_p()
//    {
//        cout << "Enter the Id: ";
//        cin >> id;
//        cout << "Enter the Name: ";
//        cin >> name;
//    }
//
//    void display_p()
//    {
//        cout << endl << "Id: " << id << "\nName: " << name << endl;
//    }
//};
//
//class Student : private Person {
//    char course[50];
//    int fee;
//
//public:
//    void set_s()
//    {
//        set_p();
//        cout << "Enter the Course Name: ";
//        cin >> course;
//        cout << "Enter the Course Fee: ";
//        cin >> fee;
//    }
//
//    void display_s()
//    {
//        display_p();
//        cout << "Course: " << course << "\nFee: " << fee << endl;
//    }
//};
//
//int main()
//{
//    Student s;
//    s.set_s();
//    s.display_s();
//    return 0;
//}


///////////////////////////////////////////////////////////////////////////////
//#include<iostream>
//#include<string.h>
//using namespace std;
//
//class Person
//{
//    int id;
//    char name[100];
//
//public:
//    void set_p(int, char[]);
//    void display_p();
//};
//
//void Person::set_p(int id, char n[])
//{
//    this->id = id;
//    strcpy_s(this->name, n);
//}
//
//void Person::display_p()
//{
//    cout << endl << id << "\t" << name;
//}
//
//class Student : private Person
//{
//    char course[50];
//    int fee;
//public:
//    void set_s(int, char[], char[], int);
//    void display_s();
//};
//
//void Student::set_s(int id, char n[], char c[], int f)
//{
//    set_p(id, n);
//    strcpy_s(course, c);
//    fee = f;
//}
//
//
//void Student::display_s()
//{
//    display_p();
//    cout << "\t" << course << "\t" << fee;
//}
//
//int main()
//{
//    Student s;
//    char name[] = "Ram";
//    char course[] = "B.Tech";
//    s.set_s(1001, name, course, 2000);
//    s.display_s();
//    return 0;
//}
