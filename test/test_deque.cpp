// my implementation
#include "stl_deque.h"
#include "test.h"

// gcc implementation
#include <iostream>
#include <assert.h>
using std::cout, std::endl;

int main(int argc, char **argv) {
    // default constructor
    cout << "********************" << endl;
    cout << "test default constructor" << endl;
    Sstl::deque<int> deque0;
    assert(deque0.begin() == deque0.end());
    assert(deque0.size() == 0);
    assert(deque0.max_size() == 8 * 512 / 4);
    assert(deque0.empty() == true);
    cout << "success!\n" << endl;

    // construct deque(int n, const value_type &value)
    cout << "********************" << endl;
    cout << "test constructor" << endl;
    Sstl::deque<int> deque1(20 * 128, 10);
    assert(compare_n(deque1, 20 * 128, 10));
    assert(deque1.size() == 20 * 128);
    assert(deque1.max_size() == 23 * 128);
    assert(deque1.empty() == false);

    Sstl::deque<int> deque2(12, 10);
    assert(compare_n(deque2, 12, 10));
    assert(deque2.size() == 12);
    assert(deque2.max_size() == 8 * 128);
    assert(deque2.empty() == false);
    cout << "success!\n" << endl;

    return 0;
}
