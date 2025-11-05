//#include <iostream>
//
//class BaseClass
//{
//private: 
//    int field_base;
//
//public:
//    BaseClass(int field_base = 0)
//        : field_base{ field_base }
//    {
//    }
//
//    int getFB() const { return field_base; }
//};
//
//class DerivedClass : public BaseClass
//{
//private: 
//    double field_derived;
//
//public:
//    DerivedClass(double field_derived = 0.0, int field_base = 0)
//        : BaseClass{ field_base }, 
//        field_derived{ field_derived }
//    {
//    }
//
//    double getFD() const { return field_derived; }
//};
//
//int main()
//{
//    DerivedClass derived_obj{ 0.1, 2 }; 
//    std::cout << "Field1: " << derived_obj.getFB() << '\n';
//    std::cout << "Field2: " << derived_obj.getFD() << '\n';
//
//    return 0;
//}