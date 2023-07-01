#ifndef __STL_MULTISET_H__
#define __STL_MULTISET_H__

// my implementation
#include "stl_alloc.h"
#include "stl_rb_tree.h"

// gcc implementation
#include <functional>

namespace Sstl {

template<class Key, class Compare = std::less<Key>, class Alloc = alloc>
class multiset {
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
    typedef typename rep_type::difference_type          difference_type;

    // constructors
    multiset() : t(Compare()) {}
    explicit multiset(const Compare &comp) : t(comp) {}

    template<class InputIterator>
    multiset(InputIterator first, InputIterator last) : t(Compare()) {
        t.insert_equal(first, last);
    }

    template<class InputIterator>
    multiset(InputIterator first, InputIterator last, const Compare &comp) : t(comp) {
        t.insert_equal(first, last);
    }

    multiset(const multiset<Key, Compare, Alloc> &x) : t(x.t) {}

    multiset &operator=(const multiset &x) {
        t = x.t;
        return *this;
    }

    key_compare key_comp() {return t.key_comp();}
    value_compare value_comp() {return t.key_comp();}
    iterator begin() {return t.begin();}
    iterator end() {return t.end();}
    bool empty() {return t.empty();}
    size_type size() {return t.size();}
    size_type max_size() {return t.max_size();}
    void swap(multiset &x) {t.swap(x.t);}

    iterator insert(const value_type &x) {
        return t.insert_equal(x);
    }

    iterator insert(iterator position, const value_type &x) {
        typedef typename rep_type::iterator rep_iterator;
        return t.insert_equal((rep_iterator&)position, x);
    }

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        t.insert_equal(first, last);
    }
}; // class multiset

} // namespace Sstl

#endif
