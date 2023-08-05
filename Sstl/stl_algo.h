#ifndef __STL_ALGO_H__
#define __STL_ALGO_H__

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

#endif
