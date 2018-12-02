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
    void ** key; // ALWAYS SET THIS TO BE = &info.key
    int color;
    KeyVals info;
} Node;

/**
 * Add a Node to the tree
 * returns the pointer to the new root
 */
Node * insert_node(Node * root, Node * n);



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
 * key->value lookup
 */
KeyVals * delete_node(void * key);
