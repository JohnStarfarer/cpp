#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream f1; // read
    // ifsteam f1("a.txt");
    ofstream f2; // write
    fstream f3; // r+w

    f1.open("a.txt"); // ios::in default
    f2.open("b.txt"); // ios::off default
    // модификаторы
    // in -- чтение, out -- запись, app -- добавление, trunc - стирание
    f1.open("a.txt", ios::in);
    f2.open("a.txt", ios::out);

    if (f1.is_open()) {
        // working
    } else {
        // error
        return 1;
    }

    if (!f2.is_open()) {
        // error
        return 1;
    }

    f1.close();
    f2.close();

    f1.open("a.txt");
    if (!f1.is_open()) {
        cout << "error";
        return 1;
    }
    int x = 0;
    // 1
    while (!f1.eof()) {
        f1 >> x;
        cout << x << " ";
    }
    f1.close();

    // 2
    x = 0;
    while (f1.peek() != EOF) {
        f1 >> x;
        cout << x << " ";
    }
    f1.close();

    // 3
    while (f1 >> x) {
        f1 >> x;
        cout << x << " ";
    }
    f1.close();



    return 0;
}
