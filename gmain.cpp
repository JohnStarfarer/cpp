// main.cpp, ЧЕИ
// Description: lab

#include <iostream>
#include <cmath> // Required for sqrt() function

int main() {
    double a, b, c;
    double discriminant, root1, root2;

    std::cout << "Enter coefficients a, b, and c for the quadratic equation (ax^2 + bx + c = 0): " << std::endl;
    std::cout << "a: ";
    std::cin >> a;
    std::cout << "b: ";
    std::cin >> b;
    std::cout << "c: ";
    std::cin >> c;

    // Check if it's a valid quadratic equation (a cannot be 0)
    if (a == 0) {
        std::cout << "Error: 'a' cannot be zero for a quadratic equation." << std::endl;
        return 1; // Indicate an error
    }

    // Calculate the discriminant
    discriminant = b * b - 4 * a * c;

    // Determine the nature of the roots based on the discriminant
    if (discriminant > 0) {
        // Real and different roots
        root1 = (-b + std::sqrt(discriminant)) / (2 * a);
        root2 = (-b - std::sqrt(discriminant)) / (2 * a);
        std::cout << "Roots are real and different." << std::endl;
        std::cout << "Root 1 = " << root1 << std::endl;
        std::cout << "Root 2 = " << root2 << std::endl;
    } else if (discriminant == 0) {
        // Real and equal roots
        root1 = -b / (2 * a);
        std::cout << "Roots are real and equal." << std::endl;
        std::cout << "Root 1 = Root 2 = " << root1 << std::endl;
    } else {
        // Complex roots
        double realPart = -b / (2 * a);
        double imaginaryPart = std::sqrt(-discriminant) / (2 * a);
        std::cout << "Roots are complex and different." << std::endl;
        std::cout << "Root 1 = " << realPart << " + " << imaginaryPart << "i" << std::endl;
        std::cout << "Root 2 = " << realPart << " - " << imaginaryPart << "i" << std::endl;
    }

    return 0; // Indicate successful execution
}