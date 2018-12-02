/**
 * This is a self balancing tree, using the red black interface
 */

#include <stdbool.h>

#define RED   true
#define BLACK false


typedef struct {
    Node *parent;
    Node *r_child;  
    Node *l_child;
    Data *range_data;
    bool rb;
} Node

typedef struct {
    void *addr;
    int *len;
    bool freed;
} Data

/**
 * Add a node to the tree
 */
void add(Node * node);



/**
 * look up a value, can wrap node-lookup?
 */
Data * look_up_data(void * key);


/**
 * look up a node
 */
Node * look_up_node(void *key);


/**
 * key->value lookup
 */
Data * remove(void * key);
