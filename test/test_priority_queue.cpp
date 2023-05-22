#include "stl_priority_queue.h"
#include "test.h"

#include <vector>
#include <iostream>
#include <assert.h>
using std::cout, std::endl, std::vector;

int main() {
    // test constructor priority_queue(InputIterator, InputIterator)
    cout << "********************" << endl;
    cout << "test constructor priority_queue(InputIterator, InputIterator)" << endl;
    vector<int> ia = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    Sstl::priority_queue<int, vector<int>> ipq(ia.begin(), ia.end());
    assert(ipq.size() == 9);
    cout << "success!\n" << endl;

    // test top()
    cout << "********************" << endl;
    cout << "test top()" << endl;
    for (int i = 0; i < ipq.size(); ++i) {
        assert(ipq.top() == 9);
    }
    cout << "success!\n" << endl;

    cout << "********************" << endl;
    cout << "test pop()" << endl;
    int i = 0;
    while (!ipq.empty()) {
        ia[i] = ipq.top();
        ipq.pop();
        ++i;
    }
    assert(compare_n(ia.begin(), ia.end(), {9, 8, 5, 4, 3, 3, 2, 1, 0}));
    cout << "success!\n" << endl;

    return 0;
}
