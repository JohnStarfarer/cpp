//// C++ code to demonstrate forward list
//// and assign()
//#include <forward_list>
//#include <iostream>
//using namespace std;
//
//// Driver Code
//int main()
//{
//    // Declaring forward list
//    forward_list<int> flist1;
//
//    // Declaring another forward list
//    forward_list<int> flist2;
//
//    //Declaring another forward list
//    forward_list<int> flist3;
//
//    // Assigning values using assign()
//    flist1.assign({ 1, 2, 3 });
//
//    // Assigning repeating values using assign()
//    // 5 elements with value 10
//    flist2.assign(5, 10);
//
//
//    //Assigning values of list 1 to list 3
//    flist3.assign(flist1.begin(), flist1.end());
//
//    // Displaying forward lists
//    cout << "The elements of first forward list are : ";
//    for (int& a : flist1)
//        cout << a << " ";
//    cout << endl;
//
//    cout << "The elements of second forward list are : ";
//    for (int& b : flist2)
//        cout << b << " ";
//    cout << endl;
//
//
//    cout << "The elements of third forward list are : ";
//    for (int& c : flist3)
//        cout << c << " ";
//    cout << endl;
//
//    // Initializing forward list
//    forward_list<int> flist4 = { 10, 20, 30, 40, 50 };
//
//    // Inserting value using push_front()
//    // Inserts 60 at front
//    flist4.push_front(60);
//
//    // Displaying the forward list
//    cout
//        << "The forward list after push_front operation : ";
//    for (int& c : flist4)
//        cout << c << " ";
//    cout << endl;
//
//    // Inserting value using emplace_front()
//    // Inserts 70 at front
//    flist4.emplace_front(70);
//
//    // Displaying the forward list
//    cout << "The forward list after emplace_front "
//        "operation : ";
//    for (int& c : flist4)
//        cout << c << " ";
//    cout << endl;
//
//    // Deleting first value using pop_front()
//    // Pops 70
//    flist4.pop_front();
//
//    // Displaying the forward list
//    cout << "The forward list after pop_front operation : ";
//    for (int& c : flist4)
//        cout << c << " ";
//    cout << endl;
//
//    // Initializing forward list
//    forward_list<int> flist5 = { 10, 20, 30 };
//
//    // Declaring a forward list iterator
//    forward_list<int>::iterator ptr;
//
//    // Inserting value using insert_after()
//    // starts insertion from second position
//    ptr = flist5.insert_after(flist5.begin(), { 1, 2, 3 });
//
//    // Displaying the forward list
//    cout << "The forward list after insert_after operation "
//        ": ";
//    for (int& c : flist5)
//        cout << c << " ";
//    cout << endl;
//
//    // Inserting value using emplace_after()
//    // inserts 2 after ptr
//    ptr = flist5.emplace_after(ptr, 2);
//
//    // Displaying the forward list
//    cout << "The forward list after emplace_after "
//        "operation : ";
//    for (int& c : flist5)
//        cout << c << " ";
//    cout << endl;
//
//    // Deleting value using erase.after Deleted 2
//    // after ptr
//    ptr = flist5.erase_after(ptr);
//    cout << "The forward list after erase_after operation "
//        ": ";
//    // Displaying the forward list
//    for (int& c : flist5)
//        cout << c << " ";
//    cout << endl;
//
//
//
//    // Deleting value in a range
//    // another variant of erase which uses start and end iterator
//    // and deletes all the values in between them
//    ptr = flist5.erase_after(flist5.begin(), flist5.end());
//    cout << "The forward list after erase_after (range) operation "
//        ": ";
//    // Displaying the forward list
//    for (int& c : flist5)
//        cout << c << " ";
//    cout << endl;
//
//    // Initializing forward list
//    forward_list<int> flist6 = { 10, 20, 30, 25, 40, 40 };
//
//    // Removing element using remove()
//    // Removes all occurrences of 40
//    flist6.remove(40);
//
//    // Displaying the forward list
//    cout << "The forward list after remove operation : ";
//    for (int& c : flist6)
//        cout << c << " ";
//    cout << endl;
//
//    // Removing according to condition. Removes
//    // elements greater than 20. Removes 25 and 30
//    flist6.remove_if([](int x) { return x > 20; });
//
//    // Displaying the forward list
//    cout << "The forward list after remove_if operation : ";
//    for (int& c : flist6)
//        cout << c << " ";
//    cout << endl;
//
//    // creating forward list
//    forward_list<int> flist7{ 1, 2, 3, 4, 5 };
//
//    //Printing forward list
//    cout << "Forward list: ";
//    for (auto i : flist7) {
//        cout << i << " ";
//    }
//    cout << endl;
//
//    flist7.clear();
//    // Forward List becomes empty
//
//     // Initializing forward list
//    forward_list<int> flist8 = { 10, 20, 30 };
//
//    // Initializing second list
//    forward_list<int> flist9 = { 40, 50, 60 };
//
//    // Shifting elements from first to second
//    // forward list after 1st position
//    flist9.splice_after(flist9.begin(), flist8);
//
//    // Displaying the forward list
//    cout << "The forward list after splice_after operation "
//        ": ";
//    for (int& c : flist9)
//        cout << c << " ";
//    cout << endl;
//
//
//    return 0;
//}