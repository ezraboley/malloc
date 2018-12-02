#include "rb_tree.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
// FIXME this is not a const but it should be!! compiler doesn't like it
Node LEAF_NODE;
//FIXME I might need more fields, but probably not
//LEAF_NODE.color = BLACK;
//LEFT_NODE.key = NULL;
// FIXME this only works because black is defined as 0,
// this WILL NOT WORK if balck is defined as something else
Node * LEAF = &LEAF_NODE;

void insert_recurse( Node * root,  Node * n);
void insert_repair_tree( Node * n);
void delete_case1( Node * n);
void delete_this_node(Node * n);

bool is_leaf(Node * n) {
    return n == LEAF;
}

Node * parent( Node * n) {
    return n->parent; // NULL for root Node
}

Node * grandparent( Node * n) {
     Node * p = parent(n);
    if (p == NULL)
        return NULL; // No parent means no grandparent
    return parent(p); // NULL if parent is root
}

Node * sibling( Node * n) {
     Node * p = parent(n);
    if (p == NULL)
        return NULL; // No parent means no sibling
    if (n == p->left)
        return p->right;
    else
        return p->left;
}

Node * uncle( Node * n) {
     Node * p = parent(n);
     Node * g = grandparent(n);
    if (g == NULL)
        return NULL; // No grandparent means no uncle
    return sibling(p);
}

void rotate_left( Node * n) {
     Node * nnew = n->right;
     Node * p = parent(n);
    assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal Nodes
    n->right = nnew->left;
    nnew->left = n;
    n->parent = nnew;
    // handle other child/parent pointers
    if (n->right != NULL)
        n->right->parent = n;
    if (p != NULL) // initially n could be the root
    {
        if (n == p->left)
            p->left = nnew;
        else if (n == p->right) // if (...) is excessive
            p->right = nnew;
    }
    nnew->parent = p;
}

void rotate_right( Node * n) {
     Node * nnew = n->left;
     Node * p = parent(n);
    assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal Nodes
    n->left = nnew->right;
    nnew->right = n;
    n->parent = nnew;
    // handle other child/parent pointers
    if (n->left != NULL)
        n->left->parent = n;
    if (p != NULL) // initially n could be the root
    {
        if (n == p->left)
            p->left = nnew;
        else if (n == p->right) // if (...) is excessive
            p->right = nnew;
    }
    nnew->parent = p;
}

void insert_case1( Node * n) {
    if (parent(n) == NULL)
        n->color = BLACK;
}

void insert_case2( Node * n) {
    return; /* Do nothing since tree is still valid */
}

void insert_case3( Node * n) {
    parent(n)->color = BLACK;
    uncle(n)->color = BLACK;
    grandparent(n)->color = RED;
    insert_repair_tree(grandparent(n));
}

void insert_case4step2( Node * n) {
     Node * p = parent(n);
     Node * g = grandparent(n);

    if (n == p->left)
        rotate_right(g);
    else
        rotate_left(g);
    p->color = BLACK;
    g->color = RED;
}

void insert_case4( Node * n) {
     Node * p = parent(n);
     Node * g = grandparent(n);

    if (n == g->left->right) {
        rotate_left(p);
        n = n->left;
    } else if (n == g->right->left) {
        rotate_right(p);
        n = n->right;
    }

    insert_case4step2(n);
}

Node * insert_node( Node * root,  Node * n) {
    // insert new Node into the current tree
    insert_recurse(root, n);

    // repair the tree in case any of the red-black properties have been violated
    insert_repair_tree(n);

    // find the new root to return
    root = n;
    while (parent(root) != NULL)
        root = parent(root);
    return root;
}

void insert_recurse( Node * root,  Node * n) {
    // recursively descend the tree until a leaf is found
    if (root != NULL && n->key < root->key) {
        if (root->left != LEAF) {
            insert_recurse(root->left, n);
            return;
        } else
            root->left = n;
    } else if (root != NULL) {
        if (root->right != LEAF) {
            insert_recurse(root->right, n);
            return;
        } else
            root->right = n;
    }
    // insert new Node n
    n->parent = root;
    n->left = LEAF;
    n->right = LEAF;
    n->color = RED;
}

