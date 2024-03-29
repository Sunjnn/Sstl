#ifndef __STL_ALGO_H__
#define __STL_ALGO_H__

#include "stl_iterator.h"
#include "stl_algobase.h"
#include "stl_heap.h"

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

// find_end
namespace Sstl {

// first of two versions of find_end
template<class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1
find_end(ForwardIterator1 first1, ForwardIterator1 last1,
         ForwardIterator2 first2, ForwardIterator2 last2) {
    typedef typename iterator_traits<ForwardIterator1>::iterator_category
        category1;
    typedef typename iterator_traits<ForwardIterator2>::iterator_category
        category2;

    return __find_end(first1, last1, first2, last2, category1(), category2());
}

template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            forward_iterator_tag, forward_iterator_tag) {
    if (first2 == last2) return last1;

    ForwardIterator1 result = last1;
    while (1) {
        ForwardIterator1 new_result = search(first1, last1, first2, last2);
        if (new_result == last1) return result;
        result = new_result;
        first1 = new_result;
        ++first1;
    }
}

template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
           BidirectionalIterator2 first2, BidirectionalIterator2 last2,
           bidirectional_iterator_tag, bidirectional_iterator_tag) {
    typedef reverse_iterator<BidirectionalIterator1> reviter1;
    typedef reverse_iterator<BidirectionalIterator2> reviter2;

    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = search(reviter1(last1), rlast1,
                              reviter2(last2), rlast2);

    if (rresult == rlast1) return last1;
    BidirectionalIterator1 result = rresult.base();
    advance(result, -distance(first2, last2));
    return result;
}

// second of two versions of find_end
template<class ForwardIterator1, class ForwardIterator2, class Predicate>
inline ForwardIterator1
find_end(ForwardIterator1 first1, ForwardIterator1 last1,
         ForwardIterator2 first2, ForwardIterator2 last2, Predicate pred) {
    typedef typename iterator_traits<ForwardIterator1>::iterator_category
        category1;
    typedef typename iterator_traits<ForwardIterator2>::iterator_category
        category2;

    return __find_end(first1, last1, first2, last2, pred,
                      category1(), category2());
}

template<class ForwardIterator1, class ForwardIterator2, class Predicate>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                            ForwardIterator2 first2, ForwardIterator2 last2,
                            Predicate pred,
                            forward_iterator_tag, forward_iterator_tag) {
    if (first2 == last2) return last1;

    ForwardIterator1 result = last1;
    while (1) {
        ForwardIterator1 new_result = search(first1, last1, first2, last2, pred);
        if (new_result == last1) return result;
        result = new_result;
        first1 = new_result;
        ++first1;
    }
}

template<class BidirectionalIterator1, class BidirectionalIterator2,
         class Predicate>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
           BidirectionalIterator2 first2, BidirectionalIterator2 last2,
           Predicate pred,
           bidirectional_iterator_tag, bidirectional_iterator_tag) {
    typedef reverse_iterator<BidirectionalIterator1> reviter1;
    typedef reverse_iterator<BidirectionalIterator2> reviter2;

    reviter1 rlast1(first1);
    reviter2 rlast2(first2);
    reviter1 rresult = search(reviter1(last1), rlast1,
                              reviter2(last2), rlast2, pred);

    if (rresult == rlast1) return last1;
    BidirectionalIterator1 result = rresult.base();
    advance(result, -distance(first2, last2));
    return result;
}

} // namespace Sstl find_end

// find_first_of
namespace Sstl {

// first of two versions of find_first_of
template<class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2) {
    for (; first1 != last1; ++first1)
        for (ForwardIterator iter = first2; iter != last2; ++iter)
            if (*first1 == *iter)
                return first1;
    return last1;
}

// second of two versions of find_first_of
template<class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2,
                            BinaryPredicate comp) {
    for (; first1 != last1; ++first1)
        for (ForwardIterator iter = first2; iter != last2; ++iter)
            if (comp(*first1, *iter))
                return first1;
    return last1;
}

} // namespace Sstl find_first_of

