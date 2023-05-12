#ifndef __TEST_H__
#define __TEST_H__

#include "stl_initializer_list.h"

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

template<class ForwardIterator, class T>
bool compare_n(ForwardIterator first, ForwardIterator last, std::initializer_list<T> il) {
    typedef typename std::initializer_list<T>::iterator ilitT;
    ilitT it_il = il.begin();
    ilitT it_il_end = il.end();

    while (first < last && it_il < it_il_end) {
        if (*first != *it_il) return false;
        ++first;
        ++it_il;
    }

    return first == last && it_il == it_il_end;
}

#endif
