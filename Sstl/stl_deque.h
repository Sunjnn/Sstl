#ifndef __STL_DEQUE_H__
#define __STL_DEQUE_H__

#include "stl_iterator.h"
#include "stl_alloc.h"

namespace Sstl {


// if n is not 0, return n decided by caller
// if n is 0, decided bu sz
//   if sz (type size) < 512, return 512 / sz
//   else return 1
inline size_t __buffer_size(size_t n, size_t sz) {
    return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template<class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
    typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
    typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
    static size_t buffer_size() {return __deque_buf_size(BufSiz, sizeof(T));}

    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef Ptr                         pointer;
    typedef Ref                         reference;
    typedef size_t                      size_type;
    typedef ptrdiff_t                   difference_type;
    typedef T**                         map_pointer;

    typedef __deque_iterator self;

    // point to buffer
    // cur element of this iterator
    T* cur;
    // first element of this buffer
    T* first;
    // last element of this buffer
    T* last;
    // point to map
    map_pointer node;

    // set this iterator to another node
    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first + difference_type(buffer_size());
    }

    reference operator*() const {return *cur};
    pointer operator->() const {return &(operator*());}

    difference_type operator-(const self& x) {
        return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
    }

    // ++iterator
    self &operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }
    // iterator++
    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    // --iterator
    self &operator--() {
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }

    // iterator += n
    self &operator+=(difference_type n) {
        difference_type offset = n + (cur - first);
        if (offset >= 0 && offset < difference_type(buffer_size()))
            // in the same node
            cur += n;
        else {
            // in the different node
            // calculate the right node
            difference_type node_offset = offset > 0 ? offset / difference_type(buffer_size()) : -difference_type((-offset - 1) / buffer_size()) - 1;
            set_node(node + node_offset);
            cur = first + (offset - node_offset * difference_type(buffer_size()));
            return *this;
        }
    }
    // iterator + n
    self operator(difference_type n) const {
        self tmp = *this;
        return tmp += n;
    }
    // iterator -= n
    self &operator-=(difference_type n) {
        return *this += -n;
    }
    // iterator - n
    self operator-(difference_type n) const {
        self tmp = *this;
        return tmp -= n;
    }

    // random access
    // call iterator + n
    reference operator[](difference_type n) const {return *(*this + n);}

    // equal == and not equal !=
    bool operator==(const self &x) const {return cur == x.cur;}
    bool operator!=(const self &x) const {return !(*this == x);}
    // compare <
    bool operator<(const self &x) const {
        return (node == x.node) ? (cur < x.cur) : (node < x.node);
    }
}; // __deque_iterator

template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;

protected:
    // pointer of pointer of T
    typedef pointer* map_pointer;

    // map contain a number of pointer,
    // each of pointer point to a consecutive space containing real element
    // when map is full, `realloc` is needed to find a larger space for map
    map_pointer map;
    size_type map_size;
}; // class deque

} // namespace Sstl


#endif