// for_each
namespace Sstl {

// only one version of for_each
template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
    for (; first != last; ++first)
        f(*first);
    return f;
}

} // namespace Sstl for_each

// generate
namespace Sstl {

template<class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
    for (; first != last; ++first)
        *first = gen();
}

} // namespace Sstl generate

// generate_n
namespace Sstl {

template<class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
    for (; n > 0; --n, ++first)
        *first = gen();
    return first;
}

} // namespace Sstl generate_n

// include
namespace Sstl {
// S1 and S2 are sorted
// the number of a element in S1 is m and that in S2 is n
// if m >= n, return true
// else return false

// first of two versions of include
template<class InputIterator1, class InputIterator2>
bool include(InputIterator1 first1, InputIterator1 last1,
             InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1)
            return false;
        else if (*first1 < *first2)
            ++first1;
        else
            ++first1, ++first2;
    }
    return first2 == last2;
}

// second of two version of include
template<class InputIterator1, class InputIterator2, class Compare>
bool include(InputIterator1 first1, InputIterator1 last1,
             InputIterator2 first2, InputIterator2 last2, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1))
            return false;
        else if (comp(*first1, *first2))
            ++first1;
        else
            ++first1, ++first2;
    }
    return first2 == last2;
}

} // namespace Sstl include

// max_element
namespace Sstl {

// first of two versions of max_element
template<class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (*result < *first) result = first;
    return result;
}

// second of two versions of max_element
template<class ForwardIterator, class Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last,
                            Compare comp) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (comp(*result, *first)) result = first;
    return result;
}

} // namespace Sstl max_element

// min_element
namespace Sstl {

// first of two versions of min_element
template<class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (*first < *result) result = first;
    return result;
}

// second of two versions of min_element
template<class ForwardIterator, class Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last,
                            Compare comp) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (comp(*first, *result)) result = first;
    return result;
}

} // namespace Sstl min_element

// partition
namespace Sstl {

template<class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first,
                                BidirectionalIterator last,
                                Predicate pred) {
    while (true) {
        while (true)
            if (first == last)
                return first;
            else if (pred(*first))
                ++first;
            else
                break;
        --last;
        while (true)
            if (first == last)
                return first;
            else if (!pred(*last))
                --last;
            else
                break;
        iter_swap(first, last);
        ++first
    }
}

} // namespace Sstl partition

// remove
namespace Sstl {

// remove element which is equal to value, do not erase them, they are replaced
// by other elements.
template<class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last,
                       const T& value) {
    first = find(first, last, value);
    ForwardIterator next = first;
    return first == last ? first : remove_copy(++next, last, first, value);
}

} // namespace Sstl remove

// remove_copy
namespace Sstl {

// remove element which is equal to value. they are not be erased but replaced
// by other elements.
template<class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last,
                           OutputIterator result, const T& value) {
    for (; first != last; ++first)
        if (*first != last; ++first) {
            *result = *first;
            ++result;
        }
    return result;
}

} // namespace Sstl remove_copy

// remove_if
namespace Sstl {

// remove element which passing to pred return true. they are not be erased but
// replaced by other elements.
template<class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
                          Predicate pred) {
    first = find_if(first, last, pred);
    ForwardIterator next = first;
    return first == last ? first : remove_copy_if(++next, last, first, pred);
}

} // namespace Sstl remove_if

// remove_copy_if
namespace Sstl {

// remove element which passing to pred return true. they are not be erased but
// replaced by other elements.
template<class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last,
                              OutputIterator result, Predicate pred) {
    for (; first != last; ++first)
        if (!pred(*first)) {
            *result = *first;
            ++result;
        }
    return result;
}

} // namespace Sstl remove_copy_if

// replace
namespace Sstl {

// replace old value with new value
template<class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last,
             const T& old_value, const T& new_value) {
    for (; first != last; ++first)
        if (*first == old_value) *first = new_value;
}

} // namespace Sstl replace

