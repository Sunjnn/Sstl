#ifndef __STL_RB_TREE_H__
#define __STL_RB_TREE_H__

// my implementation
#include "stl_iterator.h"
#include "stl_alloc.h"
#include "stl_construct.h"

// gcc implementation
#include <cstddef>

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

} // namespace Sstl

// rb iterator
namespace Sstl {

struct __rb_tree_base_iterator {
    typedef __rb_tree_node_base::base_ptr   base_ptr;
    typedef bidirectional_iterator_tag      iterator_category;
    typedef ptrdiff_t                       difference_type;

    base_ptr node;

    // implement operator++
    void increment() {
        if (node->right) {
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
            if (node->right != y)
                node = y;
        }
    }

    // implement operator--
    void decrement() {
        if (node->color == __rb_tree_red && node->parent->parent == node) {
            node = node->right;
        }
        else if (node->left) {
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
            node = y;
        }
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
    __rb_tree_iterator(const iterator& it) {node=it.node};

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
    link_type get_node() {
        return rb_tree_node_allocator::allocate();
    }
    void put_node(link_type p) {
        rb_tree_node_allocator::deallocate(p);
    }

    link_type create_node(const value_type &x) {
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
        return KeyOfValue(value(x));
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
    typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

private:
    iterator __insert(base_ptr x, base_ptr y, const value_type &v);
    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);
    // initialize a rb tree
    // create header
    void init() {
        header = get_node();
        color(header) = __rb_tree_red;

        root() = 0;
        leftmost = header;
        rightmost = header;
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
    pair<iterator, bool> insert_unique(const Value_type &x);
    // several node can have same key
    iterator insert_equal(const Value_type& x);
}; // class rb_tree

} // namespace Sstl


#endif
