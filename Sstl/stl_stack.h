#ifndef __STL_STACK_H__
#define __STL_STACK_H__

#include "stl_deque.h"

namespace Sstl {

template <class T, class Sequence = deque<T>>
class stack {
public:
    typedef typename Sequence::value_type       value_type;
    typedef typename Sequence::pointer          pointer;
    typedef typename Sequence::reference        reference;
    typedef typename Sequence::size_type        size_type;
    // typedef typename Sequence::const_reference;
    typedef typename Sequence::difference_type  difference_type;

protected:
    c;

public:
    bool empty() const {return c.empty();}
    size_type size() const {return c.size();}
    reference top() {return c.back();}
    // const_reference top() const {return c.back();}
    void push(const value_type &x) {c.push_back(x);}
    void pop() {c.pop_back();}
}; // class stack

} // namespace Sstl

#endif