// replace_copy
namespace Sstl {

// replace old value with new value
template<class InputIterator, class OutputIterator, class T>
void replace_copy(InputIterator first, InputIterator last,
                  OutputIterator result,
                  const T& old_value, const T& new_value) {
    for (; first != last; ++first, ++result)
        *result = *first == old_value ? new_value : *first;
    return result;
}

} // namespace Sstl replace_copy

// replace_if
namespace Sstl {

// replace old value with new value
template<class ForwardIterator, class Predicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last,
                Predicate pred, const T& new_value) {
    for (; first != last; ++first)
        if (pred(*first)) *first = new_value;
}

} // namespace Sstl replace_if

// replace_copy_if
namespace Sstl {

// replace old value with new value
template<class InputIterator, class OutputIterator, class Predicate, class T>
void replace_copy_if(InputIterator first, InputIterator last,
                     OutputIterator result, Predicate pred,
                     const T& new_value) {
    for (; first != last; ++first, ++result)
        *result = pred(*first) ? new_value : *first;
    return result;
}

} // namespace Sstl replace_copy_if

// reverse
namespace Sstl {

// only one version of reverse
template<class BidirectionalIterator>
inline void reverse(BidirectionalIterator first, BidirectionalIterator last) {
    __reverse(first, last, iterator_category(first));
}

template<class BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last,
               bidirectional_iterator_tag) {
    while (true)
        if (first == last || first == --last)
            return;
        else
            iter_swap(first++, last);
}

template<class RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last,
               random_access_iterator_tag) {
    while (first < last) iter_swap(first++, --last);
}

} // namespace Sstl reverse

// reverse_copy
namespace Sstl {

template<class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator result) {
    while (first != last) {
        --last;
        *result = *last;
        ++result;
    }
    return result;
}

} // namespace Sstl reverse_copy

// rotate
namespace Sstl {

template<class ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle,
                   ForwardIterator last) {
    if (first == middle || middle == last) return;
    __rotate(first, middle, last, distance_type(first),
             iterator_category(first));
}

template<class ForwardIterator, class Distance>
void __rotate(ForwardIterator first, ForwardIterator middle,
              ForwardIterator last, Distance*, forward_iterator_tag) {
    for (ForwardIterator i = middle;;) {
        iter_swap(first, i);
        ++first;
        ++i;
        if (first == middle) {
            if (i == last) return;
            middle = i;
        }
        else if (i == last)
            i = middle;
    }
}

template<class BidirectionalIterator, class Distance>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle,
              BidirectionalIterator last, Distance*,
              bidirectional_iterator_tag) {
    reverse(first, middle);
    reverse(middle, last);
    reverse(first, last);
}

template<class RandomAccessIterator, class Distance>
void __rotate(RandomAccessIterator first, RandomAccessIterator middle,
              RandomAccessIterator last, Distance*,
              random_access_iterator_tag) {
    Distance n = __gcd(last - first, middle - first);
    while (n--) {
        __rotate_cycle(first, last, first + n, middle - first,
                       value_type(first));
    }
}

template<class EuclideanRingElement>
EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n) {
    while (n != 0) {
        EuclideanRingElement t = m % n;
        m = n;
        n = t;
    }
    return m;
}

template<class RandomAccessIterator, class Distance, class T>
void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last,
                    RandomAccessIterator initial, Distance shift, T*) {
    T value = *initial;
    RandomAccessIterator ptr1 = initial;
    RandomAccessIterator ptr2 = ptr1 + shift;
    while (ptr2 != initial) {
        *ptr1 = *ptr2;
        ptr1 = ptr2;
        if (last - ptr2 > shift)
            ptr2 += shift;
        else
            ptr2 = first + (shift - (last - ptr2));
    }
    *ptr1 = value;
}

} // namespace Sstl rotate

