#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int sumLastNums(int x){ // 1 2
    if (x < 0) x = -x;
    return (x % 10) + (x % 100 / 10);
}

bool isPositive(int x){ // 1 4
    return (x > 0)? true : false;
}

bool isUpperCase(char x){ // 1 6
    return (x >= 'A' && x <= 'Z')? true : false;
}

bool isDivisior(int a, int b){ // 1 8 
    return (a % b == 0 || b % a == 0)? true : false;
}

int lastNumSum(int a, int b){ // 1 10
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return (a % 10) + (b % 10);
}

double safeDiv(int x, int y){ // 2 2
    if (y == 0) return 0;
    else return (x / y);
}

string makeDecision(int x, int y){ // 2 4
    string znak;
    if (x == y) znak = " == ";
    else
        if (x > y) znak = " > ";
        else znak = " < ";
    return (to_string(x) + znak + to_string(y));
}

bool sum3(int x, int y, int z){ // 2 6
    return (x + y == z || x + z == y || y + z == x)? true : false;
}

string age(int x){ // 2 8
    string year;
    switch (x % 10){    
        case 1:
            if (x == 11) year = "лет";
            else year = "год";
            break;

        case 2: case 3: case 4:
            if (x == 12 || x == 13 || x == 14) year = "лет";
            else year = "года";
            break;
        
        default:
            year = "лет";
            break;
    };
    return (to_string(x) + " " + year);
}

void printDays(int x){ // 2 10
    switch (x)
    {
        case 1:
            cout << "\nпонедельник";
        
        case 2:
            cout << "\nвторник";

        case 3:
            cout << "\nсреда";

        case 4:
            cout << "\nчетверг";

        case 5:
            cout << "\nпятница";

        case 6:
            cout << "\nсуббота";

        case 7:
            cout << "\nвоскресенье";
            break;

        default:
            cout << "\nэто не день недели";
            break;
    }
}

string reverseListNums(int x){ // 3 2
    string res = "";
    if (x >= 0){
        for (int i = x; i >= 0; i--){
            res.append(to_string(i));
            if (i > 0) res.append(" ");
            // res += i;
        };
    }
    else{
        for (int i = x; i <= 0; i++){
            res.append(to_string(i));
            if (i < 0) res.append(" ");
        };
    }
    return res;
}

int pow(int x, int y){ // 3 4
    for (; y > 1; y--){
        x *= x;
    }
    return x;
}

bool equalNum(int x){ // 3 6
    bool equal = true;
    int prevx = x % 10;
    if (x < 0)
        equal = false;
    while (x > 0 && equal){
        //equal = (x % 10 != prevx)? false: true;
        if (x % 10 != prevx) equal = false;
        prevx = x % 10;
        x /= 10;
    }
    return equal;
}

void leftTriangle(int x){ // 3 8
    for (int i = 1; i <= x; i++){
        for (int j = i; j > 0; j--){
            cout << '*';
        }
        cout << endl;
    }
}

void guessGame(){ // 3 10
    srand(time(0));
    int luckyNum = rand() % 10;
    cout << "[DEBUG luckyNum = " << luckyNum << "]\n";
    int totalGuesses = 1;
    int userNum;

    cout << "Введите число от 0 до 9:\n";
    cin >> userNum;
    while (userNum != luckyNum){
        cout << "Вы не угадали, введите число от 0 до 9:\n";
        cin >> userNum;
        totalGuesses += 1;
    }
    cout << "Вы угадали!\n" << "Вы отгадали число за " << totalGuesses << " попыт(ку|ки|ок)\n";
}

int findLast (int arr[], int x){
    
}

