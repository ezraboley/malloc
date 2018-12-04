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

void print_node_list(NodeList *list) {
    ListNode *node = list->frst_node;
    int count = 0;
    while (node != NULL) {
        printf("NODE NUM: %d\n\t KEY: %p, LEN: %i, FREE: %d\n", 
                count++, node->payload->info.key, node->payload->info.len, node->payload->info.free);
        node = node->nxt_node; 
    }
}

void test_2() {
    Node * node1 = malloc(sizeof(Node));
    create_node(node1, 10, 9, 0);
    Node * root = insert_node(NULL, node1);

    Node * node2 = malloc(sizeof(Node));
    create_node(node2, 20, 9, 0);
    root = insert_node(root, node2);

    Node * node3 = malloc(sizeof(Node));
    create_node(node3, 30, 20, 0);
    root = insert_node(root, node3);

    Node * node4 = malloc(sizeof(Node));
    create_node(node4, 40, 9, 0);
    root = insert_node(root, node4);

    Node * node5 = malloc(sizeof(Node));
    create_node(node5, 50, 9, 0);
    root = insert_node(root, node5);

    Node * node6 = malloc(sizeof(Node));
    create_node(node6, 60, 9, 0);
    root = insert_node(root, node6);

    Node * node7 = malloc(sizeof(Node));
    create_node(node7, 70, 9, 0);
    root = insert_node(root, node7);

    Node * node8 = malloc(sizeof(Node));
    create_node(node8, 80, 9, 0);
    root = insert_node(root, node8);

    set_root(root);

    NodeList *list = lookup_range((void *)(long)42, 1);
    printf("done with look_up\n");
    print_node_list(list); 
     

}

void test_1() {
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
    print_tree(root, 1);
    printf("\n");
    root = delete_node(root, (void*) (long) 40);
    print_tree(root, 1);
    printf("\n");
    root = delete_node(root, (void*) (long) 30);
    print_tree(root, 1);
    printf("\n");
    root = delete_node(root, (void*) (long) 20);
    print_tree(root, 1);
    printf("\n");
    root = delete_node(root, (void*) (long) 10);
    root = delete_node(root, (void*) (long) 10);


    print_tree(root, 1);
}

int main() {
    //test_1();
    test_2();
    
    return 0;
}