// rotate_copy
namespace Sstl {

template<class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle,
                           ForwardIterator last, OutputIterator result) {
    return copy(first, middle, copy(middle, last, result));
}

} // namespace Sstl rotate_copy

// search
namespace Sstl {

template<class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 search(ForwardIterator1 first1,
                               ForwardIterator1 last1,
                               ForwardIterator2 first2,
                               ForwardIterator2 last2) {
    return __search(first1, last1, first2, last2, distance_type(first1),
                    distance_type(first2));
}

template<class ForwardIterator1, class ForwardIterator2, class Distance1,
         class Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2,
                          Distance1*, Distance2*) {
    Distance1 d1 = 0;
    distance(first1, last1, d1);
    Distance2 d2 = 0;
    distance(first2, last2, d2);

    if (d1 < d2) return last1;

    ForwardIterator1 current1 = first1;
    ForwardIterator2 current2 = first2;

    while (current2 != last2) {
        if (*current1 == *current2) {
            ++current1;
            ++current2;
        }
        else {
            if (d1 == d2)
                return last1;
            else {
                current1 = ++first1;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

} // namespace Sstl search

// search_n
namespace Sstl {

// first of two version of search_n
template<class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first,
                         ForwardIterator last,
                         Integer count, const T& value) {
    if (count < 0)
        return first;
    else {
        first = find(first, last, value);
        while (first != last) {
            Integer n = count - 1;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 0 && *i == value) {
                ++i;
                --n;
            }
            if (n == 0)
                return first;
            else
                first = find(i, last, value);
        }
        return last;
    }
}

// second of two version of search_n
template<class ForwardIterator, class Integer, class T,
         class BinaryPredicate>
ForwardIterator search_n(ForwardIterator first,
                         ForwardIterator last,
                         Integer count, const T& value,
                         BinaryPredicate binary_pred) {
    if (count <= 0)
        return first;
    else {
        while (first != last) {
            if (binary_pred(*first, value)) break;
            ++first;
        }
        while (first != last) {
            Integer n = count - 1;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 0 && binary_pred(*i, value)) {
                ++i;
                --n;
            }
            if (n == 0)
                return first;
            else {
                while (i != last) {
                    if (binary_pred(*i, value)) break;
                    ++i;
                }
                first = i;
            }
        }
        return last;
    }
}

} // namespace Sstl search_n

// swap_ranges
namespace Sstl {

template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1,
                             ForwardIterator1 last1,
                             ForwardIterator2 first2,
                             ForwardIterator2 last2) {
    for (; first1 != last1; ++first1, ++first2)
        iter_swap(first1, first2);
    return first2;
}

} // namespace Sstl swap_ranges

// transform
namespace Sstl {

// first of two versions of transform
template<class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last,
                         OutputIterator result, UnaryOperation op) {
    for (; first != last; ++first, ++result)
        *result = op(*first);
    return result;
}

// second of two version of transform
template<class InputIterator1, class InputIterator2, class OutputIterator,
         class BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, OutputIterator result,
                         BinaryOperation binary_op) {
    for (; first1 != last1; ++first1, ++first2, ++result)
        *result = binary_op(*first1, *first2);
    return result;
}

} // namespace Sstl transform

// unique
namespace Sstl {

template<class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
    first = adjacent_find(first, last);
    return unique_copy(first, last, first);
}

} // namespace Sstl unique

