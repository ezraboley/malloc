#include <stdio.h>
#include "rb_tree.h"

void print_tree(Node * node, int level) {
    // recursively descend the tree until a leaf is found
    /*
    if (root != NULL && n -> key < root -> key) {
        if (root -> left != LEAF) {
            insert_recurse(root -> left, n);
            return;
        } else
            root -> left = n;
    } else if (root != NULL) {
        if (root -> right != LEAF) {
            insert_recurse(root -> right, n);
            return;
        } else
            root -> right = n;
    }
    */
    printf("LEVEL: %d, node key: %p, len: %d, free: %d, ",
            level, node->info.key, node->info.len, node->info.free);
    if (node->parent != NULL) {
        printf("parent key: %p, ", node->parent->info.key);
    }
    if (node->left != NULL) {
        printf("left key: %p, ", node->left->info.key);
    }
    if (node->right != NULL) {
        printf("right key: %p", node->right->info.key);
    }
    printf("\n");
    if (node->left != NULL)
        print_tree(node->left, level++);
    if (node->right != NULL)
        print_tree(node->right, level++);
}

void create_node(Node * node, int key, int len, int free) {
    node->info.key = (void*) (long) key;
    node->key = &node->info.key; // FIXME THIS SHOULD BE RIGHT I HOPE
    node->info.len = len;
    node->info.free = free;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
}

int main() {

    Node node;
    create_node(&node, 40, 1, 0);

    Node * root = insert_node(NULL, &node);

    Node node1;
    create_node(&node1, 50, 2, 0);

    root = insert_node(root, &node1);


    print_tree(root, 1);

    return 0;
}
