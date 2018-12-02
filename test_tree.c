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

int main() {

    Node root;
    KeyVals rootInfo;
    rootInfo.key = (void*) (long) 40;
    rootInfo.len = 1;
    rootInfo.free = 0;
    int color = 0;
    root.left = root.right = root.parent = NULL;
    root.info = rootInfo;


    print_tree(&root, 1);

    

    return 0;
}
