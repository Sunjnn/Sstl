#ifndef __STL_HASHTABLE_H__
#define __STL_HASHTABLE_H__

#include "stl_alloc.h"
#include "stl_iterator.h"
#include "stl_vector.h"
#include "stl_pair.h"

#include <cstddef>

namespace Sstl {

static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] = {
    53,         97,             193,        389,        769,
    1543,       3079,           6151,       12289,      24593,
    49157,      98317,          196613,     393241,     786433,
    1572869,    3145739,        6291469,    12582917,   25165843,
    50331653,   100663319,      201326611,  402653189,  805306457,
    1610612741, 3221225473ul,   4294967291ul
};
inline unsigned long __stl_next_prime(unsigned long n) {
    int i = 0;
    while (i < __stl_num_primes && n > __stl_prime_list[i]) {++i;}
    return i == __stl_num_primes ? __stl_prime_list[__stl_num_primes - 1] : __stl_prime_list[i];
}

template<class Value>
struct __hashtable_node {
    __hashtable_node *next;
    Value val;
};

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
class hashtable;

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator {
    typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
    typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
    // typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
    typedef __hashtable_node<Value> node;

    typedef forward_iterator_tag    iterator_category;
    typedef Value                   value_type;
    typedef ptrdiff_t               difference_type;
    typedef size_t                  size_type;
    typedef Value&                  reference;
    typedef Value*                  pointer;

    node *cur;
    hashtable *ht;

    __hashtable_iterator(node *n, hashtable *tab) : cur(n), ht(tab) {}
    __hashtable_iterator() {}
    reference operator*() {return cur->val;}
    pointer operator->() {return &(operator*());}
    iterator &operator++();
    iterator &operator++(int);
    bool operator==(const iterator &it) {return cur == it.cur;}
    bool operator!=(const iterator &it) {return cur != it.cur;}
};

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
__hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>&
__hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++() {
    const node* old = cur;
    cur = cur->next;
    if (!cur) {
        size_type bucket = ht->bkt_num(old->val);
        while (!cur && ++bucket < ht->bucket_count()) {
            cur = ht->buckets[bucket];
        }
    }
    return *this;
}

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
__hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>&
__hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++(int) {
    iterator tmp = *this;
    ++*this;
    return tmp;
}

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc = alloc>
class hashtable {
public:
    typedef HashFcn     hasher;
    typedef EqualKey    key_equal;
    typedef size_t      size_type;
    typedef Key         key_type;
    typedef Value       value_type;
    typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
    friend class __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;

private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;

    typedef __hashtable_node<Value> node;
    typedef simple_alloc<node, Alloc> node_allocator;

    vector<node*, Alloc> buckets;
    size_type num_elements;

public:
    size_type bucket_count() {return buckets.size();}
    size_type max_bucket_count() {
        return __stl_prime_list[__stl_num_primes - 1];
    }

private:
    node* new_node(const value_type &obj) {
        node * n = node_allocator::allocate();
        n->next = 0;
        construct(&n->val, obj);
        return n;
    }

    void delete_node(node *n) {
        destroy(&n->val);
        node_allocator::deallocate(n);
    }

    size_type next_size(size_type n) {return __stl_next_prime(n);}

    void initialize_buckers(size_type n) {
        const size_type n_buckets = next_size(n);
        buckets.reserve(n_buckets);
        buckets.insert(buckets.end(), n_buckets, (node*)0);
        num_elements = 0;
    }

    void resize(size_type num_elements_hint);
    pair<iterator, bool> insert_unique_noresize(const value_type &obj);
    iterator insert_equal_noresize(const value_type &obj);

    size_type bkt_num_key(const key_type &key, size_t n) {
        return hash(key) % n;
    }
    size_type bkt_num_key(const key_type &key) {
        return bkt_num_key(key, bucket_count());
    }

    size_type bkt_num(const value_type &obj, size_t n) {
        return bkt_num_key(get_key(obj), n);
    }
    size_type bkt_num(const value_type &obj) {
        return bkt_num_key(get_key(obj));
    }

public:
    hashtable(size_type n, const HashFcn &hf, const EqualKey &eql) : hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0) {
        initialize_buckers(n);
    }

    iterator begin() {
        for (size_type bucket = 0; bucket < bucket_count(); ++bucket) {
            node *first = buckets[bucket];
            if (first) return iterator(first, this);
        }
    }
    iterator end() {
        return iterator(nullptr, this);
    }

    pair<iterator, bool> insert_unique(const value_type &obj) {
        resize(num_elements + 1);
        return insert_unique_noresize(obj);
    }

    iterator insert_equal(const value_type &obj) {
        resize(num_elements + 1);
        return insert_equal_noresize(obj);
    }

    void copy_from(const hashtable &ht);

    size_type size() {return num_elements;}
    size_type elems_in_bucket(size_type bucket) {
        size_type res = 0;
        node *first = buckets[bucket];
        while (first) {
            ++res;
            first = first->next;
        }
        return res;
    }
    void clear();
}; // class hashtable

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::resize(size_type num_elements_hints) {
    const size_type old_n = bucket_count();
    if (num_elements_hints > old_n) {
        const size_type n = next_size(num_elements_hints);
        if (n > old_n) {
            vector<node*, Alloc> tmp(n, (node*)0);
            for (size_type bucket = 0; bucket < old_n; ++bucket) {
                node *first = buckets[bucket];
                while (first) {
                    size_type new_bucket = bkt_num(first->val, n);
                    buckets[bucket] = first->next;
                    first->next = tmp[new_bucket];
                    tmp[new_bucket] = first;
                    first = buckets[bucket];
                }
            }
            buckets.swap(tmp);
        }
    }
}

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
pair<typename hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator, bool>
hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::insert_unique_noresize(const value_type &obj) {
    const size_type n = bkt_num(obj);
    node *first = buckets[n];

    for (node *cur = first; cur; cur = cur->next) {
        if (equals(get_key(cur->val), get_key(obj))) {
            return pair<iterator, bool>(iterator(cur, this), false);
        }
    }

    node *tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return pair<iterator, bool>(iterator(tmp, this), true);
}

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
typename hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator
hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::insert_equal_noresize(const value_type &obj) {
    const size_type n = bkt_num(obj);
    node *first = buckets[n];

    for (node *cur = first; cur; cur = cur->next) {
        if (equals(get_key(cur->val), get_key(obj))) {
            node *tmp = new_node(obj);
            tmp->next = cur->next;
            cur->next = tmp;
            ++num_elements;
            return iterator(tmp, this);
        }
    }

    node *tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return iterator(tmp, this);
}

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::copy_from(const hashtable &ht) {
    buckets.clear();
    buckets.reserve(ht.bucket_count());
    buckets.inseert(buckets.end(), ht.bucket_count(), (node*)0);

    for (size_type i = 0; i < ht.bucket_count(); ++i) {
        if (const node* cur = ht.buckets[i]) {
            node *copy = new_node(cur->val);
            buckets[i] = copy;

            for (node *next = cur->next; next; cur = next, next = cur->next) {
                copy->next = new_node(next->val);
                copy = copy->next;
            }
        }
    }
    num_elements = ht.num_elements;
}

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::clear() {
    for (size_type i = 0; i < bucket_count(); ++i) {
        node *cur = buckets[i];
        while (!cur) {
            node *next = cur->next;
            delete_node(cur);
            cur = next;
        }
        buckets[i] = 0;
    }
    num_elements = 0;
}

} // namespace Sstl

#endif