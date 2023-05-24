#ifndef __STL__UNINITIALIZED_H__
#define __STL__UNINITIALIZED_H__

#include "stl_construct.h"
#include "type_traits.h"
#include "fill_n.h"
#include <string.h>

namespace Sstl
{

// copy [first, last) to result
// for each element i in [result, result+(last-first)), execute construct(&*(result+(i-first)), *i)
// this function is "commit or rollback"
template<class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result);

// assign [first, last) as x
// for each element i in [first, last), execute construct(&*i, x)
// commit or rollback
template<class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x);

// assign [first, first+n) as x
// for each element i in [first, first+n), execute construct(&*i, x)
// commit or rollback
template<class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x);

}

// implementation of unintialized_fill_n
namespace Sstl {

// POD class
template<class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __true_type) {
    return fill_n(first, n, x);
}

// non POD class
template<class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __false_type) {
    ForwardIterator cur = first;
    for (; n > 0; --n, ++cur)
        construct(&*cur, x);
    return cur;
}

template<class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1 *) {
    // POD means Plain Old Data, POD class has trivial ctor/dtor/copy/assignment function
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

template<class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
    return __uninitialized_fill_n(first, n, x, value_type(first));
}

}

// inplementation of unintialized_copy
namespace Sstl {

// POD class
template<class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type) {
    return copy(first, last, result);
}

// non POD class
template<class InputIterator, class ForwardIterator>
ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type) {
    ForwardIterator cur = result;
    for (; first != last; ++first, ++cur)
        construct(&*cur, *first);
    return cur;
}

template<class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*) {
    typedef typename __type_traits<T>::is_POD_type is_POD;
    return __uninitialized_copy_aux(first, last, result, is_POD());
}

template<class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
    return __uninitialized_copy(first, last, result, value_type(result));
}

// specialization for const char *
inline char *uninitialized_copy(const char *first, const char *last, char *result) {
    memmove(result, first, last - first);
    return result + (last - first);
}

// specialization for const wchar_t *
inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *result) {
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
}

}

// inplementation of uninitialized_fill
namespace Sstl {

// POD class
template<class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __true_type) {
    fill(first, last, x);
}

// non POD class
template<class ForwardIterator, class T>
void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __false_type) {
    ForwardIterator cur = first;
    for (; cur != last; ++cur)
        construct(&*cur, x);
}

template<class ForwardIterator, class T, class T1>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, T1*) {
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    __uninitialized_fill_aux(first, last, x, is_POD());
}

template<class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x) {
    __uninitialized_fill(first, last, x, value_type(first));
}

}

#endif