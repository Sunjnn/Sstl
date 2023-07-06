#ifndef __STL_HASH_MULTIMAP_H__
#define __STL_HASH_MULTIMAP_H__

#include "stl_hash_fun.h"
#include "stl_alloc.h"
#include "stl_pair.h"
#include "stl_hashtable.h"

#include <functional>

namespace Sstl {

template<class Key, class T, class HashFcn = hash<Key>, class EqualKey = std::equal_to<Key>, class Alloc = alloc>
class hash_multimap {
private:
    typedef hashtable<pair<const Key, T>, Key, HashFcn, select1st<pair<const Key, T>>, EqualKey, Alloc> ht;
    ht rep;

public:
    typedef typename ht::key_type   key_type;
    typedef T                       data_type;
    typedef T                       mapped_type;
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

public:
    hash_multimap() : rep(100, hasher(), key_equal()) {}
    explicit hash_multimap(size_type n) : rep(n, hasher(), key_equal()) {}
    hash_multimap(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
    hash_multimap(size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) {}

    template<class InputIterator>
    hash_multimap(InputIterator f, InputIterator l) : rep(100, hasher(), key_equal()) {rep.insert_unique(f, l);}
    template<class InputIterator>
    hash_multimap(InputIterator f, InputIterator l, size_type n) : rep(n, hasher(), key_equal()) {rep.insert_unique(f, l);}
    template<class InputIterator>
    hash_multimap(InputIterator f, InputIterator l, size_type n, const hasher& hf) : rep(n, hf, key_equal()) {rep.insert_unique(f, l);}
    template<class InputIterator>
    hash_multimap(InputIterator f, InputIterator l, size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) {rep.insert_unique(f, l);}

public:
    size_type size() {return rep.size();}
    size_type max_size() {return rep.max_size();}
    bool empty() {return rep.empty();}
    void swap(hash_multimap& hs) {rep.swap(hs.rep);}
    friend bool operator==(const hash_multimap&, const hash_multimap&);

    iterator begin() {return rep.begin();}
    iterator end() {return rep.end();}

public:
    pair<iterator, bool> insert(const value_type& obj) {
        return rep.insert_equal(obj);
    }
    template<class InputIterator>
    void insert(InputIterator f, InputIterator l) {rep.insert_equal(f, l);}
    iterator insert_noreisze(const value_type& obj) {
        return rep.insert_equal_noresize(obj);
    }

    iterator find(const key_type& key) {return rep.find(key);}

    size_type count(const key_type& key) {return rep.count(key);}

    pair<iterator, iterator> equal_range(const key_type& key) {
        return rep.euqal_range(key);
    }

    size_type erase(const key_type& key) {return rep.erase(key);}
    void erase(iterator it) {rep.erase(it);}
    void erase(iterator f, iterator l) {rep.erase(f, l);}
    void clear() {return rep.clear();}

public:
    void resize(size_type hint) {rep.resize(hint);}
    size_type bucket_count() {return rep.bucket_count();}
    size_type max_bucket_count() {return rep.max_bucket_count();}
    size_type elems_in_bucket(size_type n) {
        return rep.elems_in_bucket(n);
    }
}; // class hash_multimap

template<class Key, class T, class HashFcn = hash<Key>, class EqualKey = std::equal_to<Key>, class Alloc = alloc>
inline bool operator==(hash_multimap<Key, T, HashFcn, EqualKey, Alloc> &hm1,
                       hash_multimap<Key, T, HashFcn, EqualKey, Alloc> &hm2) {
    return hm1.rep == hm2.rep;
}

} // namespace Sstl

#endif
