#include "test.h"
#include "stl_rb_tree.h"

#include <string>
#include <assert.h>
#include <functional>
#include <sstream>
using std::string, std::cout, std::endl;
using std::stringstream;

template<class T>
struct identity {
    const T& operator()(const T& x) const {return x;}
};

class testRBTree : public testBase {
    virtual void test_func() {
        Sstl::rb_tree<int, int, identity<int>, std::less<int>> itree;
        assert(itree.size() == 0);

        itree.insert_unique(10);
        itree.insert_unique(7);
        itree.insert_unique(8);
        itree.insert_unique(15);
        itree.insert_unique(5);
        itree.insert_unique(6);
        itree.insert_unique(11);
        itree.insert_unique(13);
        itree.insert_unique(12);

        assert(itree.size() == 9);
        assert(compare_n(itree.begin(), itree.end(), {5, 6, 7, 8, 10, 11, 12, 13, 15}));

        auto ite1 = itree.begin();
        auto ite2 = itree.end();
        Sstl::__rb_tree_base_iterator rbtite;

        string s1 = "5(0)6(1)7(0)8(1)10(1)11(0)12(0)13(1)15(0)";
        stringstream strstream;
        for (; ite1 != ite2; ++ite1) {
            rbtite = Sstl::__rb_tree_base_iterator(ite1);
            strstream << *ite1 << "(" << rbtite.node->color << ")";
        }
        assert(s1 == strstream.str());
    }

public:
    testRBTree(const string &s) : testBase(s) {}
};

int main() {
    testRBTree t("test case of rb tree from the book");
    test_run(&t);

    return 0;
}
