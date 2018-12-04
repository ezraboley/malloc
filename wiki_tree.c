#include "rb_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#define LEFT 1
#define OVERLAP 2
#define RIGHT 3
Node LEAF_NODE = {NULL, NULL, NULL, NULL, BLACK, {NULL, 0, false}};
Node * LEAF = &LEAF_NODE;

static Node * TREE_ROOT = NULL;

void insert_recurse( Node * root, Node * n);
void insert_repair_tree( Node * n);
void delete_case1( Node * n);
void delete_this_node(Node * n);
Node * look_up_node(Node * root, void *key);
void traverse_range(Node *node, NodeList *nodeList, void *key, int len);
Node * find_range_subtree(Node *root, void *key);
Node * insert_node(Node *root, Node *n);
Node * delete_node(Node *root, void *key);
NodeList *lookup_range(void *key, int len);
void set_len(void *key, int len);

// Free the whole list
void free_list(NodeList *list) {
    ListNode *n = list->frst_node;
    ListNode *temp;
    while (n != NULL) {
        temp = n->nxt_node;
        free(n);
        n = temp;
    }
}

void coalesce(NodeList *list, void *key) {
    ListNode *n = list->frst_node;
    
    if (list->frst_node != NULL) {
        n = n->nxt_node;
    } else {
        return;
    }
    bool beforeAll = true;
    ListNode *indNode = NULL;
    while (n != NULL) {
        if (key >= n->payload->info.key) {
            indNode = n;
            beforeAll = false;
            break;
        }
            n = n->nxt_node;
    }   

    if (!beforeAll) {
        set_len(indNode, key - indNode->payload->info.key);
    }   
       
    n = list->frst_node->nxt_node;
    while (n != NULL) {
        if (!n->payload->info.free) {
            fprintf(stderr, "You cant allocate on top of other memory!\n");
            exit(1);
        }
        if (beforeAll || (!beforeAll && n != indNode)) {
            delete_data(n->payload->info.key);
        }
        n = n->nxt_node;
    }
}

void set_root(Node *root) {
    TREE_ROOT = root;
}

NodeList *lookup_range(void *key, int len) {
    // FIXME delete
    printf("key start: %p\n", key);
 
//    Node *subRoot = find_range_subtree(TREE_ROOT, key); // FIXME This is probably unneeded. Results in a duplicate node which makes me think traverse does exactly the same thing. 
//    if (subRoot == NULL) {
//        return NULL;    // Nothing in this range
//    }
    ListNode *head = malloc(sizeof(ListNode));
    //ListNode head = {NULL, subRoot};
    
    head->nxt_node = NULL;
    head->payload = NULL;
    NodeList * list = malloc(sizeof(NodeList));
    list->frst_node = head;
    list->lst_node = head;
    list->len = 0;
    traverse_range(TREE_ROOT, list, key, len); // The meat of the function!
    return list;
}

/**
 * This function will compare the first range 
 * to the second. It will return LEFT, OVERLAP, or RIGHT
 */
int compare_range(void * targ_left, void * targ_right, 
        void * val_left, void * val_right) {
    if (targ_right < val_left)
        return RIGHT;
    else if (targ_left > val_right)
        return LEFT;
    else
        return OVERLAP;
}

void traverse_range(Node *node, NodeList *nodeList, void *key, int len) {
    if (node == NULL) {
        return;
    }

    int direction = compare_range(key, key + len, node->info.key, node->info.key + node->info.len);

    //if ((node->info.key <= key && key <= node->info.key + node->info.len) || (node->info.key <= (key + len) && (key + len) <= (node->info.key + node->info.len))) {
        //ListNode listNode = {NULL, node};
        
    if (direction == OVERLAP) {
        ListNode *listNode = malloc(sizeof(ListNode));
        listNode->nxt_node = NULL;
        listNode->payload = node;
        nodeList->lst_node->nxt_node = listNode;
        nodeList->lst_node = listNode;
        nodeList->len++;
    }
   /* else if (node->info.key <= (key + len) && (key + len) <= (node->info.key + node->info.len)) {
        ListNode *listNode = malloc(sizeof(ListNode));
        listNode->nxt_node = NULL;
        listNode->
    }
*/
    if (direction != LEFT)
        traverse_range(node->left, nodeList, key, len);
    if (direction != RIGHT)
        traverse_range(node->right, nodeList, key, len);
}