// unique_copy
namespace Sstl {

template<class InputIterator, class OutputIterator>
inline OutputIterator unique_copy(InputIterator first,
                                  InputIterator last,
                                  OutputIterator result) {
    if (first == last) return result;
    return __unique_copy(first, last, result, iterator_category(result));
}

template<class InputIterator, class ForwardIterator>
ForwardIterator __unique_copy(InputIterator first,
                              InputIterator last,
                              ForwardIterator result,
                              forward_iterator_tag) {
    *result = *first;
    while (++first != last)
        if (*result != *first) *++result = *first;
    return ++result;
}

template<class InputIterator, class OutputIterator>
inline OutputIterator __unique_copy(InputIterator first,
                                    InputIterator last,
                                    OutputIterator result,
                                    output_iterator_tag) {
    return __unique_copy(first, last, result, value_type(first));
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator __unique_copy(InputIterator first, InputIterator last,
                             OutputIterator result, T*) {
    T value = *first;
    *result = value;
    while (++first != last) {
        if (value != *first) {
            value = *first;
            *++result = value;
        }
    }
    return ++result;
}

} // namespace Sstl unique_copy

// lower_bound
namespace Sstl{

template<class ForwardIterator, class T>
inline ForwardIterator lower_bound(ForwardIterator first,
                                   ForwardIterator last,
                                   const T& value) {
    return __lower_bound(first, last, value, distance_type(first),
                         iterator_category(first));
}

template<class ForwardIterator, class T, class Distance>
ForwardIterator __lower_bound(ForwardIterator first,
                              ForwardIterator last,
                              const T& value,
                              Distance*,
                              forward_iterator_tag) {
    Distance len = 0;
    distance(first, last, len);
    Distance half;
    ForwardIterator middle;

    while (len > 0) {
        half = len >> 1;
        middle = first;
        advance(middle, half);
        if (*middle < value) {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else
            len = half;
    }
    return first;
}

template<class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first,
                                   RandomAccessIterator last,
                                   const T& value,
                                   Distance*,
                                   random_access_iterator_tag) {
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;

    while (len > 0) {
        half = len >> 1;
        middle = first + half;
        if (*middle < value) {
            first = middle + 1;
            len = len - half - 1;
        }
        else
            len = half;
    }
    return first;
}

} // namespace Sstl lower_bound

// upper_bound
namespace Sstl {

template<class ForwardIterator, class T, class Compare>
inline ForwardIterator upper_bound(ForwardIterator first,
                                   ForwardIterator last,
                                   const T& value) {
    return __upper_bound(first, last, value, distance_type(first),
                         iterator_category(first));
}

template<class ForwardIterator, class T, class Distance>
ForwardIterator __upper_bound(ForwardIterator first,
                              ForwardIterator last,
                              const T& value,
                              Distance*,
                              forward_iterator_tag) {
    Distance len = 0;
    distance(first, last, len);
    Distance half;
    ForwardIterator middle;

    while (len > 0) {
        half = len >> 1;
        middle = first;
        advance(middle, half);
        if (value < *middle)
            len = half;
        else {
            first = middle;
            ++first;
            len = len - half - 1;
        }
    }
    return first;
}

template<class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first,
                              RandomAccessIterator last,
                              const T& value,
                              Distance*,
                              random_access_iterator_tag) {
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;

    while (len > 0) {
        half = len >> 1;
        middle = first + half;
        if (value < *middle)
            len = half;
        else {
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

} // namespace Sstl upper_bound

// next_permutation
namespace Sstl {

// return the next queue in lexicographical order
template<class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first,
                      BidirectionalIterator last) {
    if (first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if (i == last) return false;
    i = last;
    --i;
    for (;;) {
        BidirectionalIterator ii = i;
        --i;
        if (*i < *ii) {
            BidirectionalIterator j = last;
            while (!(*i < *--j));
            iter_swap(i, j);
            reverse(ii, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}

} // namespace Sstl next_permutation

// prev_permutation
namespace Sstl {

// return the last queue in lexicographical order
template<class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first,
                      BidirectionalIterator last) {
    if (first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if (i == last) return false;
    i = last;
    --i;

    for (;;) {
        BidirectionalIterator ii = i;
        --i;
        if (*ii < *i) {
            BidirectionalIterator j = last;
            while (!(*--j < *i));
            iter_swap(i, j);
            reverse(ii, last);
            return true;
        }
        if (i == first) {
            reverse(first, last);
            return false;
        }
    }
}

} // namespace Sstl prev_premutation

// random_shuffle
namespace Sstl {

// first of two versions of random_shuffle
template<class RandomAccessIterator>
inline void random_shuffle(RandomAccessIterator first,
                           RandomAccessIterator last) {
    __random_shuffle(first, last, distance_type(first));
}

template<class RandomAccessIterator, class Distance>
void __random_shuffle(RandomAccessIterator first,
                      RandomAccessIterator last,
                      Distance*) {
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i != last; ++i)
        iter_swap(i, first + Distance(rand() % ((i - first) + 1)));
}

// second of two versions of random_shuffle
template<class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
                    RandomNumberGenerator& rand) {
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i!= last; ++i)
        iter_swap(i, first + rand((i - first) + 1));
}

} // namespace Sstl random_shuffle

// partial_sort
namespace Sstl {

template<class RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first,
                         RandomAccessIterator middle,
                         RandomAccessIterator last) {
    __partial_sort(first, middle, last, value_type(first));
}

template<class RandomAccessIterator, class T>
void __partial_sort(RandomAccessIterator first,
                    RandomAccessIterator middle,
                    RandomAccessIterator last, T*) {
    make_heap(first, middle);
    for (RandomAccessIterator i = middle; i < last; ++i)
        if (*i < *first)
            __pop_heap(first, middle, i, T(*i), distance_type(first));
    sort_heap(first, middle);
}

} // namespace Sstl partial_sort

// partial_sort_copy
namespace Sstl {

template<class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator
partial_sort_copy(InputIterator first,
                  InputIterator last,
                  RandomAccessIterator result_first,
                  RandomAccessIterator result_last) {
    InputIterator i1 = first;
    RandomAccessIterator i2 = result_first;
    while (i1 != last) {
        *i2 = *i1;
        ++i1;
        ++i2;
    }
    partial_sort(result_first, result_last, result_last);
    return result_last;
}

} // namespace Sstl partial_sort_copy

// sort
namespace Sstl {

template<class RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first,
                      RandomAccessIterator last) {
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i != last; ++i)
        __linear_insert(first, i, value_type(first));
}

template<class RandomAccessIterator, class T>
inline void __linear_insert(RandomAccessIterator first,
                            RandomAccessIterator last, T*) {
    T value = *last;
    if (value < *first) {
        copy_backward(first, last, last + 1);
        *first = value;
    }
    else
        __unguarded_linear_insert(last, value);
}

template<class RandomAccessIterator, class T>
void __unguarded_linear_insert(RandomAccessIterator last, T value) {
    RandomAccessIterator next = last;
    --next;
    while (value < *next) {
        *last = *next;
        last = next;
        --next;
    }
    *last = value;
}

template<class T>
inline const T& __median(const T& a, const T& b, const T& c) {
    if (a < b)
        if (b < c)
            return b;
        else if (a < c)
            return c;
        else
            return a;
    else if (a < c)
        return a;
    else if (b < c)
        return c;
    return b;
}

template<class RandomAccessIterator, class T>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first,
                                           RandomAccessIterator last,
                                           T pivot) {
    while (true) {
        while (*first < pivot) ++first;
        --last;
        while (pivot < *last) --last;
        if (!(first < last)) return first;
        iter_swap(first, last);
        ++first;
    }
}

