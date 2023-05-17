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

#endif
