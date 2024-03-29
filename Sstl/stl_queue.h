#ifndef __STL__QUEUE_H__
#define __STL__QUEUE_H__

#include "stl_deque.h"

namespace Sstl {

template<class T, class Sequence = deque<T>>
class queue {
public:
    typedef typename Sequence::value_type   value_type;
    typedef typename Sequence::size_type    size_type;
    typedef typename Sequence::reference    reference;
    // typedef typename Sequence::const_reference;

protected:
    Sequence c;

public:
    bool empty() const {return c.empty();}
    size_type size() const {return c.size();}
    reference front() {return c.front();}
    reference back() {return c.back();}

    void push(const value_type &x) {c.push_back(x);}
    void pop() {c.pop_front();}
}; // class queue

}; // namespace Sstl

#endif
