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

    // push_back() and pop_back()
    cout << "********************" << endl;
    cout << "test push_back() and pop_back()" << endl;

    for (int i = 0; i < 5 * 128; ++i) {
        deque1.push_back(i);
        std_deque.push_back(i);
    }
    assert(compare_n(deque1.begin(), deque1.end(), std_deque.begin(), std_deque.end()));

    for (int i = 0; i < 5 * 128; ++i) {
        deque1.pop_back();
        std_deque.pop_back();
    }
    assert(compare_n(deque1.begin(), deque1.end(), std_deque.begin(), std_deque.end()));
    cout << "success!\n" << endl;

    // insert()
    cout << "********************" << endl;
    cout << "test insert()" << endl;
    auto it1 = deque1.begin() + 3;
    auto it2 = std_deque.begin() + 3;
    deque1.insert(it1, 100);
    std_deque.insert(it2, 100);
    assert(compare_n(deque1.begin(), deque1.end(), std_deque.begin(), std_deque.end()));
    cout << "success!\n" << endl;

    // erase()
    cout << "********************" << endl;
    cout << "test erase()" << endl;

    deque1.erase(deque1.begin());
    std_deque.erase(std_deque.begin());

    it1 = deque1.begin() + 3;
    it2 = std_deque.begin() + 3;
    deque1.erase(it1);
    std_deque.erase(it2);

    deque1.erase(deque1.begin() + 10, deque1.begin() + 30);
    std_deque.erase(std_deque.begin() + 10, std_deque.begin() + 30);

    assert(compare_n(deque1.begin(), deque1.end(), std_deque.begin(), std_deque.end()));
    cout << "success!\n" << endl;

    // front() and back()
    cout << "test front() and back()" << endl;
    deque1.front() = 5;
    deque1.back() = 5;
    assert(deque1.front() == 5);
    assert(deque1.back() == 5);
    cout << "success!\n" << endl;

    // clear()
    cout << "********************" << endl;
    cout << "test clear()" << endl;

    deque1.clear();
    assert(deque1.begin() == deque1.end());
    assert(deque1.size() == 0);
    assert(deque1.empty() == true);

    return 0;
}
