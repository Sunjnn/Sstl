#ifndef __STL_VECTOR_H__
#define __STL_VECTOR_H__

#include "stl_alloc.h"
#include "stl_uninitialized.h"
#include <cstddef>

namespace Sstl {

// implementation of vector
template<class T, class Alloc = alloc>
class vector {
public:
    typedef T           value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;

protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;

    iterator start;
    iterator finish;
    iterator end_of_storage;

    void insert_aux(iterator position, const T &x);
    void deallocate() {
        if (start)
            data_allocator::deallocate(start, end_of_storage - start);
    }

    void fill_initialize(size_type n, const T &value) {
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }

public:
    iterator begin() {return start}
    iterator end() {return finish}
    size_type size() const {return size_type(finish - start);}
    size_type capacity() const {return size_type(end_of_storage - start);}
    bool empty() const {return start == finish;}
    reference operator[](size_type n) {return *(start + n);}

    vector() : start(0), finish(0), end_of_storage(0) {}
    vector(size_type n, const T &value) {fill_initialize(n, value);}
    vector(int n, const T &value) {fill_initialize(n, value);}
    vector(long n, const T &value) {fill_initialize(n, value);}
    explicit vector(size_type n) {fill_initialize(n, T());}

    ~vector() {
        destroy(start, finish);
        deallocate();
    }

    reference front() {return *start;}
    reference back() {return *(finish - 1);}

    void push_back(const T &x) {
        if (finish != end_of_storage) {
            construct(finish, x);
            ++finish;
        }
        else
            insert_aux(finish, x);
    }
    void pop_back() {
        --finish;
        destroy(finish);
    }

    iterator erase(iterator position) {
        if (position + 1 != finish)
            copy(position + 1, finish, position);
        --finish;
        destroy(finish);
        return position;
    }
    iterator erase(iterator first, iterator last) {
        if (last != finish)
            copy(last, finish, first);
        size_type erase_size = size_type(last - first);
        iterator new_finish = finish - erase_size;
        destroy(new_finish, finish);
        finish = new_finish;
        return first;
    }

    void resize(size_type new_size, const T &x) {
        if (new_size < size())
            erase(start + new_size, finish);
        else
            insert(finish, new_size - size(), x);
    }
    void resize(size_type new_size) {resize(new_size, T());}
    void clear() {erase(start, finish);}

protected:
    iterator allocate_and_fill(size_type n, const T &x) {
        iterator result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, x);
        return result;
    }
};

}

#endif
