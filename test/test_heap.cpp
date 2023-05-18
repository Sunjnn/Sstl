#include "stl_heap.h"
#include "stl_vector.h"
#include "test.h"

#include <iostream>
#include <assert.h>
using std::cout, std::endl;

int main() {
    Sstl::vector<int> ivec({0, 1, 2, 3, 4, 8, 9, 3, 5});

    // make heap
    cout << "********************" << endl;
    cout << "test make heap" << endl;
    Sstl::make_heap(ivec.begin(), ivec.end());
    assert(compare_n(ivec.begin(), ivec.end(), {9, 5, 8, 3, 4, 0, 2, 3, 1}));
    cout << "success!\n" << endl;

    // push heap
    cout << "********************" << endl;
    cout << "test push heap" << endl;
    ivec.push_back(7);
    Sstl::push_heap(ivec.begin(), ivec.end());
    assert(compare_n(ivec.begin(), ivec.end(), {9, 7, 8, 3, 5, 0, 2, 3, 1, 4}));
    cout << "success!\n" << endl;

    cout << "********************" << endl;
    cout << "test pop heap" << endl;
    Sstl::pop_heap(ivec.begin(), ivec.end());
    ivec.pop_back();
    assert(compare_n(ivec.begin(), ivec.end(), {8, 7, 4, 3, 5, 0, 2, 3, 1}));
    cout << "success!\n" << endl;

    cout << "********************" << endl;
    cout << "test sort heap" << endl;
    Sstl::sort_heap(ivec.begin(), ivec.end());
    assert(compare_n(ivec.begin(), ivec.end(), {0, 1, 2, 3, 3, 4, 5, 7, 8}));
    cout << "success!\n" << endl;

    return 0;
}
