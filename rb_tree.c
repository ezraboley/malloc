#include "include/rb_tree.h"

static rb_tree mem_tree;

//We go right then left
Node *get_next_inorder(void *key) {
    Node *node = look_up_node(key);
    Node *child = node->r_child;
    while (child != NULL) {
        child = child->l_child;
    }
    return child;
}

// What is our key?
Data * remove(void *key) {
    Node *node = look_up_node(key);
    if (node->r_child == NULL && node->l_child == NULL) {
        // No Children
        
    
    } else if (node->r_child != NULL && node->l_child != NULL) {
        // Two children
        Node *replacement = get_next_inorder(key);
        
        Node *parent = node->parent;
        // root
        if (parent->r_child == parent->l_child) {
            parent->r_child = replacement;
        } else {
            if (parent->r_child == node) {
                // replace here
                parent->r_child = replacement;
            } else {
                parent->l_child = replacement;
                
            }
        }
    
    } else {
        // One child
        if (node->r_child != NULL) {
            node = node->
        } else {
            
        }
    }

        
}


Data * look_up_data(void *key) {
    Node *node = look_up_node(key);
    return Node->data;
}

