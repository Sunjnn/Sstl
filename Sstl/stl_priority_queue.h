#ifndef __STL_PRIORITY_QUEUE_H__
#define __STL_PRIORITY_QUEUE_H__

#include "stl_vector.h"
#include "stl_heap.h"

namespace Sstl {

// template<class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type>>
template<class T, class Sequence = vector<T>>
class priority_queue {
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    // typedef typename Sequence::const_reference

protected:
    Sequence c;
    // Compare comp;

public:
    priority_queue() : c() {}
    // explicit priority_queue(const Compare &x)

    template<class InputIterator>
    priority_queue(InputIterator first, InputIterator last) : c(first, last) {make_heap(c.begin(), c.end());}

    bool empty() const {return c.empty();}
    size_type size() const {return c.size();}
    reference top() {return c.front();}
    void push(const value_type &x) {
        c.push_back(x);
        push_heap(c.begin(), c.end());
    }
    void pop() {
        pop_heap(c.begin(), c.end());
        c.pop_back();
    }

}; // class priority_queue

} // namespace Sstl 

#endif