template<class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first != last) {
        __introsort_loop(first, last, value_type(first), __lg(last-first) * 2);
        __final_insertion_sort(first, last);
    }
}

template<class Size>
inline Size __lg(Size n) {
    Size k;
    for (k = 0; n > 1; n >>= 1) ++k;
    return k;
}

const int __stl_threshold = 16;

template<class RandomAccessIterator, class T, class Size>
void __introsort_loop(RandomAccessIterator first, RandomAccessIterator last,
                      T*, Size depth_limit) {
    while (last - first > __stl_threshold) {
        if (depth_limit == 0) {
            partial_sort(first, last, last);
            return;
        }
        --depth_limit;
        RandomAccessIterator cut = __unguarded_partition(first, last,
                                    T(__median(*first,
                                               *(first + (last - first) / 2),
                                               *(last - 1))));
        __introsort_looploop(cut, last, value_type(first), depth_limit);
        last = cut;
    }
}

template<class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first,
                            RandomAccessIterator last) {
    if (last - first > __stl_threshold) {
        __insertion_sort(first, first + __stl_threshold);
        __unguarded_insertion_sort(first + __stl_threshold, last);
    }
    else
        __insertion_sort(first, last);
}

template<class RandomAccessIterator>
inline void __unguarded_insertion_sort(RandomAccessIterator first,
                                       RandomAccessIterator last) {
    __unguarded_insertion_sort_aux(first, last, value_type(first));
}

