#ifndef __RB__TREE__H__
#define __RB__TREE__H__
#include <stdbool.h>
#define RED 1
#define BLACK 0

/**
 * This is a self balancing tree, using the red black interface
 */
typedef struct {
    void * key;
    int len;
    bool free;
} KeyVals;

typedef struct node {
    struct node * parent;
    struct node * left;
    struct node * right;
    void * key; // ALWAYS SET THIS TO BE = info.key
    int color;
    KeyVals info;
} Node;

/**
 * Add a Node to the tree
 * returns the pointer to the new root
 */
Node * insert_node(Node * root, Node * n);

/**
 * Deletes a node, returns the new root
 * Right now, this assumes that the node
 * exists in the tree and will exit the
 * program if not.
 *
 * Checking for the nodes existence should
 * be handled before calling the function
 */
Node * delete_node( Node * root,  void * key);

/**
 * look up a value
 */
KeyVals * look_up(void * key);

/**
 * Look up a range of values
 * used in safe malloc
 */
KeyVals ** look_up_range(void * key);

/**
 * Changed the freed flag for a node.
 * This with exit if a node is previously freed
 */
void free_data(void * key);

#endif
