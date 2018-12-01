#include "zen_tree.h"
#include <stdio.h> 
 
#define N 800

void print_tree(RedBlackTree T) {

}
 
int main() {
    RedBlackTree T;
    Position P;
    int i;
    int j = 0;
 
    T = Initialize();
    T = MakeEmpty(T);
 
    for (i = 0; i < N; i++, j = (j + 7) % N)
        T = Insert(j, T);
    printf("Inserts are complete\n");
 
    for (i = 0; i < N; i++)
        if ((P = Find(i, T)) == NULL || Retrieve(P) != i)
            printf("Error at %d\n", i);
 
    printf("Min is %d, Max is %d\n", Retrieve(FindMin(T)),
            Retrieve(FindMax(T)));

    print_tree(T);
 
    return 0;
}
