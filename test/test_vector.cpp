// my implementation
#include "stl_vector.h"

// gcc implementation
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

    // constructor of initializer list
    cout << "\n********************" << endl;
    cout << "test construct of initializer list" << endl;
    Sstl::vector<int> nums4({0, 1, 2, 3, 4});
    cout << "nums4 size is " << nums4.size() << endl;
    cout << "nums4 capacity is " << nums4.capacity() << endl;
    cout << "nums4 is empty? " << (nums4.empty() ? "true" : "false") << endl;
    cout << nums4 << endl;

    // deconstructor
    nums0.~vector();
    nums1.~vector();
    nums2.~vector();
    nums4.~vector();

    // operator []
    cout << "\n********************" << endl;
    cout << "test operator []" << endl;
    for (int i = 0; i < nums3.size(); ++i) nums3[i] = 10;
    cout << nums3 << endl;

    // iterator
    cout << "\n********************" << endl;
    cout << "test iterator" << endl;
    int i = 0;
    for (auto it = nums3.begin(); it < nums3.end(); ++it) {
        *it = i++;
    }
    cout << nums3 << endl;

    // front() and back()
    cout << "\n********************" << endl;
    cout << "test front() and back()" << endl;
    nums3.front() = 10;
    nums3.back() = 10;
    cout << nums3 << endl;

    // insert()
    cout << "\n********************" << endl;
    cout << "test insert()" << endl;
    auto it = nums3.begin();
    nums3.insert(it, 3, 3);
    cout << nums3 << endl;

    // push_back() and pop_back()
    cout << "\n********************" << endl;
    cout << "test push_back()" << endl;
    nums3.push_back(0);
    cout << nums3 << endl;

    nums3.pop_back();
    cout << nums3 << endl;

    // erase()
    cout << "\n********************" << endl;
    cout << "test erase()" << endl;
    it = nums3.begin();
    nums3.erase(it);
    cout << nums3 << endl;

    it = nums3.begin();
    auto it1 = it + 3;
    nums3.erase(it, it1);
    cout << nums3 << endl;

    cout << "\n********************" << endl;
    cout << "test resize" << endl;
    nums3.resize(20);
    cout << nums3 << endl;

    // clear()
    cout << "\n********************" << endl;
    cout << "test clear()" << endl;
    nums3.clear();
    cout << nums3 << endl;

    return 0;
}
