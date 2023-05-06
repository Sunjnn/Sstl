// my implementation
#include "stl_list.h"

// gcc implementation
#include <iostream>

using std::cout, std::endl;

int main() {
    // default constructor
    cout << "********************" << endl;
    cout << "test default constructor" << endl;
    Sstl::list<int> list0;
    cout << "list0 size is " << list0.size() << endl;
    cout << "list0 is empty? " << (list0.empty() ? "true" : "false") << endl;

    // begin(), end() and size() at empty list
    cout << "********************" << endl;
    cout << "test begin(), end() and size() at empty list" << endl;
    Sstl::list<int>::iterator beg = list0.begin(), end = list0.end();
    Sstl::list<int>::size_type size = list0.size();
    cout << "element of begin iterator: " << *beg << endl;
    cout << "element of end iterator: " << *end << endl;
    cout << "size is " << size << endl;

    // insert
    cout << "********************" << endl;
    cout << "test insert()" << endl;
    list0.insert(beg, 1);
    list0.insert(end, 2);
    cout << list0 << endl;

    // front() and back()
    cout << "********************" << endl;
    cout << "test front() and back()" << endl;
    typename Sstl::list<int>::reference front = list0.front(), back = list0.back();
    front = 10;
    back = 10;
    cout << list0 << endl;

    // push_front() and push_back()
    cout << "********************" << endl;
    cout << "test push_front() and push_back()" << endl;
    list0.push_front(1);
    list0.push_front(2);
    list0.push_front(3);
    list0.push_back(4);
    list0.push_back(5);
    list0.push_back(6);
    cout << list0 << endl;

    // erase
    cout << "********************" << endl;
    cout << "test erase()" << endl;
    list0.erase(list0.begin());
    list0.erase(++list0.begin());
    cout << list0 << endl;

    // pop_front() and pop_back()
    cout << "********************" << endl;
    cout << "test pop_front() and pop_back()" << endl;
    list0.pop_front();
    list0.pop_back();
    cout << list0 << endl;

    // remove()
    cout << "********************" << endl;
    cout << "test remove()" << endl;
    list0.remove(10);
    cout << list0 << endl;

    // unique()
    cout << "********************" << endl;
    cout << "test unique()" << endl;
    list0.unique();
    cout << list0 << endl;

    // splice(iterator, list)
    cout << "********************" << endl;
    cout << "list1 and list2" << endl;
    Sstl::list<int> list1, list2;
    for (int i = 0; i < 10; ++i) {
        list1.push_back(i * 2);
        list2.push_back(i * 2 + 1);
    }
    cout << list1 << endl;
    cout << list2 << endl;

    cout << "test splice(iterator, list)" << endl;
    list1.splice(list1.begin(), list2);
    cout << list1 << endl;
    cout << list2 << endl;

    // reverse()
    cout << "********************" << endl;
    cout << "test reverse()" << endl;
    list1.reverse();
    cout << list1 << endl;

    // sort()
    cout << "********************" << endl;
    cout << "test sort()" << endl;
    list1.sort();
    cout << list1 << endl;

    return 0;
}
