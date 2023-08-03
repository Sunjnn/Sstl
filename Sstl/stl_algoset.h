#ifndef __STL_ALGOSET_H__
#define __STL_ALGOSET_H__

#include "stl_algobase.h"

// set union
namespace Sstl {

// if the number of a element in set1 is m and that in set2 is n,
// so that in output set is max(m, n)

// first of two version of algorithm set union
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            ++first1;
        }
        else if (*first2 < *first1) {
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }

    return copy(first2, last2, copy(first1, last1, result));
}

// second version of two of algorithm set union
template<class InputIterator1, class InputIterator2,
         class OutputIterator, class BinaryOperation>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, BinaryOperation comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) {
            *result = *first1;
            ++first1;
        }
        else if (comp(*first2, *first1)) {
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }

    return copy(first2, last2, copy(first1, last1, result));
}

} // namespace Sstl set union

// ser intersection
namespace Sstl {

// if the number of a element in set1 is m and that in set2 is n,
// so that in output set is min(m, n)


// first of two versions of algorithm set intersection
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2)
            ++first1;
        else if (*first2 < *first1)
            ++first2;
        else {
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
}

// second of two versions of algorithm ser intersection
template<class InputIterator1, class InputIterator2,
         class OutputIterator, class BinaryOperation>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, BinaryOperation comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2))
            ++first1;
        else if (comp(*first2, *first1))
            ++first2;
        else {
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
}

} // namespace Sstl set intersection

// set difference
namespace Sstl {

// if the number of a element in set1 is m and that in set2 is n,
// so that in output set is max(m - n, 0)

// first of two versions of algorithm set difference
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2,
                              OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) {
            *result = *first1;
            ++first1;
            ++result;
        }
        else if (*first2 < *first1)
            ++first2;
        else {
            ++first1;
            ++first2;
        }
    }
    return copy(first1, first2, result);
}

// second of two versions of algorithm set difference
template<class InputIterator1, class InputIterator2,
         class OutputIterator, class BinaryOperation>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, BinaryOperation comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) {
            *result = *first1;
            ++first1;
            ++result;
        }
        else if (comp(*first2, *first1))
            ++first2;
        else {
            ++first1;
            ++first2;
        }
    }
    return copy(first1, first2, result);
}

} // namespace Sstl set difference

// set symmetric difference
namespace Sstl {

// the number of a element in set1 is m and that in set2 is n,
// so that in output set is |n - m|

// first of two versions of algorithm set symmetric difference
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_symmetric_difference(InputIterator1 first1,
                                        InputIterator1 last1,
                                        InputIterator2 first2,
                                        InputIterator2 last2,
                                        OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < first2) {
            *result = *first1;
            ++first1;
            ++first2;
        }
        else if (*first2 < *first1) {
            *result = *first2;
            ++first1;
            ++first2;
        }
        else {
            ++first1;
            ++first2;
        }
    }
    return copy(first2, last2, copy(first1, last1, result));
}

// second of two versions of algorithm set symmetric difference
template<class InputIterator1, class InputIterator2,
         class OutputIterator, class BinaryOperation>
OutputIterator set_symmetric_difference(InputIterator1 first1,
                                        InputIterator1 last1,
                                        InputIterator2 first2,
                                        InputIterator2 last2,
                                        OutputIterator result,
                                        BinaryOperation comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) {
            *result = *first1;
            ++first1;
            ++first2;
        }
        else if (comp(*first2, *first1)) {
            *result = *first2;
            ++first1;
            ++first2;
        }
        else {
            ++first1;
            ++first2;
        }
    }
    return copy(first2, last2, copy(first1, last1, result));
}

} // namespace Sstl set symmetric difference

#endif
