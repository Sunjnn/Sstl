#ifndef __STL_SET_H__
#define __STL_SET_H__

// my implementation
#include "stl_alloc.h"
#include "stl_rb_tree.h"

// gcc implementation
#include <functional>
#include <utility>

namespace Sstl {

template<class Key, class Compare= std::less<Key>, class Alloc = alloc>
class set {
public:
    typedef Key     key_type;
    typedef Key     value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;

private:
    template<class T>
    struct identity {
        const T& operator()(const T& x) const {return x;}
    };
    typedef rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc> rep_type;
    rep_type t;

public:
    // set cannot change value
    typedef typename rep_type::const_pointer    pointer;
    typedef typename rep_type::const_pointer    const_pointer;
    typedef typename rep_type::const_reference  reference;
    typedef typename rep_type::const_reference  const_reference;
    // set cannot write iterator
    typedef typename rep_type::const_iterator           iterator;
    typedef typename rep_type::const_iterator           const_iterator;
    // typedef typename rep_type::const_reverse_iterator   reverse_iterator;
    // typedef typename rep_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename rep_type::size_type                size_type;
    typedef typename rep_type::difference_type          difference_type;

    // constructors
    set() : t(Compare()) {}
    explicit set(const Compare &comp) : t(comp) {}

    template<class InputIterator>
    set(InputIterator first, InputIterator last) : t(Compare()) {t.insert_unique(first, last);}

    template<class InputIterator>
    set(InputIterator first, InputIterator last, const Compare &comp) : t(comp) {
        t.insert_unique(first, last);
    }

    set(const set<Key, Compare, Alloc> &x) : t(x.t) {}

    // copying assignment
    set<Key, Compare, Alloc> &operator=(const set<Key, Compare, Alloc> &x) {
        t = x.t;
        return *this;
    }

    key_compare key_comp() {return t.key_comp();}
    value_compare value_comp() {return t.key_comp();}
    iterator begin() {return t.begin();}
    iterator end() {return t.end();}
    // reverse_iterator rbegin() const {return t.rbegin();}
    // reverse_iterator rend() const {return t.rend();}
    bool empty() {return t.empty();}
    size_type size() {return t.size();}
    size_type max_size() {return t.max_size();}
    void swap(set<Key, Compare, Alloc> &x) {t.swap(x.t);}

    typedef std::pair<iterator, bool> pair_iterator_bool;
    std::pair<iterator, bool> insert(const value_type &x) {
        std::pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
        return std::pair<iterator, bool>(p.first, p.second);
    }
    iterator insert(iterator position, const value_type &x) {
        typedef typename rep_type::iterator rep_iterator;
        return t.insert_unique((rep_iterator&)position, x);
    }
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        t.insert_unique(first, last);
    }
    void erase(iterator position) {
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator&)position);
    }
    size_type erase(const key_type &x) {
        return t.erase(x);
    }
    void erase(iterator first, iterator last) {
        typedef typename rep_type::iterator rep_iterator;
        t.erase((rep_iterator&)first, (rep_iterator&)last);
    }
    void clear() {t.clear();}

    iterator find(const key_type &x) {return t.find(x);}
    size_type count(const key_type &x) {return t.count(x);}
    iterator lower_bound(const key_type &x) {
        return t.lower_bound(x);
    }
    iterator upper_bound(const key_type &x) {
        return t.upper_bound(x);
    }
    std::pair<iterator, iterator> equal_range(const key_type &x) {
        return t.equal_range(x);
    }
    friend bool operator==(const set&, const set&);
    friend bool operator<(const set&, const set&);
}; // class set

template<class Key, class Compare, class Alloc>
inline bool operator==(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y) {
    return x.t == y.t;
}

template<class Key, class Compare, class Alloc>
inline bool operator<(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y) {
    return x.t < y.t;
}

} // namespace Sstl

#endif
