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

    // push(), pop(), front() and back()
    cout << "********************" << endl;
    cout << "test push(), pop(), front() and back()" << endl;
    for (int i = 0; i < 10; ++i) {
        queue0.push(i);
        assert(queue0.front() == 0);
        assert(queue0.back() == i);
    }
    assert(queue0.empty() == false);
    assert(queue0.size() == 10);
    for (int i = 1; i < 10; ++i) {
        queue0.pop();
        assert(queue0.front() == i);
        assert(queue0.back() == 9);
    }
    queue0.pop();
    assert(queue0.empty() == true);
    assert(queue0.size() == 0);
    cout << "success!\n" << endl;

    return 0;
}
