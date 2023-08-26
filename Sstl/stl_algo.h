#ifndef __STL_ALGO_H__
#define __STL_ALGO_H__

#include "stl_iterator.h"
#include "stl_algobase.h"

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
