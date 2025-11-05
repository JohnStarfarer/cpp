#include <iostream>
#include <vector>
#include <limits> // добавляем для numeric_limits
#include "QuadraticEquation.h"

using namespace std;

double inputCoefficient(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            break;
        } else {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            // Используем std::numeric_limits<std::streamsize>::max()
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return value;
}

int main() {
    try {
        cout << "Default constructor test:" << endl;
        QuadraticEquation eq1;
        cout << "Equation: " << eq1 << endl;
        vector<double> roots = eq1.solve();
        cout << "Roots: ";
        for (double root : roots) cout << root << " ";
        cout << endl << endl;

        cout << "Parameterized constructor test:" << endl;
        double a = inputCoefficient("Enter coefficient a: ");
        double b = inputCoefficient("Enter coefficient b: ");
        double c = inputCoefficient("Enter coefficient c: ");
        
        QuadraticEquation eq2(a, b, c);
        cout << "Equation: " << eq2 << endl;
        roots = eq2.solve();
        cout << "Roots: ";
        for (double root : roots) cout << root << " ";
        cout << endl << endl;

        cout << "Copy constructor test:" << endl;
        QuadraticEquation eq3 = eq2;
        cout << "Copied equation: " << eq3 << endl;
        roots = eq3.solve();
        cout << "Roots: ";
        for (double root : roots) cout << root << " ";
        cout << endl << endl;

        cout << "Setters test:" << endl;
        eq1.setA(inputCoefficient("Enter new coefficient a: "));
        eq1.setB(inputCoefficient("Enter new coefficient b: "));
        eq1.setC(inputCoefficient("Enter new coefficient c: "));
        cout << "Modified equation: " << eq1 << endl;
        roots = eq1.solve();
        cout << "Roots: ";
        for (double root : roots) cout << root << " ";
        cout << endl;

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
    
    return 0;
}