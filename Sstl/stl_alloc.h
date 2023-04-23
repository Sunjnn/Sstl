#ifndef __STL_ALLOC_H__
#define __STL_ALLOC_H__

#if 0
#   include <new>
#   define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#   include <iostream>
#   define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1)
#endif


namespace Sstl {
template<class T, class Alloc>
class simple_alloc {
public:
    static T *allocate(size_t n) {return 0 == n? 0 : (T*)Alloc::allocate(n * sizeof(T));}
    static T *allocate(void) {return (T*)Alloc::allocate(sizeof(T));}
    static void deallocate(T *p, size_t n) {if (0 != n) Alloc::deallocate(p, n * sizeof(T));}
    static void deallocate(T *p) {Alloc::deallocate(p, sizeof(T));}
};
}

// first version of allocation
namespace Sstl {

template<int inst>
class __malloc_alloc_template {
private:
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    static void (*__malloc_alloc_oom_handler)();

public:
    static void *allocate(size_t n) {
        void *result = malloc(n);
        if (result == 0) result = oom_malloc(n);
        return result;
    }

    static void deallocate(void *p, size_t) {
        free(p);
    }

    static void *reallocate(void *p, size_t, size_t new_sz) {
        void *result = realloc(p, new_sz);
        if (result == 0) result = oom_realloc(p, new_sz);
        return result;
    }

    static void (*set_malloc_handler(void (*f)()))() {
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return (old);
    }
};

// default no oom handler
template<int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template<int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n) {
    void (*my_malloc_handler)();
    void *result;

    for (;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (my_malloc_handler == 0) {__THROW_BAD_ALLOC;}
        (*my_malloc_handler)();
        result = malloc(n);
        if (result) return result;
    }
}

template<int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
    void (*my_malloc_handler)();
    void *result;

    for (;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (my_malloc_handler == 0) {__THROW_BAD_ALLOC;}
        (*my_malloc_handler)();
        result = realloc(p, n);
        if (result) return result;
    }
}

typedef __malloc_alloc_template<0> malloc_alloc;

}

// second version of allocation
// malloc a large memory, making a memory pool
namespace Sstl {

enum {__ALIGN = 8};
enum {__MAX_BYTES = 128};
enum{__NFREELISTS = __MAX_BYTES / __ALIGN};

template<bool threads, int inst>
class __default_alloc_template {
private:
    static size_t ROUND_UP(size_t bytes) {
        return (((bytes) + __ALIGN - 1) & ~(__ALIGN - 1));
    }

    union obj {
        union obj *free_list_link;
        char client_data[1];
    };

    static obj *volatile free_list[__NFREELISTS];
    static size_t FREELIST_INDEX(size_t bytes) {
        return (((bytes) + __ALIGN - 1) / __ALIGN - 1);
    }

    static void *refill(size_t n);
    static char *chunk_alloc(size_t size, int &nobjs);

    static char *start_free;
    static char *end_free;
    static size_t heap_size;

public:
    static void *allocate(size_t n) {
        obj *volatile *myf_free_list;
        obj *result;

        // larger than 128, use first version of allocation
        if (n > (size_t)__MAX_BYTES) {
            return malloc_alloc::allocate(n);
        }

        myf_free_list = free_list + FREELIST_INDEX(n);
        result = *myf_free_list;

        // no space in free list
        if (result == 0) {
            void *r = refill(ROUND_UP(n));
            return r;
        }

        // enough space in free list
        *myf_free_list = result->free_list_link;
        return result;
    }
    static void deallocate(void *p, size_t n) {
        obj *q = (obj *)p;
        obj *volatile *my_free_list;

        // larger than 128
        if (n > (size_t)__MAX_BYTES) {
            malloc_alloc::deallocate(p, n);
            return;
        }

        // find corresponding list
        my_free_list = free_list + FREELIST_INDEX(n);
        q->free_list_link = *my_free_list;
        *my_free_list = q;
    }
    static void *reallocate(void *p, size_t old_sz, size_t new_sz);
};

template<bool threads, int inst>
char *__default_alloc_template<threads, inst>::start_free = 0;

template<bool threads, int inst>
char *__default_alloc_template<threads, inst>::end_free = 0;

template<bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;

template<bool threads, int inst>
__default_alloc_template<threads, inst>::obj *volatile __default_alloc_template<threads, inst>::free_list[__NFREELISTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// refill list
// n has been rounded up, n is a multiple of 8
template<bool threads, int inst>
void *__default_alloc_template<threads, inst>::refill(size_t n) {
    int nobjs = 20;

    // chunk_alloc() malloc nobjs blocks
    char *chunk = chunk_alloc(n, nobjs);

    obj *volatile *my_free_list;
    obj *result;
    obj *current_obj, *next_obj;
    int i;

    // only get a block, return it to user
    if (nobjs == 1) return chunk;

    // get more block, add them to list
    my_free_list = free_list + FREELIST_INDEX(n);
    // return first block to user
    result = (obj *)chunk;
    // link other blocks
    *my_free_list = next_obj = (obj *)(chunk + n);
    for (int i = 1;; ++i) {
        current_obj = next_obj;
        next_obj = (obj *)((char *)next_obj + n);
        if (nobjs - 1 == i) {
            // last block point ot 0
            current_obj->free_list_link = 0;
            break;
        }
        else {
            current_obj->free_list_link = next_obj;
        }
    }
    return result;
}

// require some block from heap
// n has been rounded up, being a multiple of 8
template<bool threads, int inst>
char *__default_alloc_template<threads, inst>::chunk_alloc(size_t size, int &nobjs) {
    char *result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free;

    if (bytes_left >= total_bytes) {
        // enough size in heap
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else if (bytes_left >= size) {
        // left space is larger than a block
        nobjs = bytes_left / size;
        total_bytes = size * nobjs;
        result = start_free;
        start_free += total_bytes;
        return result;
    }
    else {
        // less space than n

        // add left space to list
        if (bytes_left > 0) {
            obj *volatile *my_free_list = free_list + FREELIST_INDEX(bytes_left);
            ((obj *)start_free)->free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }

        // malloc some space
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        start_free = (char *)malloc(bytes_to_get);

        // malloc no space
        // try to get space from list node above size
        if (start_free == 0) {
            int i;
            // obj *volatile *my_free_list, *p;
            obj *volatile *my_free_list;
            obj *p;
            for (i = size; i <= __MAX_BYTES; i += __ALIGN) {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (p != 0) {
                    *my_free_list = p->free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;
                    return chunk_alloc(size, nobjs);
                }
            }

            // no space from list
            // end_free = 0;
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
        }

        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        return chunk_alloc(size, nobjs);
    }
}

}

namespace Sstl {
#ifdef __USE_MALLOC
typedef malloc_alloc alloc;
#else
typedef __default_alloc_template<0, 0> alloc;
// typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
#endif
}

#endif