void insert_repair_tree( Node * n) {
    if (parent(n) == NULL) {
        insert_case1(n);
    } else if (parent(n)->color == BLACK) {
        insert_case2(n);
    } else if (uncle(n)->color == RED) {
        insert_case3(n);
    } else {
        insert_case4(n);
    }
}

void replace_Node( Node * n,  Node * child) {
    child->parent = n->parent;
    if (n == n->parent->left)
        n->parent->left = child;
    else
        n->parent->right = child;
}

void delete_case6( Node * n) {
     Node * s = sibling(n);

    s->color = n->parent->color;
    n->parent->color = BLACK;

    if (n == n->parent->left) {
        s->right->color = BLACK;
        rotate_left(n->parent);
    } else {
        s->left->color = BLACK;
        rotate_right(n->parent);
    }
}

void delete_case5( Node * n) {
     Node * s = sibling(n);

    if (s->color == BLACK) {
        /* this if statement is trivial,
due to case 2 (even though case 2 changed the sibling to a sibling's child,
the sibling's child can't be red, since no red parent can have a red child). */
        /* the following statements just force the red to be on the left of the left of the parent,
           or right of the right, so case six will rotate correctly. */
        if ((n == n->parent->left) &&
            (s->right->color == BLACK) &&
            (s->left->color == RED)) { /* this last test is trivial too due to cases 2-4. */
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(s);
        } else if ((n == n->parent->right) &&
            (s->left->color == BLACK) &&
            (s->right->color == RED)) { /* this last test is trivial too due to cases 2-4. */
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(s);
        }
    }
    delete_case6(n);
}

void delete_case4( Node * n) {
     Node * s = sibling(n);

    if ((n->parent->color == RED) &&
        (s->color == BLACK) &&
        (s->left->color == BLACK) &&
        (s->right->color == BLACK)) {
        s->color = RED;
        n->parent->color = BLACK;
    } else
        delete_case5(n);
}

void delete_case3( Node * n) {
     Node * s = sibling(n);

    if ((n->parent->color == BLACK) &&
        (s->color == BLACK) &&
        (s->left->color == BLACK) &&
        (s->right->color == BLACK)) {
        s->color = RED;
        delete_case1(n->parent);
    } else
        delete_case4(n);
}

void delete_case2( Node * n) {
     Node * s = sibling(n);

    if (s->color == RED) {
        n->parent->color = RED;
        s->color = BLACK;
        if (n == n->parent->left)
            rotate_left(n->parent);
        else
            rotate_right(n->parent);
    }
    delete_case3(n);
}

void delete_case1( Node * n) {
    if (n->parent != NULL)
        delete_case2(n);
}

void delete_one_child( Node * n) {
    /*
     * Precondition: n has at most one non-leaf child.
     */
     Node * child = is_leaf(n->right) ? n->left : n->right;

    replace_Node(n, child);
    if (n->color == BLACK) {
        if (child->color == RED)
            child->color = BLACK;
        else
            delete_case1(child);
    }
    free(n);
}

void delete_two_child(Node * n) {
    // Take the min value in the right tree
    // and copy it to this node. then, delete
    // the node that the value was copied from
    Node * min_right = find_min_right(n);
    n->info.key = min_right->info.key;
    n->info.len = min_right->info.len;
    n->info.free = min_right->info.free;
    delete_this_node(min_right);
}

/**
 * This will delete a node, handling all
 * conditions for number of non-leaf
 * children
 */
void delete_this_node(Node * n) {
    if (n->left != LEAF && n->right != LEAF)
        delete_two_child(n);
    else if (n->left != LEAF || n->right != LEAF)
        delete_one_child(n);
    else {
        // TODO make the parent forget this child
        // Reset the right or left of the parent to the node
        // to the LEAF
        free(n);
    }
}

Node * delete_node( Node * root,  void * key) {
    // if the node has two non leaf children, then copy
    // the min value from the right tree to the node
    // and delete the node which the value was copied from
    // that node must have at most one non leaf child
    // because of the properties of a binary tree
    

    // TODO handle the case where the node deleted is the 
    // root node. This will be an issue cuz you need some
    // way to find the root node
    
    delete_this_node(node);

    while (parent(root) != NULL)
        root = parent(root);
    return root;
}
