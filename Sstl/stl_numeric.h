#ifndef __STL_NUMERIC_H__
#define __STL_NUMERIC_H__

// accumulate
namespace Sstl {

// frist of two version of accumulate
template<class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init) {
    for (; first != last; ++first)
        init += *first;
    return init;
}

// second of two version of accumulate
template<class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
    for (; first != last; ++first)
        init += binary_op(init, *first);
    return init;
}

} // namespace Sstl

#endif
