#ifndef __STL_RB_TREE_H__
#define __STL_RB_TREE_H__

// my implementation
#include "stl_iterator.h"
#include "stl_alloc.h"
#include "stl_construct.h"

// gcc implementation
#include <cstddef>
#include <map>

// rb tree node
namespace Sstl {

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base {
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base* base_ptr;

    color_type color;
    base_ptr parent;
    base_ptr left;
    base_ptr right;

    static base_ptr minimum(base_ptr x) {
        while (x->left) x = x->left;
        return x;
    }

    static base_ptr maximum(base_ptr x) {
        while (x->right) x = x->right;
        return x;
    }
};

template<class Value>
struct __rb_tree_node : public __rb_tree_node_base {
    typedef __rb_tree_node<Value>* link_type;
    // node value
    Value value_field;
};

// rotate left
// reverse graph of `__rb_tree_rotate_right`
inline void __rb_tree_rotate_left(__rb_tree_node_base *x, __rb_tree_node_base *&root) {
    __rb_tree_node_base *y = x->right;
    x->right = y->left;
    if (y->left != 0)
        y->left->parent = x;
    y->parent = x->parent;

    if (x == root)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

/*
rotate right
parameter `x` is G in the graph below
from
              G
             / \
            P   S
           / \  / \
          X   C D  E
         / \
        A   B
to
               P
            /     \
           X       G
          / \     / \
         A   B   C   S
                    / \
                   D   E
*/
inline void __rb_tree_rotate_right(__rb_tree_node_base *x, __rb_tree_node_base *&root) {
    __rb_tree_node_base *y = x->left;
    x->left = y->right;
    if (y->right != 0)
        y->right->parent = x;
    y->parent = x->parent;

    if (x == root)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

inline void __rb_tree_rebalance(__rb_tree_node_base *x, __rb_tree_node_base *&root) {
    x->color = __rb_tree_red;
    while (x != root && x->parent->color == __rb_tree_red) {
        if (x->parent == x->parent->parent->left) {
            __rb_tree_node_base *y = x->parent->parent->right;
            if (y && y->color == __rb_tree_red) {
            // G is black and its children (P and S) are red
            // change color of G P S
                x->parent->color = __rb_tree_black;
                y->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                x = x->parent->parent;
            }
            else {
            // G is black where its left P is red and its right S is black
            // if x is P's left, rotate right G and change color of G P. Condition 1
            // else rotate left P, rotate right G and change color of G X. Condition 2
                if (x == x->parent->right) {
                    x = x->parent;
                    __rb_tree_rotate_left(x, root);
                }
                x->parent->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                __rb_tree_rotate_right(x->parent->parent, root);
            }
        }
        else { // reverse condition of above branch
            __rb_tree_node_base *y = x->parent->parent->left;
            if (y && y->color == __rb_tree_red) {
                x->parent->color = __rb_tree_black;
                y->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                x = x->parent->parent;
            }
            else {
                if (x == x->parent->left) {
                    x = x->parent;
                    __rb_tree_rotate_right(x, root);
                }
                x->parent->color = __rb_tree_black;
                x->parent->parent->color = __rb_tree_red;
                __rb_tree_rotate_left(x->parent->parent, root);
            }
        }
    } // end while
    root->color = __rb_tree_black;
} // inline void __rb_tree_rebalance(__rb_tree_node_base *x, __rb_tree_node_base *root)

} // namespace Sstl

// rb iterator
namespace Sstl {

// the implementation of iterator need to consider the header of rb tree
struct __rb_tree_base_iterator {
    typedef __rb_tree_node_base::base_ptr   base_ptr;
    typedef bidirectional_iterator_tag      iterator_category;
    typedef ptrdiff_t                       difference_type;

    base_ptr node;

    // implement operator++
    //
    // if node->right exists:
    //      get the most left of node->right
    // else if node == parent->right:
    //      get parent's parent iteratively
    // else if node == parent->left:
    //      node = parent
    //
    // consider node == head, i.e. node == end(), ++node gets most left
    void increment() {
        if (node->right) {
        // node->right exists
            node = node->right;
            while (node->left)
                node = node->left;
        }
        else {
            base_ptr y = node->parent;
            while (node == y->right) {
                node = y;
                y = node->parent;
            }

            // consider a specific condition: there is only one node, so header->right == node
            // after code above, node == header and y == root, so node is what needed
            // otherwise node == y->left
            if (node->right != y)
                node = y;
        }
    }

    // implement operator--
    //
    // if node == header:
    //      --node gets the most right i.e. node->right
    // else if node->left exists:
    //      get the most right of node->left
    // else if node == parent->left:
    //      get parent iteratively
    //
    void decrement() {
        if (node->color == __rb_tree_red && node->parent->parent == node) {
        // node is header
            node = node->right;
        }
        else if (node->left) {
        // node->left exists
            base_ptr y = node->left;
            while (y->right)
                y = y->right;
            node = y;
        }
        else {
            base_ptr y = node->parent;
            while (node == y->left) {
                node = y;
                y = y->parent;
            }

            // node == root && node->left doesn't exist
            // after code above, node is header and it is what needed
            if (node->left != y)
                node = y;
        }
    }

    bool operator==(const __rb_tree_base_iterator &rhv) {
        return node == rhv.node;
    }
    bool operator!=(const __rb_tree_base_iterator &rhv) {
        return node != rhv.node;
    }
}; // struct __rb_tree_base_iterator

template<class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator {
    typedef Value                                                   value_type;
    typedef Ref                                                     reference;
    typedef Ptr                                                     pointer;
    typedef __rb_tree_iterator<Value, Value&, Value*>               iterator;
    typedef __rb_tree_iterator<Value, const Value&, const Value*>   const_iterator;
    typedef __rb_tree_iterator<Value, Ref, Ptr>                     self;
    typedef __rb_tree_node<Value>*                                  link_type;

    __rb_tree_iterator() {}
    __rb_tree_iterator(link_type x) {node = x;}
    __rb_tree_iterator(const iterator& it) {node=it.node;}

    reference operator*() const {return link_type(node)->value_field;}
    pointer operator->() const {return &(operator*());}

    self& operator++() {
        increment();
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        decrement();
        return tmp;
    }

    self& operator--() {
        decrement();
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        decrement();
        return tmp;
    }
}; // struct __rb_tree_iterator

} // namespace Sstl

// rb tree
namespace Sstl {

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rb_tree {
protected:
    typedef void*                               void_pointer;
    typedef __rb_tree_node_base*                base_ptr;
    typedef __rb_tree_node<Value>               rb_tree_node;
    typedef simple_alloc<rb_tree_node, Alloc>   rb_tree_node_allocator;
    typedef __rb_tree_color_type                color_type;

public:
    typedef Key                 Key_type;
    typedef Value               Value_type;
    typedef Value_type*         pointer;
    typedef const Value_type*   const_pointer;
    typedef Value_type&         reference;
    typedef const Value_type&   const_reference;
    typedef rb_tree_node*       link_type;
    typedef size_t              size_type;
    typedef ptrdiff_t           difference_type;

protected:
    // allocate an empty node
    link_type get_node() {
        return rb_tree_node_allocator::allocate();
    }
    // deallocate node
    void put_node(link_type p) {
        rb_tree_node_allocator::deallocate(p);
    }

    // create an node and construct it with x
    link_type create_node(const Value_type &x) {
        link_type tmp = get_node();
        construct(&tmp->value_field, x);
        return tmp;
    }

    link_type clone_node(link_type x) {
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = 0;
        tmp->right = 0;
        return tmp;
    }

    void destroy_node(link_type p) {
        destroy(&p->value_field);
        put_node(p);
    }

protected:
    size_type node_count;
    // rb tree has a header node
    // header->parent point to the root node
    // header->left point to the most left node
    // header->right point to the most right node
    link_type header;
    // key_compare should be a function object
    Compare key_compare;

    // get pointer of root, the most left or the most right through header
    link_type& root() const {return (link_type&)header->parent;}
    link_type& leftmost() const {return (link_type&)header->left;}
    link_type& rightmost() const {return (link_type&)header->right;}

    // get pointer of a node's parent, left or right
    static link_type& parent(link_type x) {
        return (link_type&)x->parent;
    }
    static link_type& left(link_type x) {
        return (link_type&)x->left;
    }
    static link_type& right(link_type x) {
        return (link_type&)x->right;
    }
    // get a node's value, key or color
    static reference value(link_type x) {
        return x->value_field;
    }
    static const Key& key(link_type x) {
        return KeyOfValue()(value(x));
    }
    static color_type& color(link_type x) {
        return (color_type&)x->color;
    }

    // get minimum and maximum given a node
    static link_type minimum(link_type x) {
        return (link_type)__rb_tree_node_base::minimum(x);
    }
    static link_type maximum(link_type x) {
        return (link_type)__rb_tree_node_base::maximum(x);
    }

public:
    // define type of iterator
    typedef __rb_tree_iterator<Value_type, reference, pointer> iterator;
    typedef __rb_tree_iterator<Value_type, const_reference, const_pointer> const_iterator;

private:
    iterator __insert(base_ptr x, base_ptr y, const Value_type &v);
    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);
    // initialize a rb tree
    // create header
    void init() {
        header = get_node();
        color(header) = __rb_tree_red;

        root() = 0;
        leftmost() = header;
        rightmost() = header;
    }

public:
    // default constructor
    rb_tree(const Compare &comp = Compare()) : node_count(0), key_compare(comp) {init();}

    // destructor
    ~rb_tree() {
        clear();
        put_node(header);
    }

    // rb_tree<Key, Value, KeyOfValue, Compare, Alloc>&
    // operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x);
    // template parameters can omit in class
    rb_tree& operator=(const rb_tree &x);

public:
    Compare key_comp() const {return key_compare;}
    iterator begin() {return leftmost();}
    iterator end() {return header;}
    bool empty() const {return node_count == 0;}
    size_type size() const {return node_count;}
    size_type max_size() const {return size_type(-1);}

    // insert a node
    // node is unique in the tree
    std::pair<iterator, bool> insert_unique(const Value_type &x);
    // several node can have same key
    iterator insert_equal(const Value_type& x);

    // range insertion
    template<class InputIterator>
    void insert_unique(InputIterator first, InputIterator last) {
        while (first != last) {
            insert_unique(*first);
        }
    }

    iterator find(const Key_type &k) const;
    size_type count(const Key_type &k) const;
}; // class rb_tree

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value &v) {
    link_type y = header;
    link_type x = root();
    while (x != 0) {
        y = x;
        x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
    }
    return __insert(x, y, v);
}

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
std::pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value &v) {
    link_type y = header;
    link_type x = root();
    bool comp = true;
    while (x != 0) {
        y = x;
        // v is less than x, left
        // otherwise, right
        comp = key_compare(KeyOfValue()(v), key(x));
        x = comp ? left(x) : right(x);
    }

    // y is parent of insert point
    iterator j = iterator(y);
    if (comp) {
        // v < y
        // if y is the most left, insert
        // else test v and y->left
        if (j == begin()) 
            return std::pair<iterator, bool>(__insert(x, y, v), true);
        else
            --j;
    }

    // if decrement(y) < v, insert
    // otherwise, duplicate v
    if (key_compare(key(link_type(j.node)), KeyOfValue()(v)))
        return std::pair<iterator, bool>(__insert(x, y, v), true);

    return std::pair<iterator, bool>(j, false);
}

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__insert(base_ptr x_, base_ptr y_, const Value &v) {
    link_type x = (link_type)x_;
    link_type y = (link_type)y_;
    link_type z;

    if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y))) {
    // v < y
        z = create_node(v);
        left(y) = z;
        if (y == header) {
            root() = z;
            rightmost() = z;
        }
        else if (y == leftmost()) {
            leftmost() = z;
        }
    }
    else {
        z = create_node(v);
        right(y) = z;
        if (y == rightmost()) {
            rightmost() = z;
        }
    }
    parent(z) = y;
    left(z) = 0;
    right(z) = 0;

    __rb_tree_rebalance(z, header->parent);
    ++node_count;
    return iterator(z);
}

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key &k) const {
    link_type y = header;
    link_type x = root();

    while (x != 0) {
        if (!key_compare(key(x), k))
            y = x, x = left(x);
        else
            x = right(x);
    }

    iterator j = iterator(y);
    returrn (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::count(const Key &k) const {
    link_type y = header;
    link_type x = root();

    while (x != 0) {
        if (!key_compare(key(x), k))
            y = x, x = left(x);
        else
            x = right(x);
    }

    iterator j = iterator(y);
    size_t res = 0;
    while (!key_compare(k, key(link_type(j.node))) && !key_compare(key(link_type(j.node)), k)) {
        ++res;
        --j;
    }
    return res;
}

} // namespace Sstl


#endif
