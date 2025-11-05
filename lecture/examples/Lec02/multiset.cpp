//// CPP Program to demonstrate the 
//// implementation of multiset
//#include <iostream>
//#include <iterator>
//#include <set>
//
//using namespace std;
//
//int main()
//{
//    // empty multiset container
//    multiset<int, greater<int> > ms1;
//
//    // insert elements in random order
//    ms1.insert(40);
//    ms1.insert(30);
//    ms1.insert(60);
//    ms1.insert(20);
//    ms1.insert(50);
//
//    // 50 will be added again to
//    // the multiset unlike set
//    ms1.insert(50);
//    ms1.insert(10);
//
//    // printing multiset ms1
//    multiset<int, greater<int> >::iterator itr;
//    cout << "\nThe multiset ms1 is : \n";
//    for (itr = ms1.begin(); itr != ms1.end(); ++itr) {
//        cout << *itr << " ";
//    }
//    cout << endl;
//
//    // assigning the elements from ms1 to ms2
//    multiset<int> ms2(ms1.begin(), ms1.end());
//
//    // print all elements of the multiset ms2
//    cout << "\nThe multiset ms2 \n"
//        "after assign from ms1 is : \n";
//    for (itr = ms2.begin(); itr != ms2.end(); ++itr) {
//        cout << *itr << " ";
//    }
//    cout << endl;
//
//    // remove all elements up to element
//    // with value 30 in ms2
//    cout << "\nms2 after removal \n"
//        "of elements less than 30 : \n";
//    ms2.erase(ms2.begin(), ms2.find(30));
//    for (itr = ms2.begin(); itr != ms2.end(); ++itr) {
//        cout << *itr << " ";
//    }
//
//    // remove all elements with value 50 in ms2
//    int num;
//    num = ms2.erase(50);
//    cout << "\nms2.erase(50) : \n";
//    cout << num << " removed \n";
//    for (itr = ms2.begin(); itr != ms2.end(); ++itr) {
//        cout << *itr << " ";
//    }
//
//    cout << endl;
//
//    // lower bound and upper bound for multiset ms1
//    cout << "\nms1.lower_bound(40) : \n"
//        << *ms1.lower_bound(40) << endl;
//    cout << "ms1.upper_bound(40) : \n"
//        << *ms1.upper_bound(40) << endl;
//
//    // lower bound and upper bound for multiset ms2
//    cout << "ms2.lower_bound(40) : \n"
//        << *ms2.lower_bound(40) << endl;
//    cout << "ms2.upper_bound(40) : \n"
//        << *ms2.upper_bound(40) << endl;
//
//    return 0;
//}