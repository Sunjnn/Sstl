#include "test.h"
#include "stl_hashtable.h"
#include <stl_alloc.h>

#include <iostream>
#include <assert.h>
#include <string>
#include <functional>

template<class T>
struct identity {
    const T& operator()(const T& x) const {return x;}
};

class testHashtable : public testBase {
    virtual void test_func() {
        Sstl::hashtable<int, int, std::hash<int>, identity<int>, std::equal_to<int>, Sstl::alloc> iht(50, std::hash<int>(), std::equal_to<int>());

        assert(iht.size() == 0);
        assert(iht.bucket_count() == 53);
        assert(iht.max_bucket_count() == 4294967291ul);

        iht.insert_unique(59);
        iht.insert_unique(63);
        iht.insert_unique(108);
        iht.insert_unique(2);
        iht.insert_unique(53);
        iht.insert_unique(55);

        assert(iht.size() == 6);
        assert(compare_n(iht.begin(), iht.end(), {53, 55, 2, 108, 59, 63}));

        // for (int i = 0; i < iht.bucket_count(); ++i) {
        //     int n = iht.elems_in_bucket(i);
        //     if (n) std::cout << "bucket[" << i << "] has " << n << " elems." << std::endl;
        // }

        for (int i = 0; i <= 47; ++i) iht.insert_equal(i);

        assert(iht.size() == 54);
        assert(iht.bucket_count() == 97);

        // for (int i = 0; i < iht.bucket_count(); ++i) {
        //     int n = iht.elems_in_bucket(i);
        //     if (n) std::cout << "bucket[" << i << "] has " << n << " elems." << std::endl;
        // }

        assert(compare_n(iht.begin(), iht.end(), {0, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 108, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 53, 55, 59, 63}));

        assert(*(iht.find(2)) == 2);
        assert(iht.count(2) == 2);
    }
public:
    testHashtable(std::string s) : testBase(s) {}
};

int main() {
    testHashtable t("test cases from the book");
    test_run(&t);
    return 0;
}
