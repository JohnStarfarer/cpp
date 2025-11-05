//#include <iostream>
//using namespace std;
//
//class Complex {
//private:
//    int real, imag;
//
//public:
//    Complex(int r = 0, int i = 0)
//    {
//        real = r;
//        imag = i;
//    }
//
//    Complex operator+(Complex const& obj)
//    {
//        Complex res;
//        res.real = real + obj.real;
//        res.imag = imag + obj.imag;
//        return res;
//    }
//    void print() 
//    { 
//        cout << real << " + i" << imag << '\n'; 
//    }
//};
//
//int main()
//{
//    Complex c1{ 10, 5 }, c2{ 2, 4 };
//    Complex c3 = c1 + c2;
//
//    c3.print();
//}
////////////////////////////////////////////////////////////////
//#include <iostream>
//using namespace std;
//class Complex {
//private:
//    int real, imag;
//
//public:
//    Complex(int r = 0, int i = 0)
//    {
//        real = r;
//        imag = i;
//    }
//    void print() 
//    { 
//        cout << real << " + i" << imag << endl; 
//    }
//    
//    friend Complex operator+(Complex const& c1,
//        Complex const& c2);
//};
//Complex operator+(Complex const& c1, Complex const& c2)
//{
//    return Complex(c1.real + c2.real, c1.imag + c2.imag);
//}
//
//int main()
//{
//    Complex c1{ 10, 5 }, c2{ 2, 4 };
//    Complex c3 = c1 + c2;
//    c3.print();
//    return 0;
//}
////////////////////////////////////////////////////////////////
//#include <iostream>

//class Point
//{
//private:
//    double m_x{};
//    double m_y{};
//    double m_z{};
//
//public:
//    Point(double x = 0.0, double y = 0.0, double z = 0.0)
//        : m_x{ x }, m_y{ y }, m_z{ z }
//    {
//    }
//
//    friend std::ostream& operator<< (std::ostream& out, const Point& point);
//    friend std::istream& operator>> (std::istream& in, Point& point);
//};
//
//std::ostream& operator<< (std::ostream& out, const Point& point)
//{
//    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';
//    return out;
//}
//std::istream& operator>> (std::istream& in, Point& point)
//{
//    in >> point.m_x;
//    in >> point.m_y;
//    in >> point.m_z;
//    return in;
//}
//
//int main()
//{
//    std::cout << "Enter a point: \n";
//    Point point{};
//    std::cin >> point;
//    std::cout << "You entered: " << point << '\n';
//    return 0;
//}

////////////////////////////////////////////////////////////////
//#include <iostream>
//
//class Point
//{
//private:
//    double m_x, m_y, m_z;
//
//public:
//    Point(double x = 0.0, double y = 0.0, double z = 0.0) :
//        m_x{ x }, m_y{ y }, m_z{ z }
//    {
//    }
//
//    
//    Point operator- () const;
//    bool operator! () const;
//
//    double getX() const { return m_x; }
//    double getY() const { return m_y; }
//    double getZ() const { return m_z; }
//};
//
//Point Point::operator- () const
//{
//    return Point(-m_x, -m_y, -m_z);
//}
//
//bool Point::operator! () const
//{
//    return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);
//}
//
//int main()
//{
//    Point point{};
//
//    if (!point)
//        std::cout << "point is set at the origin.\n";
//    else
//        std::cout << "point is not set at the origin.\n";
//
//    return 0;
//}
////////////////////////////////////////////////////////////////
//#include <iostream>
//
//class Digit
//{
//private:
//    int m_digit;
//public:
//    Digit(int digit = 0)
//        : m_digit{ digit }
//    {
//    }
//    //префиксные
//
//    Digit& operator++();
//    Digit& operator--();
//    //постфиксные
//
//    Digit operator++(int); 
//    Digit operator--(int); 
//
//    friend std::ostream& operator<< (std::ostream& out, const Digit& d);
//};
//
//Digit& Digit::operator++()
//{
//    if (m_digit == 9)
//        m_digit = 0;
//    else ++m_digit;
//
//    return *this;
//}
//
//Digit& Digit::operator--()
//{
//    if (m_digit == 0)
//        m_digit = 9;
//    else --m_digit;
//
//    return *this;
//}
//Digit Digit::operator++(int)
//{
//    Digit temp{ *this };
//    ++(*this);
//    return temp;
//}
//
//Digit Digit::operator--(int)
//{
//    Digit temp{ *this };
//    --(*this); 
//    return temp; 
//}
//
//std::ostream& operator<< (std::ostream& out, const Digit& d)
//{
//    out << d.m_digit;
//    return out;
//}
//
//int main()
//{
//    Digit digit(9);
//
//    std::cout << digit;
//    std::cout << ++digit; 
//    std::cout << digit++; 
//    std::cout << digit;
//    std::cout << --digit; 
//    std::cout << digit--; 
//    std::cout << digit;
//
//    return 0;
//}
////////////////////////////////////////////////////////////////
//#include <iostream>
//
//class Money
//{
//private:
//    int m_rubles, m_kopecks;
//public:
//    Money(int rubles = 0, int kopecks = 0)
//        : m_rubles{ rubles }, m_kopecks{ kopecks }
//    {
//    }
//
//    operator int() const { return m_rubles * 100 + m_kopecks; }
//};
//
//
//int main()
//{
//    Money money{ 12, 34 };
//
//    int tmp = money;
//    
//
//    std::cout << tmp;
//
//    std::cout << '\n';
//
//    return 0;
//}