int main(){
	setlocale(LC_ALL, "rus");
    int majorTaskChoice, minorTaskChoice;

    cout << "Доступные задания:\n  | 1.2 | 1.4 | 1.6 | 1.8 | 1.10 |\n  | 2.2 | 2.4 | 2.6 | 2.8 | 2.10 |\n  | 3.2 | 3.4 | 3.6 | 3.8 | 3.10 |\n  | 4.2 | 4.4 | 4.6 | 4.8 | 4.10 |\n"
         << "Введите номер задания (первая цифра)(для отмены введите 0): ";
    cin >> majorTaskChoice;
    cout << "Введите номер подзадания (вторая цифра): ";
    cin >> minorTaskChoice;

    switch (majorTaskChoice){
        case 1: switch (minorTaskChoice){
            case 2:{
                cout << "> Введите целое число, содержащие не менее двух знаков: ";
                int x;
                cin >> x;
                cout << "> Результат: " << sumLastNums(x) << endl;

            }; break;
            
            case 3:{
                cout << "> Введите число: ";
                float x;
                cin >> x;
                cout << boolalpha;
                cout << "> Результат: " << isPositive(x) << endl;

            }; break;

            case 6:{
                cout << "> Введите символ: ";
                char x;
                cin >> x;
                cout << boolalpha;
                cout << "> Результат: " << isUpperCase(x) << endl;

            }; break;

            case 8:{
                cout << "> Введите два целых числа (через пробел): ";
                int x, y;
                cin >> x >> y;
                cout << boolalpha;
                cout << "> Результат: " << isDivisior(x, y) << endl;

            }; break;

            case 10:{
                for (int i = 1; i <= 5; i++){
                    cout << "> Введите " << i << "-ю пару двух целых чисел (через пробел): ";
                    int x, y;
                    cin >> x >> y;
                    cout << "> Результат: " << lastNumSum(x, y) << endl;
                }

            }; break;

            default: cout << "\nВыход из программы\n"; break;
        
        }; break;

        case 2: switch (minorTaskChoice){
            case 2:{
                cout << "> Введите два числа (через пробел): ";
                int x, y;
                cin >> x >> y;
                cout << "> Результат: " << safeDiv(x, y) << endl;
            }; break;

            case 4:{
                cout << "> Введите два числа (через пробел): ";
                float x, y;
                cin >> x >> y;
                cout << "> Результат: " << makeDecision(x, y) << endl;
            }; break;

            case 6:{
                cout << "> Введите три целых числа (через пробел): ";
                int x, y, z;
                cin >> x >> y >> z;
                cout << boolalpha;
                cout << "> Результат: " << sum3(x, y, z) << endl;
            }; break;
            
            case 8:{
                cout << "> Введите целое число: ";
                int x;
                cin >> x;
                cout << "> Результат: " << age(x) << endl;
            }; break;

            case 10:{
                cout << "> Введите целое число: ";
                int x;
                cin >> x;
                cout << "> Результат: "; printDays(x);
                cout << endl;
            }; break;

            default: cout << "\nВыход из программы\n"; break;

        }; break;

        case 3: switch (minorTaskChoice){
            case 2:{
                cout << "> Введите целое число: ";
                int x;
                cin >> x;
                cout << "> Результат: " << reverseListNums(x) << endl;
            }; break;

            case 4:{
                cout << "> Введите два целых числа: ";
                int x, y;
                cin >> x >> y;
                cout << "> Результат: " << pow(x, y) << endl;
            }; break;

            case 6:{
                cout << "> Введите число: ";
                int x;
                cin >> x;
                cout << boolalpha;
                cout << "> Результат: " << equalNum(x) << endl;
            }; break;

            case 8:{
                cout << "> Введите число: ";
                int x;
                cin >> x;
                cout << "> Результат: " << endl;
                leftTriangle(x);
            }; break;

            case 10:{
                guessGame();
            }; break;

            default: cout << "\nВыход из программы\n"; break;

        }; break;

        case 4: switch (minorTaskChoice){
            case 2:{

            }; break;

            default: cout << "\nВыход из программы\n"; break;

        }; break;

        //case 0: cout << "major"; break;

        default: cout << "\nВыход из программы\n"; break;
    }
    // cout << "\nТакого задания нет!" << endl;
    return 0;
}

