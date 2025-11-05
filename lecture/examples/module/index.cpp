#include <iostream>
#include <iomanip>
#include "treug.h"
using namespace std;
void main()
{
	float x, y, z;
	setlocale(LC_ALL, "rus");
	cout << "Введите стороны треугольника" << endl;
	cin >> x >> y >> z;
	int punkt = 0;
	while (punkt != 4)
	{
		cout << "Выберите номер пункта:" << endl;
		cout << "1.Периметр" << endl;
		cout << "2.Площадь" << endl;
		cout << "3.Тип" << endl;
		cout << "4.Выход" << endl;
		cin >> punkt;
		switch (punkt)
		{
		case 1: cout << "Периметр=" << setprecision(2) << fixed <<
			perimetr(x, y, z) << endl; break;
		case 2: cout << "Площадь=" << setprecision(2) << fixed <<
			square(x, y, z) << endl; break;
		case 3: tip(x, y, z); break;
		case 4: break;
		default: cout << "Неверный ввод" << endl; break;
		}
	}
}