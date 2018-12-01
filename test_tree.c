#include <stdio.h>
#include "rb_tree.h"

void print_tree(struct node * n, int level) {
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
    printf("LEVEL: %d, node key: %d, len: %d, free: %d, parent key: %d, left key: %d, right key %d\n",
            level, node->info->key, node->info->len, node->info->free, node->parent->info->key,
            node->left->info->key, node->right->info->key);
    if (node->left != NULL)
        print_tree(node->left, level++);
    if (node->right != NULL)
        print_tree(node->right, level++);
}

int main() {

    node root;
    KeyVals rootInfo;
    rootInfo.key = 40;
    rootInfo.len = 1;
    rootInfo.free = 0;
    int color = 0;

    print_tree(&root, 1);

    

    return 0;
}
