#include <iostream>
#include <string>
using namespace std;

class Employee
{
public:
    string m_name{};
    int m_id{};
    double m_wage{};

    void print()
    {
        cout << "Name: " << m_name <<
                "  Id: " << m_id <<
                "  Wage: " << m_wage << '\n';
    }
};

int main()
{
    Employee jack{ "Jack", 1, 35.00 };
    Employee john{ "John", 2, 32.50 };

    jack.print();
    john.print();

    return 0;
}

class A {
public:
    int x;
 
protected:
    int y;
 
private:
    int z;
};
 
class B : public A {
    // x is public
    // y is protected
    // z is not accessible from B
};
 
class C : protected A {
    // x is protected
    // y is protected
    // z is not accessible from C
};
 
class D : private A // 'private' is default
{
    // x is private
    // y is private
    // z is not accessible from D
};

