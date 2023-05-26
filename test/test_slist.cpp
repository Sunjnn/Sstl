#include "test.h"
#include "stl_slist.h"

#include <string>
#include <assert.h>
using std::string, std::cout, std::endl;

class testSlist : public testBase {
    virtual void test_func() {
        Sstl::slist<int> islist;
        assert(islist.size() == 0);

        islist.push_front(9);
        islist.push_front(1);
        islist.push_front(2);
        islist.push_front(3);
        islist.push_front(4);
        assert(islist.size() == 5);
        assert(compare_n(islist.begin(), islist.end(), {4, 3, 2, 1, 9}));

        islist.pop_front();
        islist.pop_front();
        assert(islist.size() == 3);
        assert(compare_n(islist.begin(), islist.end(), {2, 1, 9}));

        islist.clear();
        assert(islist.size() == 0);
    }

public:
    testSlist(string s) : testBase(s) {}
};

int main() {
    testSlist t("test case of slist from the book");
    test_run(&t);

    return 0;
}
