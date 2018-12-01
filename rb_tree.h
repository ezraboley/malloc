#include <stdbool.h>

/**
 * This is a self balancing tree, using the red black interface
 */
typedef struct {
    void * key;
    int len;
    bool free;
} KeyVals;

typedef struct {
    struct Node * parent;
    struct Node * left;
    struct Node * right;
    int color;
    KeyVals info;
} Node;

/**
 * Add a Node to the tree
 * returns the pointer to the new root
 */
Node * insert(Node * root, Node * n)


/**
 * look up a value
 */
KeyVals * look_up(void * key);


/**
 * key->value lookup
 */
KeyVals * remove(void * key);
