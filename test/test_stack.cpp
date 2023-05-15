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

    // push(), top() and pop()
    cout << "********************" << endl;
    cout << "test push(), top() and pop()" << endl;
    for (int i = 0; i < 10; ++i) {
        stack0.push(i);
    }
    assert(stack0.empty() == false);
    assert(stack0.size() == 10);
    for (int i = 9; i >= 0; --i) {
        int x = stack0.top();
        assert(x == i);
        stack0.pop();
        assert(stack0.size() == i);
    }
    assert(stack0.empty() == true);
    assert(stack0.size() == 0);
    cout << "success!\n" << endl;

    return 0;
}
