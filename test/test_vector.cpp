#include "stl_vector.h"
#include <iostream>

using std::cout, std::endl;

int main() {
    // default constructor
    cout << "********************" << endl;
    cout << "test default constructor" << endl;
    const Sstl::vector<int> nums0;
    cout << "nums0 size is " << nums0.size() << endl;
    cout << "nums0 capacity is " << nums0.capacity() << endl;
    cout << "nums0 is empty? " << (nums0.empty() ? "true" : "false") << endl;

    // constructor of n t
    cout << "\n********************" << endl;
    cout << "test construct of n t" << endl;
    Sstl::vector<int>::size_type n = 10;
    int val = 5;
    Sstl::vector<int> nums1(n, val);
    cout << "nums1 size is " << nums1.size() << endl;
    cout << "nums1 capacity is " << nums1.capacity() << endl;
    cout << "nums1 is empty? " << (nums1.empty() ? "true" : "false") << endl;
    Sstl::vector<int> nums2((int)n, val);
    cout << "nums2 size is " << nums2.size() << endl;
    cout << "nums2 capacity is " << nums2.capacity() << endl;
    cout << "nums2 is empty? " << (nums2.empty() ? "true" : "false") << endl;
    Sstl::vector<int> nums3((long)n, val);
    cout << "nums3 size is " << nums3.size() << endl;
    cout << "nums3 capacity is " << nums3.capacity() << endl;
    cout << "nums3 is empty? " << (nums3.empty() ? "true" : "false") << endl;

    // deconstructor
    nums0.~vector();
    nums1.~vector();
    nums2.~vector();

    // operator []
    cout << "\n********************" << endl;
    cout << "test operator []" << endl;
    for (int i = 0; i < nums3.size(); ++i) {
        cout << "nums3[" << i << "] = " << nums3[i] << endl;
    }

    // iterator
    cout << "\n********************" << endl;
    cout << "test iterator" << endl;
    int i = 0;
    for (auto it = nums3.begin(); it < nums3.end(); ++it) {
        *it = i++;
        cout << *it << endl;
    }

    // front() and back()
    cout << "\n********************" << endl;
    cout << "test front() and back()" << endl;
    nums3.front() = 10;
    cout << "nums3.front() = " << nums3.front() << endl;
    nums3.back() = 10;
    cout << "nums3.back() = " << nums3.back() << endl;

    // insert()
    cout << "\n********************" << endl;
    cout << "test insert()" << endl;
    for (int i = 0; i < nums3.size(); ++i) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    auto it = nums3.begin();
    nums3.insert(it, 3, 3);

    for (int i = 0; i < nums3.size(); ++i) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    // push_back() and pop_back()
    cout << "\n********************" << endl;
    cout << "test push_back()" << endl;

    nums3.push_back(0);
    for (int i = 0; i < nums3.size(); ++i) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    nums3.pop_back();
    for (int i = 0; i < nums3.size(); ++i) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    // erase()
    cout << "\n********************" << endl;
    cout << "test erase()" << endl;
    it = nums3.begin();
    nums3.erase(it);
    for (int i = 0; i < nums3.size(); ++i) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    it = nums3.begin();
    auto it1 = it + 3;
    nums3.erase(it, it1);
    for (int i = 0; i < nums3.size(); ++i) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    // clear()
    cout << "\n********************" << endl;
    cout << "test clear()" << endl;
    nums3.clear();
    for (int i = 0; i < nums3.size(); ++i) {
        cout << nums3[i] << " ";
    }
    cout << endl;

    return 0;
}