KeyVals look_up(void *key) {
    Node * n = look_up_node(TREE_ROOT, key); 
    if (n == NULL) {
        KeyVals keys = {NULL, 0, false};
        return keys;
    }
    else return n->info;
}

void insert_data(KeyVals key_vals) {
    Node *n = malloc(sizeof(Node));
    n->info = key_vals;
    n->color = RED;
    n->key = n->info.key;
    n->info.free = false;
    n->left = n->right = n->parent = NULL;
    TREE_ROOT = insert_node(TREE_ROOT, n);
}

void delete_data(void *key) {
    TREE_ROOT = delete_node(TREE_ROOT, key);
}

/*
Node * find_range_subtree(Node *node, void *key) {
    printf("\trecurse that key: %p\n", key);
    printf("\tTHE TREENODE: %p, THE LEN: %i\n", node->info.key, node->info.len);
    if (node == NULL || (node->info.key + node->info.len) >= key && node->info.key <= key) {
        return node;
    }
    
    if (node->info.key < key) {
        return find_range_subtree(node->left, key);
    }
    
    return find_range_subtree(node->right, key);
}
*/

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

/**
 * This will find the min node of a
 * tree.
 */
Node * find_min(Node * n) {
    if (n->left == LEAF)
        return n;
    return find_min(n->left);
}

void delete_two_child(Node * n) {
    // Take the min value in the right tree
    // and copy it to this node. then, delete
    // the node that the value was copied from
    Node * min_right = find_min(n->right);
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
    else //if (n->left != LEAF || n->right != LEAF)
        delete_one_child(n);
}

/**
 * This will tranverse the tree looking for the correct
 * node. Exits the program if it cannot be found.
 */
Node * look_up_node(Node * root, void * key) {
    if (root == NULL) { 
        return NULL; 
    }

    if( is_leaf(root))
        // node cannot be found
        return NULL;
    if (key == root->key)
        return root;
    else if (key < root->key)
        return look_up_node(root->left, key);
    else
        return look_up_node(root->right, key);
}

void free_node(Node * root, void * key) {
    Node * n = look_up_node(root, key);
    if (NULL == n) {
        fprintf(stderr, "Invalid free, data at %p cannot be found\n", key);
        exit(-1);
    }
    if (n->info.free) {
        fprintf(stderr,"Invalid free, data at %p is already free\n", key);
        exit(-1);
    }
    n->info.free = true;
}

void mark_data_free(void * key) {
    free_node(TREE_ROOT , key);
}

void set_len(void * ptr, int len) {
    Node * n = look_up_node(TREE_ROOT, ptr);
    if (n == NULL) {
        fprintf(stderr, "Error, data at %p does not exist\n", ptr);
        exit(-1);
    }
    n->info.len = len;
}

Node * delete_node( Node * root,  void * key) {
    // if the node has two non leaf children, then copy
    // the min value from the right tree to the node
    // and delete the node which the value was copied from
    // that node must have at most one non leaf child
    // because of the properties of a binary tree
    

    // handle the case where the node deleted is the 
    // root node. This will be an issue cuz you need some
    // way to find the root node
    
    Node * node_to_delete = look_up_node(root, key);

    if (node_to_delete == NULL) {
        fprintf(stderr, "Invalid free, nothing at address %p\n", key);
        exit(-1);
    }
    bool deleted_node_is_root = node_to_delete == root;
    Node * ret_node_base = root;
    if (deleted_node_is_root) {
        if (is_leaf(root->left) && is_leaf(root->right))
            // In this case, the tree is empty
            ret_node_base = NULL;
        else {
            ret_node_base = is_leaf(root->right) ? root->left : root->right;
        }
    }

    delete_this_node(node_to_delete);


    if (ret_node_base != NULL)
        while (parent(ret_node_base) != NULL)
            ret_node_base = parent(ret_node_base);
    return ret_node_base;
}
