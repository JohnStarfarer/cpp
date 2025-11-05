#include "QuadraticEquation.h"
#include <cmath>
#include <stdexcept>
#include <iostream> // добавлен для cout
#include <cmath>    // добавлен для fabs

using namespace std;

QuadraticEquation::QuadraticEquation() : a(1), b(0), c(0) {}

QuadraticEquation::QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {
    if (a == 0) throw invalid_argument("Coefficient 'a' cannot be zero");
}

QuadraticEquation::QuadraticEquation(const QuadraticEquation& other) 
    : a(other.a), b(other.b), c(other.c) {}

double QuadraticEquation::getA() const { return a; }
double QuadraticEquation::getB() const { return b; }
double QuadraticEquation::getC() const { return c; }

void QuadraticEquation::setA(double a) { 
    if (a == 0) throw invalid_argument("Coefficient 'a' cannot be zero");
    this->a = a; 
}

void QuadraticEquation::setB(double b) { this->b = b; }
void QuadraticEquation::setC(double c) { this->c = c; }

vector<double> QuadraticEquation::solve() const {
    vector<double> roots;
    
    if (a == 0) {
        if (b == 0) {
            if (c == 0) roots.push_back(0); // Бесконечное число корней
            return roots;
        }
        roots.push_back(-c / b);
        return roots;
    }
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        roots.push_back((-b - sqrt(discriminant)) / (2 * a));
        roots.push_back((-b + sqrt(discriminant)) / (2 * a));
    } 
    else if (discriminant == 0) {
        roots.push_back(-b / (2 * a));
    }
    
    return roots;
}

ostream& operator<<(ostream& os, const QuadraticEquation& eq) {
    os << eq.a << "x^2 ";
    os << (eq.b >= 0 ? "+ " : "- ") << fabs(eq.b) << "x ";
    os << (eq.c >= 0 ? "+ " : "- ") << fabs(eq.c) << " = 0";
    return os;
}