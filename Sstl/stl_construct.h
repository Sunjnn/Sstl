#ifndef __STL_CONSTRUCT__H__
#define __STL_CONSTRUCT__H__

#include "type_traits.h"
#include "stl_iterator.h"

namespace Sstl {

template<class T1, class T2>
inline void construct(T1 *p, const T2 &value) {
    new (p) T1(value);
}

// first version of destroy
template<class T>
inline void destroy(T *pointer) {
    pointer->~T();
}

// no trivial destructor
// call first version of destroy for each element
template<class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
    for (; first < last; ++first) {
        destroy(&*first);
    }
}

// there is trivial destructor
template<class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __true_type) {
    for (; first < last; ++first) {
        destroy(&*first);
    }
}

// if there is trivial destructor
template<class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destroy_aux(first, last, trivial_destructor());
}

// second version of destroy, accept a range
template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    __destroy(first, last, value_type(first));
}

inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*){}

}

#endif