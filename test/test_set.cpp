#include "test.h"
#include "stl_set.h"

#include <string>
#include <assert.h>
using std::string, std::cout, std::endl;

class testSet : public testBase {
    virtual void test_func() {
        int ia[5] = {0, 1, 2, 3, 4};
        Sstl::set<int> iset(ia, ia + 5);

        assert(iset.size() == 5);
        assert(iset.count(3) == 1);
        iset.insert(3);
        assert(iset.size() == 5);
        assert(iset.count(3) == 1);
        iset.insert(5);
        assert(iset.size() == 6);
        assert(iset.count(3) == 1);
        // iset.erase(1);
        assert(iset.size() == 6);
        assert(iset.count(3) == 1);
    }

public:
    testSet(string s) : testBase(s) {}
};

int main() {
    testSet t("test case of set from the book");
    test_run(&t);

    return 0;
}
