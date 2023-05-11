// my implementation
#include "stl_deque.h"

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

    return 0;
}
