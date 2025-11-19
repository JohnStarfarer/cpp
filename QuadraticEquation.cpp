// QuadraticEquation.cpp, ЧУЕ
// Description: lab4.h.cpp
#include "QuadraticEquation.h"

QuadraticEquation::QuadraticEquation(): a_(0), b_(0), c_(0) {}

QuadraticEquation::QuadraticEquation(const QuadraticEquation &quadeq) : a_(quadeq.a_), b_(quadeq.b_), c_(quadeq.c_) {}

QuadraticEquation::QuadraticEquation(double a, double b, double c) : a_(a), b_(b), c_(c) {}

double QuadraticEquation::get_a() const { return a_; }

double QuadraticEquation::get_b() const { return b_; }

double QuadraticEquation::get_c() const { return c_; }

std::vector<double> QuadraticEquation::roots() const
{
    std::vector<double> vRoots;
    
    // a = 0 -- уравнение линейное
    if (a_ == 0) {
        if (b_ != 0) {
            // только один корень
            vRoots.push_back(-c_ / b_);
        }
        // a = b = 0 -- нет корней
        return vRoots;
    }
    
    double d = b_ * b_ - 4 * a_ * c_;
    
    if (d > 0) {
        double sqrt_d = std::sqrt(d);
        vRoots.push_back((-b_ - sqrt_d) / (2 * a_));
        vRoots.push_back((-b_ + sqrt_d) / (2 * a_));
    } else if (d == 0) {
        vRoots.push_back(-b_ / (2 * a_));
    }
    // d < 0 -- нет корней

    return vRoots;
}

QuadraticEquation &QuadraticEquation::operator++()
{
    a_++;
    b_++;
    c_++;
    return *this;
}

QuadraticEquation QuadraticEquation::operator++(int)
{
    QuadraticEquation quadeq = *this;
    ++(*this);
    return quadeq;
}

QuadraticEquation &QuadraticEquation::operator--()
{
    a_--;
    b_--;
    c_--;
    return *this;
}

QuadraticEquation QuadraticEquation::operator--(int)
{
    QuadraticEquation quadeq = *this;
    --(*this);
    return quadeq;
}

QuadraticEquation::operator double() const
{
    double d = b_ * b_ - 4 * a_ * c_;
    return d;
}

QuadraticEquation::operator bool() const
{
    double d = b_ * b_ - 4 * a_ * c_;
    return (d >= 0 ? true : false); // bool(0.0) -- false !!!
}

std::ostream &operator<<(std::ostream &out, const QuadraticEquation &quadeq)
{
    out << "Квадратное уравнение: "; // << quadeq.a_ << " * x^2 + " << quadeq.b_ << " * x + " << quadeq.c_ << " = 0";
    if (not(quadeq.a_ || quadeq.b_ || quadeq.c_)) {
        out << "0";
        return out;
    }
    if (quadeq.a_) out << quadeq.a_ << "x^2";
    if (quadeq.b_ < 0) {
        out << " - " << -quadeq.b_ << "x";
    } else if (quadeq.b_ > 0) {
                out << " + " << quadeq.b_ << "x";
            }
    if (quadeq.c_ < 0) {
        out << " - " << -quadeq.c_;
    } else if (quadeq.c_ > 0) {
                out << " + " << quadeq.c_;
            }
    out << " = 0";

    return out;
}

bool operator==(const QuadraticEquation &quadL, const QuadraticEquation &quadR)
{
    if ((quadL.get_a() == quadR.get_a()) && (quadL.get_b() == quadR.get_b()) && (quadL.get_c() == quadR.get_c())) {
        return true;
    } else {
        return false;
    }
}

bool operator!=(const QuadraticEquation &quadL, const QuadraticEquation &quadR)
{
    if ((quadL.get_a() != quadR.get_a()) || (quadL.get_b() != quadR.get_b()) || (quadL.get_c() != quadR.get_c())) {
        return true;
    } else {
        return false;
    }
}
