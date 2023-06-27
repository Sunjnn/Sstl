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

void compare_whole_tree(Sstl::rb_tree<int, int, identity<int>, std::less<int>> &itree, const string &s) {
    stringstream strstream;
    for (auto ite1 = itree.begin(); ite1 != itree.end(); ++ite1) {
        strstream << *ite1 << "(" << ite1.node->color << ")";
    }
    assert(s == strstream.str());
}

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

        // red      0
        // black    1
        compare_whole_tree(itree, "5(0)6(1)7(0)8(1)10(1)11(0)12(0)13(1)15(0)");

        itree.erase(10);
        assert(itree.size() == 8);
        compare_whole_tree(itree, "5(0)6(1)7(0)8(1)11(1)12(0)13(0)15(1)");

        itree.erase(8);
        assert(itree.size() == 7);
        compare_whole_tree(itree, "5(0)6(1)7(0)11(1)12(1)13(0)15(1)");

        itree.erase(11);
        assert(itree.size() == 6);
        compare_whole_tree(itree, "5(0)6(1)7(0)12(1)13(1)15(0)");
    }

public:
    testRBTree(const string &s) : testBase(s) {}
};

int main() {
    testRBTree t("test case of rb tree from the book");
    test_run(&t);

    return 0;
}
