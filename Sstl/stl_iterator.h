#ifndef __STL_ITERATOR_H__
#define __STL_ITERATOR_H__

#include <cstddef>

namespace Sstl {

// five categories of iterator
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// heir this class when define new iterator class
template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
};

template<class I>
struct iterator_traits {
    typedef typename I::iterator_category   iterator_category;
    typedef typename I::value_type          value_type;
    typedef typename I::difference_type     difference_type;
    typedef typename I::pointer             pointer;
    typedef typename I::reference           reference;
};

// partial specilization of traits for native pointer
template<class T>
struct iterator_traits<T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};

// partial specilization of traits for native pointer-to-const
template<class T>
struct iterator_traits<const T*> {
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
};

}

namespace Sstl {

template<class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

template<class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

template<class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

}

namespace Sstl {

template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
    iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

template<class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
    return last - first;
}

template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
    typedef iterator_traits<InputIterator>::iterator_category category;
    return __distance(first, last, category());
}

}

namespace Sstl {

template<class InputIterator, class Distance>
inline void __advance(InputIterator &i, Distance n, input_iterator_tag) {
    while (n--) ++i;
}

template<class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag) {
    if (n >= 0)
        while (n--) ++i;
    else
        while (n++) --i;
}

template<class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator &i, Distance n, random_access_iterator_tag) {
    i += n;
}

template<class InputIterator, class Distance>
inline void advance(InputIterator &i, Distance n) {
    __advance(i, n, iterator_category(i));
}

}

#endif