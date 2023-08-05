#ifndef __STL_ALGO_H__
#define __STL_ALGO_H__

#include "stl_iterator.h"

// find
namespace Sstl {

template<class ForwardIterator, class T>
ForwardIterator find(ForwardIterator begin, ForwardIterator end, const T& value) {
    while (begin != end && *begin != value) {
        ++begin;
    }

    return begin;
}

} // namespace Sstl find

//find_if
namespace Sstl {

// onle one version of find_if
template<class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last,
                      Predicate pred) {
    while (first != last && !pred(*first)) ++first;
    return first;
}

} // namespace Sstl find_if

// adjacent find
namespace Sstl {

// first of two versions of adjacent find
// find two equal adjacent element
template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
    if (first == last) return last;
    ForwardIterator next = first;
    while (++next != last) {
        if (*first == *next) return first;
        first = next;
    }
    return last;
}

// seconda of two versions of adjacent find
// find two adjacent element that binary_pred(*first, *next)
template<class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator frist, ForwardIterator last,
                              BinaryPredicate binary_pred) {
    if (frist == last) return last;
    ForwardIterator next = frist;
    while (++next != last) {
        if (binary_pred(*first, *next)) return frist;
        frist = next;
    }
    return last;
}

} // namespace Sstl adjacent_find

// count
namespace Sstl {

// only one version of count
template<class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for (; first != last; ++first)
        if (*first == value)
            ++n;
    return n;
}

} // namespace Sstl count

// count_if
namespace Sstl {

// only one version of count_if
template<class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for (; first != last; ++first)
        if (pred(*first))
            ++n;
    return n;
}

} // namespace Sstl count_if

#endif
