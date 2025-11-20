// QuadraticEquation.h, ЧУЕ
// Description: lab4.h
#ifndef QUADRATICEQUATION
#define QUADRATICEQUATION

#include <iostream>
#include <vector>
#include <cmath>

class QuadraticEquation {
public:
    QuadraticEquation();
    QuadraticEquation(const QuadraticEquation& quadeq);
    QuadraticEquation(double a, double b, double c);

    double get_a() const;
    double get_b() const;
    double get_c() const;

    friend std::ostream& operator<< (std::ostream& out, const QuadraticEquation& quadeq);

    std::vector<double> roots() const;

    QuadraticEquation& operator++();
    QuadraticEquation operator++(int);
    QuadraticEquation& operator--();
    QuadraticEquation operator--(int);

    operator double() const;
    explicit operator bool() const;
private:
    double a_;
    double b_;
    double c_;
};
bool operator== (const QuadraticEquation& quadL, const QuadraticEquation& quadR);
bool operator!= (const QuadraticEquation& quadL, const QuadraticEquation& quadR);

#endif