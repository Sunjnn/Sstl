#ifndef __STL_ALGOBASE_H__
#define __STL_ALGOBASE_H__

#include "stl_pair.h"

#include <cstddef>
#include <cstring>

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

// iter swap
namespace Sstl {

// the only one version of iter swap
template<class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
    template<class ForwardIterator1, class ForwardIterator2, class T>
    inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*);
    __iter_swap(a, b, value_type(a));
}

template<class ForwardIterator1, class ForwardIterator2, class T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

} // namespace iter swap

// lexicographical compare
namespace Sstl {

// first version of three of lexicographical compare
template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (*first1 < *first2)
            return true;
        else if (*first2 < *first1)
            return false;
    }
    return first1 == last1 && first2 != last2;
}

// second version of three lexicographical compare
template<class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2,
                             Compare comp) {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (comp(*first1, *first2))
            return true;
        else if (comp(*first2, *first1))
            return false;
    }
    return first1 == last1 && first2 != last2;
}

// third version of three lexicographical compare
inline bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1,
                                    const unsigned char* first2, const unsigned char* last2) {
    const size_t len1 = last1 - first1;
    const size_t len2 = last2 - first2;

    const int result = memcmp(first1, first2, min(len1, len2));

    return result != 0 ? result < 0 : len1 < len2;
}

} // namespace Sstl lexicographical compare

// max
namespace Sstl {

// first version of two of max
template<class T>
inline const T& max(const T& a, const T& b) {
    return a < b ? b : a;
}

// second version of two of max
template<class T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? b : a;
}

} // namespace Sstl max

// min
namespace Sstl {

// first version of two of min
template<class T>
inline const T& min(const T& a, const T& b) {
    return b < a ? b : a;
}

// second version of two of min
template<class T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? b : a;
}

} // namespace Sstl min

// mismatch
namespace Sstl {

// first version of two of mismatch
template<class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
                                              InputIterator2 first2) {
    while (first1 != last1 && *first1 == *first2) {
        ++first1;
        ++first2;
    }
    return pair<InputIterator1, InputIterator2>(first1, first2);
}

// second version of two of mismatch
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1,
                                              InputIterator2 first2, BinaryPredicate binary_pred) {
    while (first1 != last1 && binary_pred(*first1, *first2)) {
        ++first1;
        ++first2;
    }
    return pair<InputIterator1, InputIterator2>(first1, first2);
}

} // namespace Sstl mismatch

#endif
