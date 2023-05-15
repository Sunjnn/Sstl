#include "stl_stack.h"

#include <iostream>
#include <assert.h>
using std::cout, std::endl;

int main() {
    // default constructor
    cout << "********************" << endl;
    cout << "test default constructor" << endl;
    Sstl::stack<int> stack0;
    assert(stack0.empty() == true);
    assert(stack0.size() == 0);
    cout << "success!\n" << endl;

    return 0;
}
