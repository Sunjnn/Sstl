#ifndef __TEST_H__
#define __TEST_H__

#include <cstddef>

template<class ForwardIterator, class T>
bool compare_n(ForwardIterator first, ForwardIterator last, const size_t n, const T &x) {
    size_t len = 0;
    while (first < last) {
        if (*first != x) return false;
        ++first;
        ++len;
    }
    return len == n;
}

template<class container, class T>
bool compare_n(container con, const size_t n, const T &x) {
    return compare_n(con.begin(), con.end(), n, x);
}

#endif
