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

typedef struct listNode {
    struct listNode * nxt_node;
    Node * payload;
} ListNode;

typedef struct {
    ListNode * frst_node;
    ListNode * lst_node;
    int len;
} NodeList;

// Test funcs:
Node * delete_node(Node *r, void *k);
Node * insert_node(Node *r, Node *n);
NodeList *lookup_range(void *k, int l);



/**
 * Add a Node to the tree
 * returns the pointer to the new root
 */
void insert_data(KeyVals key);

/**
 * Deletes a node, returns the new root
 * Right now, this assumes that the node
 * exists in the tree and will exit the
 * program if not.
 *
 * Checking for the nodes existence should
 * be handled before calling the function
 */
void delete_data(void * key);

/**
 * look up a value
 */
KeyVals look_up(void * key);

/**
 * Look up a range of values
 * used in safe malloc
 */
NodeList * lookup_range(void * key, int len);

/**
 * Changed the freed flag for a node.
 * This with exit if a node is previously freed
 */
void free_data(void * key);

/**
 * Set the root node
 */
void set_root(Node *root);

/**
 * This will split nodes that start before
 * the block and end within it and remove
 * nodes that start within the block
 */
void coalesce(NodeList *list, void *key);

/**
 * Mark the block free without calling
 * free library call
 */
void mark_data_free(void *key);

void set_len(void *key, int len);
#endif
