#ifndef __STL_ALGOBASE_H__
#define __STL_ALGOBASE_H__

// equal
namespace Sstl {

// first version of two of equal
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    for (; first1 != last1; ++first1, ++first2)
        if (*first1 != *first2)
            return false;
    return true;
}

// second version of two of equal
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred) {
    for (; first1 != last1; ++first1, ++first2)
        if (!binary_pred(*first1, *first2))
            return false;
    return true;
}

} // namepace equal

// fill and fill_n
namespace Sstl {

// the only one version of fill
template<class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
    for (; first != last; ++first)
        *first = value;
}

// the only one version fo fill_n
template<class ForwardIterator, class Size, class T>
void fill(ForwardIterator first, Size n, const T& value) {
    for (; n > 0; --n, ++first)
        *first = value;
    return first;
}

} // namespace fill and fill_n

#endif
