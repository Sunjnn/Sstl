#ifndef __STL_LIST_H__
#define __STL_LIST_H__

#include "stl_iterator.h"
#include "stl_alloc.h"
#include "stl_construct.h"

namespace Sstl {

// list node
template<class T>
struct __list_node {
    typedef void *void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

// list iterator
template<class T, class Ref, class Ptr>
struct __list_iterator {
    typedef __list_iterator<T, T&, T*>      iterator;
    typedef __list_iterator<T, Ref, Ptr>    self;

    typedef bidirectional_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef Ptr                         pointer;
    typedef Ref                         reference;
    typedef __list_node<T>*             link_type;
    typedef size_t                      size_type;
    typedef ptrdiff_t                   difference_type;

    link_type node;

    // constructor
    __list_iterator(link_type x) : node(x) {}
    __list_iterator() {}
    __list_iterator(const iterator &x) : node(x.node) {}

    bool operator==(const self &x) const {return node == x.node;}
    bool operator!=(const self &x) const {return node != x.node;}

    // dereference to get node value
    reference operator*() const {return node->data;}

    pointer operator->() const {return &(operator*());}

    // ++iterator
    self &operator++() {
        node = (link_type)(node->next);
        return *this;
    }
    //iterator++
    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    // --iterator
    self &operator--() {
        node = (link_type)(node->prev);
        return *this;
    }
    // iterator--
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }
};

// list
template<class T, class Alloc = alloc>
class list {
protected:
    typedef __list_node<T>                  list_node;
    typedef simple_alloc<list_node, Alloc>  list_node_allocator;

public:
    typedef list_node*                  link_type;

    typedef T                           value_type;
    typedef value_type*                 pointer;
    typedef __list_iterator<T, T&, T*>  iterator;
    typedef T&                          reference;
    typedef size_t                      size_type;
    typedef ptrdiff_t                   difference_type;

protected:
    link_type node;

    // allocate memory for a node
    link_type get_node() {return list_node_allocator::allocate();}
    // deallocate memory
    void put_node(link_type p) {list_node_allocator::deallocate(p);}

    // create a new node and construct data
    link_type create_node(const T &x) {
        link_type p = get_node();
        construct(&p->data, x);
        return p;
    }
    // deconstruct data and deallocate
    void destroy_node(link_type p) {
        destroy(&p->data);
        put_node(p);
    }

    void empty_initialize() {
        node = get_node();
        node->next = node;
        node->prev = node;
    }

    // transfer [first, last) to before position
    void transfer(iterator position, iterator first, iterator last) {
        if (position != last) {
            (*(link_type((*last.node).prev))).next = position.node;
            (*(link_type((*first.node).prev))).next = last.node;
            (*(link_type((*position.node).prev))).next = first.node;
            link_type tmp = link_type((*position.node).prev);
            (*position.node).prev = (*last.node).prev;
            (*last.node).prev = (*first.node).prev;
            (*first.node).prev = tmp;
        }
    }

public:
    list() {empty_initialize();}

    iterator begin() const {return (link_type)(node->next);}
    iterator end() const {return node;}
    bool empty() const {return node->next == node;}
    size_type size() const {
        size_type result = 0;
        // distance(begin(), end(), result);
        result = distance(begin(), end());
        return result;
    }
    reference front() const {return *begin();}
    reference back() const {return *(--end());}

    // insert a node whose value is x at position
    iterator insert(iterator position, const T &x) {
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }

    // push a node at the front of list
    void push_front(const T &x) {insert(begin(), x);}
    // push a data at the end of list
    void push_back(const T &x) {insert(end(), x);}

    // erase a node at position
    iterator erase(iterator position) {
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    // pop a node at front of list
    void pop_front() {erase(begin());}
    // pop a node at end of list
    void pop_back() {
        iterator tmp = end();
        erase(--tmp);
    }

    // clear all node
    void clear() {
        // destroy each node
        link_type cur = (link_type)node->next;
        while (cur != node) {
            link_type tmp = cur;
            cur = (link_type)cur->next;
            destroy_node(tmp);
        }
        node->next = node;
        node->prev = node;
    }

    void remove(const T &value) {
        iterator first = begin();
        iterator last = end();
        while (first != last) {
            iterator next = first;
            ++next;
            if (*first == value) erase(first);
            first = next;
        }
    }

    void unique() {
        iterator first = begin();
        iterator last = end();
        if (first == last) return;
        iterator next = first;
        while (++next != last) {
            if (*first == *next)
                erase(next);
            else
                first = next;
            next = first;
        }
    }

    // space x before position
    void splice(iterator position, list &x) {
        if (!x.empty()) {
            transfer(position, x.begin(), x.end());
        }
    }

    // space i at position
    void splice(iterator position, iterator i) {
        iterator j = i;
        ++j;
        if (position == i || position == j) return;
        transfer(position, i, j);
    }

    // space [first, last) at position
    // position cannot be in [first, last)
    void splice(iterator position, iterator first, iterator last) {
        if (first != last) {
            transfer(position, first, last);
        }
    }

    // merge two lists, they must be sorted
    void merge(list<T, Alloc> &x) {
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = x.begin();
        iterator last2 = x.end();

        while (first1 != last1 && first2 != last2) {
            if (*first2 < *first1) {
                iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            }
            else
                ++first1;

        }
        if (first2 != last2) transfer(last1, first2, last2);
    }

    // reverse list
    void reverse() {
        // size is 0 or 1, return
        if (node->next == node || link_type(node->next)->next == node) return;

        iterator first = begin();
        ++first;
        while (first != end()) {
            iterator old = first;
            ++first;
            transfer(begin(), old, first);
        }
    }

    // list cannot use sort method of algorithm
    void sort() {
        // size is 0 or 1, return
        if (node->next == node || link_type(node->next)->next == node) return;

        list<T, Alloc> carry;
        list<T, Alloc> counter[64];
        int fill = 0;
        while (!empty()) {
            carry.splice(carry.begin(), *this, begin());
            int i = 0;
            while (i < fill && !counter[i].empty()) {
                counter[i].merge(carry);
                carry.swap(counter[i++]);
            }
            carry.swap(counter[i]);
            if (i == fill) ++fill;
        }

        for (int i = 1; i < fill; ++i)
            counter[i].merge(counter[i-1]);
        swap(counter[fill-1]);
    }
};

template<class T, class Alloc>
std::ostream &operator<<(const std::ostream &ostream, const list<T, Alloc> _list) {
    if (_list.empty()) return ostream;

    list<T, Alloc>::iterator it = _list.begin(), end = _list.end();
    --end;
    while (it != end) {
        ostream << *it << endl;
        ++it;
    }
    ostream << *it;
} // std::ostream &operator<<(const std::ostream&, const list<T, Alloc>)

template<class Alloc>
std::ostream &operator<<(const std::ostream &ostream, const list<int, Alloc> _list) {
    if (_list.empty()) return ostream;

    list<T, Alloc>::iterator it = _list.begin(), end = _list.end();
    --end;
    while (it != end) {
        ostream << *it << " ";
        ++it;
    }
    ostream << *it;
} // std::ostream &operator<<(const std::ostream&, const list<int, Alloc>)

}

#endif
