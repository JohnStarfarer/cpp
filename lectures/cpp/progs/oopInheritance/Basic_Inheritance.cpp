//#include <string>
//#include <iostream>
//
//class Person
//{
//public:
//	std::string m_name{};
//	int m_age{};
//	Person(const std::string& name = "", int age = 0)
//		: m_name{ name }, m_age{ age }
//	{
//	}
//	const std::string& getName() const { return m_name; }
//	int getAge() const { return m_age; }
//
//};
//class Student: public Person
//{
//public:
//	double m_rateAverage{};
//	int m_kurs{};
//
//	Student(double rateAverage = 0.0, int kurs = 0)
//		: m_rateAverage{ rateAverage }, m_kurs{ kurs }
//	{
//	}
//};
//class Prepod : public Person
//{
//public:
//	double m_hourlySalary{};
//	long m_prepodID{};
//	Prepod(double hourlySalary = 0.0, long prepodID = 0)
//		: m_hourlySalary{ hourlySalary }, m_prepodID{ prepodID }
//	{
//	}
//	void printNameAndSalary() const
//	{
//		std::cout << m_name << ": " << m_hourlySalary << '\n';
//	}
//};
//class BigBoss : public Prepod
//{
//public:
//	long m_prepodsIDs[100]{};
//};
//
//int main() {
//	Student jack{};
//	jack.m_name = "Jack";
//	std::cout << jack.getName() << '\n';
//	Prepod john{ 100500.99, 123456789 };
//	john.m_name = "John";
//	john.printNameAndSalary();
//	return 0;
//}