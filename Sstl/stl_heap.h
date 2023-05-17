#ifndef __STL_HEAP_H__
#define __STL_HEAP_H__

#include "stl_iterator.h"

// define push function of heap
namespace Sstl {

template<class randomAccessIterator, class Distance, class T>
void __push_heap(randomAccessIterator first, Distance holeIndex, Distance topIndex, T value) {
    Distance parent = (holeIndex - 1) / 2;
    // compare level by level, until top node or cur <= parent
    while (holeIndex > topIndex && *(first + parent) < value) {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

template<class randomAccessIterator, class Distance, class T>
inline void __push_heap_aux(randomAccessIterator first, randomAccessIterator last, Distance*, T*) {
    __push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
}

// new element has already been in the last position
template<class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
    __push_heap_aux(first, last, distance_type(first), value_type(first));
}

} // namespace Sstl

// define pop function of heap
namespace Sstl {

template<class RandomAccessIterator, class Distance, class T>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value) {
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2;
    while (secondChild < len) {
        if (*(first + secondChild) < *(first + (secondChild - 1))) --secondChild;
        *(first + holeIndex) = *(first + secondChild);
        holeIndex = secondChild;
        secondChild = 2 * (secondChild - 1);
    }

    if (secondChild == len) {
        *(first + holeIndex) = *(first + (secondChild + 1));
        holeIndex = secondChild - 1;
    }

    __push_heap(first, holeIndex, topIndex, value);
}

template<class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*) {
    *result = *first;
    __adjust_heap(first, distance(0), distance(last - first), value);
}

template<class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
    __pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
}

template<class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
    __pop_heap_aux(first, last, value_type(first));
}

} // namespace Sstl

#endif
