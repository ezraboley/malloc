#include <stdio.h>
#include <stdlib.h>
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
    if (node->key == NULL)
        return;
    printf("LEVEL: %d, node key: %p, len: %d, free: %d, color: %d, ",
            level, node->info.key, node->info.len, node->info.free, node->color);
    if (node->parent != NULL) {
        printf("parent key: %p, ", node->parent->info.key);
    }
    if (node->left->key != NULL) {
        printf("left key: %p, ", node->left->info.key);
    }
    if (node->right->key != NULL) {
        printf("right key: %p", node->right->info.key);
    }
    printf("\n");
    if (node->left != NULL)
        print_tree(node->left, level + 1);
    if (node->right != NULL)
        print_tree(node->right, level + 1);
}

void create_node(Node * node, int key, int len, int free) {
    node->info.key = (void*) (long) key;
    node->key = node->info.key; // FIXME THIS SHOULD BE RIGHT I HOPE
    node->info.len = len;
    node->info.free = free;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
}

int main() {

    Node * node1 = malloc(sizeof(Node));
    create_node(node1, 10, 1, 0);
    Node * root = insert_node(NULL, node1);

    Node * node2 = malloc(sizeof(Node));
    create_node(node2, 20, 2, 0);
    root = insert_node(root, node2);

    Node * node3 = malloc(sizeof(Node));
    create_node(node3, 30, 3, 0);
    root = insert_node(root, node3);

    Node * node4 = malloc(sizeof(Node));
    create_node(node4, 40, 4, 0);
    root = insert_node(root, node4);

    Node * node5 = malloc(sizeof(Node));
    create_node(node5, 50, 5, 0);
    root = insert_node(root, node5);

    Node * node6 = malloc(sizeof(Node));
    create_node(node6, 60, 6, 0);
    root = insert_node(root, node6);

    Node * node7 = malloc(sizeof(Node));
    create_node(node7, 70, 7, 0);
    root = insert_node(root, node7);

    Node * node8 = malloc(sizeof(Node));
    create_node(node8, 80, 8, 0);
    root = insert_node(root, node8);


    print_tree(root, 1);

    printf("\n\n=========DELETING========\n\n");

    root = delete_node(root, (void*) (long) 50);
    root = delete_node(root, (void*) (long) 40);
    root = delete_node(root, (void*) (long) 30);
    root = delete_node(root, (void*) (long) 20);
    root = delete_node(root, (void*) (long) 10);

    print_tree(root, 1);

    return 0;
}