template<class RandomAccessIterator, class T>
void __unguarded_insertion_sort_aux(RandomAccessIterator first,
                                    RandomAccessIterator last,
                                    T*) {
    for (RandomAccessIterator i = first; i != last; ++i)
        __unguarded_linear_insert(i, T(*i));
}

} // namespace Sstl sort

// equal_range
namespace Sstl {

template<class ForwardIterator, class T>
inline pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last, const T&  value) {
    return __equal_range(first, last, value, distance_type(first),
                         iterator_category(first));
}

template<class RandomAccessIterator, class T, class Distance>
pair<RandomAccessIterator, RandomAccessIterator>
__equal_range(RandomAccessIterator first, RandomAccessIterator last,
              const T& value, Distance*, random_access_iterator_tag) {
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle, left, right;

    while (len > 0) {
        half = len >> 1;
        middle = first + half;
        if (*middle < value) {
            first = middle + 1;
            len = len - half - 1;
        }
        else if (value < *middle)
            len = half;
        else {
            left = lower_bound(first, middle, value);
            right = upper_bound(++middle, first + len, value);
            return pair<RandomAccessIterator, RandomAccessIterator>(left, right);
        }
    }
    return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
}

template<class ForwardIterator, class T, class Distance>
pair<ForwardIterator, ForwardIterator>
__equal_range(ForwardIterator first, ForwardIterator last, const T& value,
              Distance*, forward_iterator_tag) {
    Distance len = 0;
    distance(first, last, len);
    Distance half;
    ForwardIterator middle, left, right;

    while (len > 0) {
        half = len >> 1;
        middle = first;
        advance(middle, half);
        if (*middle < value) {
            first = middle;
            ++first;
            len = len - half - 1;
        }
        else if (value < *middle)
            len = half;
        else {
            left = lower_bound(first, middle, value);
            advance(first, len);
            right = upper_bound(++middle, first, value);
            return pair<ForwardIterator, ForwardIterator>(left, right);
        }
    }
    return pair<ForwardIterator, ForwardIterator>(first, first);
}

} // namespace Sstl equal_range

