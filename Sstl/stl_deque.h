#ifndef __STL_DEQUE_H__
#define __STL_DEQUE_H__

#include "stl_iterator.h"
#include "stl_alloc.h"
#include "stl_uninitialized.h"
#include "fill_n.h"
#include "max.h"

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
    size_type buffer_size() const {return __buffer_size(BufSiz, sizeof(T));}

    typedef __deque_iterator<T, T&, T*, BufSiz> iterator;

protected:
    // pointer of pointer of T
    typedef pointer* map_pointer;

    // map contain a number of pointer,
    // each of pointer point to a consecutive space containing real element
    // when map is full, `realloc` is needed to find a larger space for map
    map_pointer map;
    size_type map_size;

    iterator start;     // first element of first buffer
    iterator finish;    // next position of last element of last buffer

    // allocator, one for elements and the other for map
    typedef simple_alloc<value_type, Alloc> data_allocator;
    typedef simple_alloc<pointer, Alloc>    map_allocator;

    inline size_type initial_map_size() {return 8;}
    // allocate element space for a node
    pointer allocate_node() {
        return data_allocator.allocate(buffer_size());
    }
    //deallocate a node
    void deallocate_node(pointer node) {
        data_allocator.deallocate(node);
    }

    void create_map_and_node(size_type num_element);
    void fill_initialize(size_type n, const value_type &value);

    // reallocate new space for map
    // if add_at_front is true, add from front
    // otherwise, add from back
    void reallocate_map(size_type node_to_add, bool add_at_front);
    // not enough empty space at back
    void reserve_map_at_back(size_type nodes_to_add = 1) {
        if (nodes_to_add + 1 > map_size - (finish.node - map))
            reallocate_map(nodes_to_add, false);
    }
    // not enough empty space at front
    void reserve_map_at_front(size_type nodes_to_add = 1) {
        if (nodes_to_add > start.node - map)
            reallocate_map(nodes_to_add, true);
    }

public:
    deque(int n, const value_type &value) : start(), finish(), map(0), map_size(0) {
        fill_initialize(n, value);
    }

    iterator begin() const {return start;}
    iterator end() const {return finish;}

    // implement via iterator
    reference operator[](size_type n) const {
        return start[difference_type(n)];
    }

    // implement via iterator
    reference front() const {return *start;}
    reference back() const {
        iterator tmp = finish;
        --tmp;
        return *tmp;
    }

    size_type size() const {return finish - start;}
    size_type max_size() const {return size_type(map_size * buffer_size());}
    bool empty() const {return finish == start;}

    void push_back_aux(const value_type &t);
    // push an element in the back of deque
    void push_back(const value_type &t) {
        if (finish.cur != finish.last - 1) {
            construct(finish.cur, t);
            ++finish.cur;
        }
        else {
            push_back_aux(t);
        }
    }

    void push_front_aux(const value_type &t);
    // push an element at the front of deque
    void push_front(const value_type &t) {
        if (start.cur != start.first) {
            --start.cur;
            construct(start.cur, t);
        }
        else {
            push_front_aux(t);
        }
    }

    void pop_back_aux();
    // remove an element from the back of deque
    void pop_back() {
        if (finish.cur != finish.first) {
            --finish.cur;
            destroy(finish.cur);
        }
        else
            // finish point to a empty buffer
            pop_back_aux();
    }

}; // class deque

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::fill_initialize(size_type n, const value_type &value) {
    create_map_and_nodes(n);
    map_pointer cur;
    for (cur = start.node; cur < finish.node; ++cur) {
        uninitialized_fill(*cur, *cur + buffer_size(), value);
    }
    uninitialized_fill(finish.first, finish.cur, value);
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::create_map_and_node(size_type num_elements) {
    // number of nodes it needed
    size_type num_nodes = num_elements / buffer_size() + 1;

    // map size and allocate map
    map_size = max(initial_map_size(), num_nodes + 2);
    map = map_allocator::allocate(map_size);

    // start node point to first node of elements
    // fill elements in the middle of deque
    map_pointer nstart = map + (map_size - num_nodes) / 2;
    map_pointer nfinish = nstart + num_nodes - 1;

    map_pointer cur;
    for (cur = nstart; cur <= nfinish; ++cur) {
        *cur = allocate_node();
    }

    // set iterators start and finish
    start.set_node(nstart);
    start.cur = start.first;
    finish.set_node(nfinish);
    finish.cur = finish.first + num_elements % buffer_size();
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_back_aux(const value_type &t) {
    value_type t_copy = t;

    // todo: definee reserve_map_at_back()
    // if map is full
    reserve_map_at_back();

    *(finish.node + 1) = allocate_node();
    try {
        construct(finish.cur, t_copy);
        finish.set_node(finish.node + 1);
        finish.cur = finish.first;
    }
    catch (...) {
        deallocate_node(*(finish.node + 1));
    }
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_front_aux(const value_type &t) {
    value_type t_copy = t;

    reserve_map_at_front();

    *(start.node - 1) = allocate_node();
    try {
        start.set_node(start.node - 1);
        start.cur = start.last - 1;
        construct(start.cur, t_copy);
    }
    catch (...) {
        start.set_node(start.node + 1);
        start.cur = start.first;
        deallocate_node(*(start.node - 1));
        throw;
    }
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front) {
    size_type old_num_nodes = finish.node - start.node + 1;
    size_type new_num_nodes = old_num_nodes + nodes_to_add;

    map_pointer new_nstart;
    if (map_size > 2 * new_num_nodes) {
        new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
        if (new_nstart < start.node)
            copy(start.node, finish.node + 1, new_nstart);
        else
            copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
    }
    else {
        size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;

        // allocate a new map
        map_pointer new_map = map_allocator::allocate(new_map_size);
        new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);

        // copy old map to new map
        copy(start.node, finish.node + 1, new_nstart);
        map_allocator::deallocate(map, map_size);

        // set member to new variable
        map = new_map;
        map_size = new_map_size;
    }

    start.set_node(new_nstart);
    finish.set_node(new_nstart + old_num_nodes - 1);
}

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::pop_back_aux() {
    deallocate_node(finish.first);
    finish.set_node(finish.node - 1);
    finish.cur = finish.last - 1;
    destroy(finish.cur);
}

} // namespace Sstl


#endif
