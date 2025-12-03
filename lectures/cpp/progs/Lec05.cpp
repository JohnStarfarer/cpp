//#include <cmath> 
//#include <iostream>
//
//
//double mySqrt(double x)
//{
//    if (x < 0.0)
//        throw "Can not take sqrt of negative number";
//
//    return std::sqrt(x);
//}
//
//int main()
//{
//    std::cout << "Enter a number: ";
//    double x{};
//    std::cin >> x;
//
//    try 
//    {   double d = mySqrt(x);
//        std::cout << "The sqrt of " << x << " is " << d << '\n';
//    }
//    catch (const char* exception) 
//    {
//        std::cerr << "Error: " << exception << std::endl;
//    }
//
//    return 0;
//}
////////////////////////////////////////////////////////
//#include <iostream>
//
//int main()
//{
//    try
//    {
//        throw 5; 
//    }
//    catch (double x)
//    {
//        std::cout << "We caught an exception of type double: " << x << '\n';
//    }
//    catch (...) 
//    {
//        std::cout << "We caught an exception of an undetermined type\n";
//    }
//}
///////////////

//#include <iostream>

//class Member
//{
//public:
//    Member()
//    {
//        std::cerr << "Member allocated some resources\n";
//    }

//    ~Member()
//    {
//        std::cerr << "Member cleaned up\n";
//    }
//};

//class A
//{
//private:
//    int m_x{};
//    Member m_member;

//public:
//    A(int x) : m_x{ x }
//    {
//        if (x <= 0)
//            throw 1;
//    }

//    ~A()
//    {
//        std::cerr << "~A\n"; 
//    }
//};


//int main()
//{
//    try
//    {
//        A a{ 0 };
//    }
//    catch (int)
//    {
//        std::cerr << "Oops\n";
//    }

//    return 0;
//}
//////////////////////////////
//#include <string>
//#include <string_view>
//#include <iostream>
//
//class ArrayException
//{
//private:
//    std::string m_error;
//
//public:
//    ArrayException(std::string error)
//        : m_error{ error }
//    {
//    }
//
//    std::string_view getError() const { return m_error; }
//};
//class IntArray
//{
//private:
//
//    int m_data[3]{}; 
//public:
//    IntArray() {}
//
//    int getLength() const { return 3; }
//
//    int& operator[](const int index)
//    {
//        if (index < 0 || index >= getLength())
//            throw ArrayException{ "Invalid index" };
//
//        return m_data[index];
//    }
//
//};
//
//int main()
//{
//    IntArray array;
//
//    try
//    {
//        int value{ array[5] }; 
//    }
//    catch (const ArrayException& exception)
//    {
//        std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
//    }
//}
//////////////
//#include <cstddef>   // для std::size_t
//#include <iostream>
//#include <exception> // для std::exception
//#include <limits>
//#include <string>    // для this example
//
//int main()
//{
//    try
//    {
//        // Здесь идет ваш код, использующий стандартную библиотеку.
//        // Для примера мы намеренно вызываем одно из ее исключений.
//        std::string s;
//        // вызовет исключение std::length_error или исключение выделения памяти
//        s.resize(std::numeric_limits<std::size_t>::max());
//    }
//    // Этот обработчик перехватит std::exception и все производные от него исключения
//    catch (const std::exception& exception)
//    {
//        std::cerr << "Standard exception: " << exception.what() << '\n';
//    }
//
//    return 0;
//}
//////////////////////
#include <exception> // для std::exception
#include <iostream>
#include <string>
#include <string_view>

class ArrayException : public std::exception
{
private:
    std::string m_error{}; 

public:
    ArrayException(std::string_view error)
        : m_error{ error }
    {
    }
    // std::exception::what() возвращает const char* !!!
    const char* what() const noexcept override { return m_error.c_str(); }
};


class IntArray
{
private:

    int m_data[3]{};
public:
    IntArray() {}

    int getLength() const { return 3; }

    int& operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw ArrayException("Invalid index");

        return m_data[index];
    }

};

int main()
{
    IntArray array;

    try
    {
        int value{ array[5] };
    }
    catch (const ArrayException& exception) // блоки catch с производными классами идут первыми !!!
    {
        std::cerr << "An array exception occurred (" << exception.what() << ")\n";
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
    }
}
