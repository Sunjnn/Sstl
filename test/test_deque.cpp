// my implementation
#include "stl_deque.h"
#include "test.h"

// gcc implementation
#include <iostream>
#include <assert.h>
#include <deque>
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

    // deque operator[]
    cout << "********************" << endl;
    cout << "test operator[]" << endl;
    for (int i = 0; i < deque1.size(); ++i) {
        assert(deque1[i] == 10);
    }
    for (int i = 0; i < deque2.size(); ++i) {
        assert(deque2[i] == 10);
    }
    cout << "success!\n" << endl;

    // push_front() and pop_front()
    cout << "********************" << endl;
    cout << "test push_front() and pop_front()" << endl;
    std::deque<int> std_deque(20 * 128, 10);

    for (int i = 0; i < 5 * 128; ++i) {
        deque1.push_front(i);
        std_deque.push_front(i);
    }
    assert(compare_n(deque1.begin(), deque1.end(), std_deque.begin(), std_deque.end()));

    for (int i = 0; i < 5 * 128; ++i) {
        deque1.pop_front();
        std_deque.pop_front();
    }
    assert(compare_n(deque1.begin(), deque1.end(), std_deque.begin(), std_deque.end()));
    cout << "success!\n" << endl;

    return 0;
}