// inplace_merge
namespace Sstl {

template<class BidirectionalIterator>
inline void inplace_merge(BidirectionalIterator first,
                          BidirectionalIterator middle,
                          BidirectionalIterator last) {
    if (first == middle || middle == last) return;
    __inplace_merge_aux(first, middle, last, value_type(first),
                        distance_type(first));
}

template<class BidirectionalIterator, class T, class Distance>
inline void __inplace_merge_aux(BidirectionalIterator first,
                                BidirectionalIterator middle,
                                BidirectionalIterator last,
                                T*, Distance*) {
    Distance len1 = 0;
    distance(first, middle, len1);
    Distance len2 = 0;
    distance(middle, last, len2);

    temporary_buffer<BidirectionalIterator, T> buf(first, last);
    if (buf.begin() == 0)
        __merge_without_buffer(first, middle, last, len1, len2);
    else
        __merge_adaptive(first, middle, last, len1, len2,
                         buf.begin(), Distance(buf.size()));
}

template<class BidirectionalIterator, class Distance, class Pointer>
void __merge_adaptive(BidirectionalIterator first,
                      BidirectionalIterator middle,
                      BidirectionalIterator last,
                      Distance len1, Distance len2,
                      Pointer buffer, Distance buffer_size) {
    if (len1 <= len2 && len1 <= buffer_size) {
        Pointer end_buffer = copy(first, middle, buffer);
        merge(buffer, end_buffer, middle, last, first);
    }
    else if (len2 <= buffer_size) {
        Pointer end_buffer = copy(middle, last, buffer);
        __merge_backward(first, middle, buffer, end_buffer, last);
    }
    else {
        BidirectionalIterator first_cut = first;
        BidirectionalIterator second_cut = middle;
        Distance len11 = 0;
        Distance len22 = 0;
        if (len1 > len2) {
            len11 = len1 / 2;
            advance(first_cut, len11);
            second_cut = lower_bound(middle, last, *first_cut);
            distance(middle, second_cut, len22);
        }
        else {
            len22 = len2 / 2;
            advance(second_cut, len22);
            first_cut = upper_bound(first, middle, *second_cut);
            distance(first, first_cut, len11);
        }
        BidirectionalIterator new_middle =
            __rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
                              len22, buffer, buffer_size);
        __merge_adaptive(first, first_cut, new_middle, len11, len22, buffer,
                         buffer_size);
        __merge_adaptive(new_middle, second_cut, last, len1 - len11,
                         len2 - len22, buffer, buffer_size);
    }
}

template<class BidirectionalIterator1, class BidirectionalIterator2,
         class Distance>
BidirectionalIterator1 __rotate_adaptive(BidirectionalIterator1 first,
                                         BidirectionalIterator1 middle,
                                         BidirectionalIterator1 last,
                                         Distance len1, Distance len2,
                                         BidirectionalIterator2 buffer,
                                         Distance buffer_size) {
    BidirectionalIterator2 buffer_end;
    if (len1 > len2 && len2 <= buffer_size) {
        buffer_end = copy(middle, last, buffer);
        copy_backward(buffer, middle, last);
        return copy(buffer, buffer_end, first);
    }
    else if (len1 <= buffer_size) {
        buffer_end = copy(first, middle, buffer);
        copy(middle, last, first);
        return copy_backward(buffer, buffer_end, last);
    }
    else {
        rotate(first, middle, last);
        advance(first, len2);
        return first;
    }
}

} // namespace Sstl inplace_merge

// nth_element
namespace Sstl {

template<class RandomAccessIterator>
inline void nth_element(RandomAccessIterator first,
                        RandomAccessIterator nth,
                        RandomAccessIterator last) {
    __nth_element(first, nth, last, value_type(first));
}

template<class RandomAccessIterator, class T>
void __nth_element(RandomAccessIterator first,
                   RandomAccessIterator nth,
                   RandomAccessIterator last, T*) {
    while (last - first > 3) {
        RandomAccessIterator cut = __unguarded_partition(first, last,
                                    T(__median(*first,
                                               *(first + (last - first)/2),
                                               *(last - 1))));
        if (cut <= nth)
            first = cut;
        else
            last = cut;
    }
    __insertion_sort(first, last);
}

} // namespace Sstl nth_element

// mergesort
namespace Sstl {

template<class BidirectionalIterator>
void mergesort(BidirectionalIterator first, BidirectionalIterator last) {
    typename iterator_traits<BidirectionalIterator>::difference_type n =
                                                        distance(first, last);
    if (n == 0 || n == 1)
        return;
    else {
        BidirectionalIterator mid = first + n / 2;
        mergesort(first, mid);
        mergesort(mid, last);
        inplace_merge(first, mid, last);
    }
}

} // namespace Sstl mergesort

// merge
namespace Sstl {

// first of two versions of merge
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) {
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

// second of two versions of merge
template<class InputIterator1, class InputIterator2, class OutputIterator,
         class Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1)) {
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

} // namespace Sstl merge

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
