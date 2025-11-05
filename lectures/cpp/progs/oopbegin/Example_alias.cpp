//#include <iostream>
//#include <vector>
//
//class Calculator
//{
//public:
//    using number_t = int; // это вложенный псевдоним типа
//
//    std::vector<number_t> m_resultHistory{};
//
//    number_t add(number_t a, number_t b)
//    {
//        auto result{ a + b };
//
//        m_resultHistory.push_back(result);
//
//        return result;
//    }
//};
//
//int main()
//{
//    Calculator calculator{};
//
//    std::cout << calculator.add(3, 4) << '\n';   // 7
//    std::cout << calculator.add(99, 24) << '\n'; // 123
//
//    for (Calculator::number_t result : calculator.m_resultHistory)
//    {
//        std::cout << result << '\n';
//    }
//
//    return 0;
//}