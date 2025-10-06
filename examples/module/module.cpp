#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
void tip(float a, float b, float c)
{
	int t;
	t = 0;
	if ((a == b) && (a == c) && (c == b))
	{
		cout << "Равносторонний" << endl; t = 1;
	}
	if ((a == b) && (a == c) && (c != b) || (a == b) && (a != c) && (c == b) ||
		(a != b) && (a == c) && (c == b))
	{
		cout << "Равнобедренный" << endl; t = 1;
	}
	if ((a * a + b * b == c * c) || (a * a + c * c == b * b) || (c * c + b * b == a * a))
	{
		cout << "Прямоугольный" << endl; t = 1;
	}
	if ((a + b <= c) || (a + c <= b) || (b + c <= a))
	{
		cout << "Не существует" << endl; t = 1;
	}
	if (t == 0)
	{
		cout << "Обычный" << endl;
	}
}
float square(float a, float b, float c)
{
	float p;
	p = (a + b + c) / 2;
	return (sqrt(p * (p - a) * (p - b) * (p - c)));
}
float perimetr(float a, float b, float c)
{
	return (a + b + c);
}