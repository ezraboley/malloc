#include "537malloc.h"
#include "rb_tree.h"

void *malloc537(size_t size) {

}


void free537(void *ptr) {
    free_data(ptr);    
}


void *realloc537(void *ptr, size_t size) {
    // TODO should this delete the node?
    // or just free it?
    //
    if (NULL == ptr)
        return malloc537(size);
    if (NULL == look_up(ptr)) {
        fprintf(stderr, "Invalid pointer, data at %p does not exist\n", ptr);
        exit(-1);
    }
    if (0 == size) {
        fprintf(stderr,"Size of realloc is 0\n");
        free537(ptr);
        // FIXME is this correct behavior? we are mallocing without
        // adding anything to the tree
        return malloc(ptr, size);
    }
    // FIXME if there is a size 0 then the node is not deleted. However, it seems
    // that if there is a size greater then 0 the instructions say to delete it
    // What's correct?
    delete_data(ptr);
    // TODO realloc needs to be called
    

}

void memcheck537(void *ptr, size_t size) {

}
