#include <stdbool.h>

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
    int color;
    KeyVals info;
} node;

/**
 * Add a node to the tree
 * returns the pointer to the new root
 */
struct node * insert(node * root, struct node * n)


/**
 * look up a value
 */
Data * look_up(void * key);


/**
 * key->value lookup
 */
Data * remove(void * key);
