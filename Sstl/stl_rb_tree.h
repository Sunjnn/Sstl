#ifndef __STL_RB_TREE_H__
#define __STL_RB_TREE_H__

// my implementation
#include "stl_iterator.h"

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

} // namespace Sstl

#endif
