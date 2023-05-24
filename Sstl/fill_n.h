#ifndef __FILL_N_H__
#define __FILL_N_H__

namespace Sstl {

template<class ForwardIterator, class Size, class T>
ForwardIterator fill_n(ForwardIterator first, Size n, const T &x) {
    ForwardIterator cur = first;
    for (int i = 0; i < n; ++i) {
        *cur = x;
        ++cur;
    }
    return cur;
}

template<class InputIterator, class ForwardIterator>
ForwardIterator copy(InputIterator first, InputIterator last, ForwardIterator result) {
    while (first != last) {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

template<class InputIterator, class T>
void fill(InputIterator first, InputIterator last, const T &x) {
    while (first != last) {
        *first = x;
        ++first;
    }
}

template<class InputIterator>
void copy_backward(InputIterator first, InputIterator last, InputIterator result) {
    --last;
    --result;
    while (first <= last) {
        *result = *last;
        --last;
        --result;
    }
}

}

#endif
