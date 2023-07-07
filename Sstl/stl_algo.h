#ifndef __STL_ALGO_H__
#define __STL_ALGO_H__

namespace Sstl {

template<class ForwardIterator, class T>
ForwardIterator find(ForwardIterator begin, ForwardIterator end, const T& value) {
    while (begin != end && *begin != value) {
        ++begin;
    }

    return begin;
}

} // namespace Sstl

#endif
