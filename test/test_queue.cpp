#include "stl_queue.h"

#include <iostream>
#include <assert.h>
using std::cout, std::endl;

int main() {
    // default constructor
    cout << "********************" << endl;
    cout << "test default constructor" << endl;
    Sstl::queue<int> queue0;
    assert(queue0.empty() == true);
    assert(queue0.size() == 0);
    cout << "success!\n" << endl;

    return 0;
}
