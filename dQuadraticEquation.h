#ifndef QUADRATICEQUATION_H
#define QUADRATICEQUATION_H

#include <iostream>
#include <vector>

class QuadraticEquation {
private:
    double a, b, c;
public:
    QuadraticEquation();
    QuadraticEquation(double a, double b, double c);
    QuadraticEquation(const QuadraticEquation& other);
    
    double getA() const;
    double getB() const;
    double getC() const;
    
    void setA(double a);
    void setB(double b);
    void setC(double c);
    
    std::vector<double> solve() const;
    friend std::ostream& operator<<(std::ostream& os, const QuadraticEquation& eq);
};

#endif