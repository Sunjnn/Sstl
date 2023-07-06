#ifndef __STL_HASH_MULTISET_H__
#define __STL_HASH_MULTISET_H__

#include "stl_alloc.h"
#include "stl_hash_fun.h"
#include "stl_hashtable.h"
#include "stl_pair.h"

#include <functional>

template<class T>
struct identity {
    const T& operator()(const T& x) const {return x;}
};

namespace Sstl {

template<class Value, class HashFcn = hash<Value>, class EqualKey = std::equal_to<Value>, class Alloc = alloc>
class hash_multiset {
private:
    typedef hashtable<Value, Value, HashFcn, identity<Value>, EqualKey, Alloc> ht;
    ht rep;

public:
    typedef typename ht::key_type   key_type;
    typedef typename ht::value_type value_type;
    typedef typename ht::hasher     hasher;
    typedef typename ht::key_equal  key_equal;

    typedef typename ht::size_type          size_type;
    typedef typename ht::difference_type    difference_type;
    typedef typename ht::pointer            pointer;
    typedef typename ht::reference          reference;

    typedef typename ht::iterator iterator;

    hasher hash_funct() {return rep.hash_funct();}
    key_equal key_eq() {return rep.key_eq();}

    hash_multiset() : rep(100, hasher(), key_equal()) {}
    explicit hash_multiset(size_type n) : rep(n, hasher(), key_equal()) {}
    hash_multiset(size_type n, const hasher &hf) : rep(n, hf, key_equal()) {}
    hash_multiset(size_type n, const hasher &hf, const key_equal &eql) : rep(n, hf, eql) {}

    template<class InputIterator>
    hash_multiset(InputIterator f, InputIterator l) : rep(100, hasher(), key_equal()) {rep.insert_unique(f, l);}
    template<class InputIterator>
    hash_multiset(InputIterator f, InputIterator l, size_type n) : rep(n, hasher(), key_equal()) {rep.insert_unique(f, l);}
    template<class InputIterator>
    hash_multiset(InputIterator f, InputIterator l, size_type n, const hasher &hf) : rep(n, hf, key_equal()) {rep.insert_unique(f, l);}
    template<class InputIterator>
    hash_multiset(InputIterator f, InputIterator l, size_type n, const hasher &hf, const key_equal &eql) : rep(n, hf, eql) {rep.insert_unique(f, l);}

    size_type size() {return rep.size();}
    size_type max_size() {return rep.max_size();}
    bool empty() {return rep.empty();}
    void swap(hash_multiset &hs) {rep.swap(hs.rep);}
    friend bool operator==(const hash_multiset&, const hash_multiset&);

    iterator begin() {return rep.begin();}
    iterator end() {return rep.end();}

    iterator insert(const value_type &obj) {return rep.insert_equal(obj);}
    template<class InputIterator>
    void insert(InputIterator f, InputIterator l) {rep.insert_equal(f, l);}
    iterator insert_noresize(const value_type &obj) {
        return rep.insert_equal_noresize(obj);
    }

    iterator find(const key_type &key) {return rep.find(key);}

    size_type count(const key_type &key) {return rep.count(key);}

    pair<iterator, iterator> equal_range(const key_type &key) {
        return rep.equal_range(key);
    }

    size_type erase(const key_type &key) {return rep.erase(key);}
    void erase(iterator it) {return rep.erase(it);}
    void erase(iterator f, iterator l) {return rep.erase(f, l);}
    void clear() {rep.clear();}

    void resize(size_type hint) {rep.resize(hint);}
    size_type bucket_count() {return rep.bucket_count();}
    size_type max_bucket_count() {return rep.max_bucket_count();}
    size_type elems_in_bucket(size_type n) {return rep.elems_in_bucket(n);}
}; // hash_multiset

template<class Value, class HashFcn = hash<Value>, class EqualKey = std::equal_to<Value>, class Alloc = alloc>
inline bool operator==(const hash_multiset<Value, HashFcn, EqualKey, Alloc> &hs1, const hash_multiset<Value, HashFcn, EqualKey, Alloc> &hs2) {
    return hs1.rep == hs2.rep;
}

} // namespace Sstl

#endif
