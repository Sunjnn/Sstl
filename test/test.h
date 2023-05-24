#ifndef __TEST_H__
#define __TEST_H__

#include "stl_initializer_list.h"

#include <cstddef>
#include <iostream>
#include <string>

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

template<class ForwardIterator1, class ForwardIterator2>
bool compare_n(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
    while (first1 < last1 && first2 < last2) {
        if (*first1 != *first2) return false;
        ++first1;
        ++first2;
    }
    return first1 == last1 && first2 == last2;
}

class testBase {
    std::string info;

    void print_stars() {
        std::cout << "********************" << std::endl;
    }

    void print_info() {
        std::cout << info << std::endl;
    }

    virtual void test_func() {
        std::cout << "print from testBase" << std::endl;
    }

    void print_succ() {
        std::cout << "success!\n" << std::endl;
    }

    friend void test_run(testBase *t);

public:
    testBase(std::string s) : info(s) {}

    testBase() {
        print_stars();
        print_info();
        test_func();
        print_succ();
    }
};

void test_run(testBase *t) {
    t->print_stars();
    t->print_info();
    t->test_func();
    t->print_succ();
}

#endif
