//class BaseClass
//{
//public:
//    int m_public; //доступно везде
//protected:
//    int m_protected;// доступно в BaseClass и в производных классах
//private:
//    int m_private;//доступно в BaseClass, НЕ доступно в производных
//};
//
//class DerivedClass : public BaseClass
//{
//public:
//    DerivedClass()
//    {
//        m_public = 1; //есть доступ к открытым членам базового класса из производного класса
//        m_protected = 2; //есть доступ к защищенным членам базового класса из производного класса
//        m_private = 3;//НЕТ доступа к закрытым членам базового класса из производного класса
//    }
//};
//
//int main()
//{
//    BaseClass base_obj;
//    base_obj.m_public = 1;//есть доступ к открытым членам извне класса
//    base_obj.m_protected = 2; //НЕТ доступа к защищенным членам извне класса
//    base_obj.m_private = 3; //НЕТ доступа к закрытым членам извне  класса
//
//    return 0;
//}

