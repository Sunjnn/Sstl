#ifndef __STL_VECTOR_H__
#define __STL_VECTOR_H__

// my implementation
// <> is default, but I will implement
#include "stl_alloc.h"
#include "stl_uninitialized.h"
#include "max.h"
#include "stl_initializer_list.h"

// gcc implementation
#include <cstddef>
#include <iostream>

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
        // todo: second version allocation return a larger space,
        // but this routine does not use it
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }

public:
    iterator begin() const {return start;}
    iterator end() const {return finish;}
    size_type size() const {return size_type(finish - start);}
    size_type capacity() const {return size_type(end_of_storage - start);}
    bool empty() const {return start == finish;}
    reference operator[](size_type n) const {return *(start + n);}

    vector() : start(0), finish(0), end_of_storage(0) {}
    vector(size_type n, const T &value) {fill_initialize(n, value);}
    vector(int n, const T &value) {fill_initialize(n, value);}
    vector(long n, const T &value) {fill_initialize(n, value);}
    vector(std::initializer_list<T> il) : vector(il.size(), T()) {
        iterator it = start;
        typename std::initializer_list<T>::iterator it_il = il.begin();
        typename std::initializer_list<T>::iterator it_il_end = il.end();
        while (it_il != it_il_end) {
            *it = *it_il;
            ++it;
            ++it_il;
        }
    }
    explicit vector(size_type n) {fill_initialize(n, T());}

    ~vector() {
        destroy(start, finish);
        deallocate();
    }

    reference front() const {return *start;}
    reference back() const {return *(finish - 1);}

    void insert(iterator position, size_type n, const T &x);

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

    void reserve(size_type new_size) {
        if (new_size <= capacity()) return;

        iterator new_start = data_allocator::allocate(new_size);
        iterator new_finish = new_start;
        new_finish = uninitialized_copy(start, finish, new_start);

        destroy(start, finish);
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + new_size;
    }

    void swap(vector &tmp) {
        if (&tmp == this) return;

        iterator tmpIt = start;
        start = tmp.start;
        tmp.start = tmpIt;

        tmpIt = finish;
        finish = tmp.finish;
        tmp.finish = tmpIt;

        tmpIt = end_of_storage;
        end_of_storage = tmp.end_of_storage;
        tmp.finish = tmpIt;
    }

protected:
    iterator allocate_and_fill(size_type n, const T &x) {
        iterator result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, x);
        return result;
    }
};

template<class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T &x) {
    if (finish != end_of_storage) {
        // enough space
        construct(finish, *(finish - 1));
        ++finish;
        T x_copy = x;
        copy_backward(position, finish - 2, finish - 1);
        *position = x_copy;
    }
    else {
        // allocate new space
        const size_type old_size = size();
        const size_type len = old_size != 0 ? 2 * old_size : 1;

        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;
        try {
            new_finish = uninitialized_copy(start, position, new_start);
            construct(new_finish, x);
            ++new_finish;
            new_finish = uninitialized_copy(position, finish, new_finish);
        }
        catch(...) {
            // commit or rollback
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, len);
            throw;
        }

        destroy(start, finish);
        deallocate();

        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}

template<class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T &x) {
    if (n != 0) {
        if (size_type(end_of_storage - finish) >= n) {
            // enough space
            T x_copy = x;
            const size_type elems_after = finish - position;
            iterator old_finish = finish;
            if (elems_after > n) {
                uninitialized_copy(finish - n, finish, finish);
                finish += n;
                copy_backward(position, old_finish - n, finish);
                fill(position, position + n, x_copy);
            }
            else {
                uninitialized_fill_n(finish, n - elems_after, x_copy);
                finish += n - elems_after;
                uninitialized_copy(position, old_finish, finish);
                finish += elems_after;
                fill(position, old_finish, x_copy);
            }
        }
        else {
            // allocate new space
            const size_type old_size = size();
            const size_type len = old_size + max(old_size, n);

            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;
            try {
                new_finish = uninitialized_copy(start, position, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, x);
                new_finish = uninitialized_copy(position, finish, new_finish);
            }
            catch(...) {
                // commit or rollback
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, len);
                throw;
            }
            destroy(start, finish);
            deallocate();
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }
}

template<class T, class Alloc>
std::ostream &operator<<(std::ostream &ostream, const vector<T, Alloc> &_vector) {
    typename vector<T, Alloc>::size_type n = _vector.size();
    if (n == 0) return ostream;

    for (decltype(n) i = 0; i < n - 1; ++i) {
        ostream << _vector[i] << "\n";
    }
    ostream << _vector[n - 1];
    return ostream;
} // std::ostream &operator<<(std::ostream&, vector<T, Alloc>)

template<class Alloc>
std::ostream &operator<<(std::ostream &ostream, const vector<int, Alloc> &_vector) {
    typename vector<int, Alloc>::size_type n = _vector.size();
    if (n == 0) return ostream;

    for (decltype(n) i = 0; i < n - 1; ++i) {
        ostream << _vector[i] << " ";
    }
    ostream << _vector[n - 1];
    return ostream;
} // std::ostream &operator<<(std::ostream&, vector<int, Alloc>)

}

#endif
