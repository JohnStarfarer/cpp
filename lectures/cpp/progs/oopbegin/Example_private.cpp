//#include <cassert>
//#include <iostream>
//
//class Fraction
//{
//private:
//    int m_numerator;
//    int m_denominator;
//
//public:
//    Fraction() 
//    {
//        m_numerator = 0;
//        m_denominator = 1;
//    }
//
//    Fraction(int numerator, int denominator = 1)
//    {
//        assert(denominator != 0);
//        m_numerator = numerator;
//        m_denominator = denominator;
//    }
//        
//    int getNumerator() { return m_numerator; }
//    int getDenominator() { return m_denominator; }
//    double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
//};
//
//int main()
//{
//    Fraction frac(13, 0);
//    
//    std::cout << frac.getNumerator() << "/" << frac.getDenominator() << '\n';
//
//    return 0;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <cassert>
//
//class Fraction
//{
//private:
//    int m_numerator;
//    int m_denominator;
//
//public:
//    
//    Fraction(int numerator = 0, int denominator = 1)
//    {
//        assert(denominator != 0);
//
//        m_numerator = numerator;
//        m_denominator = denominator;
//    }
//
//    int getNumerator() { return m_numerator; }
//    int getDenominator() { return m_denominator; }
//    double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
//};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <iostream>
//#include <cassert>
//#include <cstddef>
//
//class IntArray
//{
//private:
//	int* m_array{};
//	int m_length{};
//
//public:
//	IntArray(int length) 
//	{
//		assert(length > 0);
//
//		m_array = new int[length] {};
//		m_length = length;
//	}
//
//	~IntArray() 
//	{
//		delete[] m_array;
//	}
//
//	void setValue(int index, int value) { m_array[index] = value; }
//	int getValue(int index) { return m_array[index]; }
//
//	int getLength() { return m_length; }
//};
//
//int main()
//{
//	IntArray ar(10); // выделяем 10 чисел int
//	for (int count{ 0 }; count < ar.getLength(); ++count)
//		ar.setValue(count, count + 1);
//
//	std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';
//
//	return 0;
//} 