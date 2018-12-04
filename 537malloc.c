#include "537malloc.h"
#include "rb_tree.h"

void *malloc537(size_t size) {
    if (size == 0) {
        fprintf(stderr, "Allocating memory with size 0 is odd, are you sure?\n"); 
    }
    
    KeyVals range_data;
    range_data.key = malloc(size);
    range_data.len = size;

    KeyVals old_data;
    if ((old_data = lookup_data(range_data.key)) != NULL) {
        if (old_data.free) {
            lookup_range();       
        } else {
            fprintf(stderr, "Can't malloc an already in use address\n Quitting...\n");
            exit(1);
        }
    } else {
        insert_data(range_data);
    }
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
        // I THINK WE SHOULD ADD IT
        return malloc(ptr, size);
    }
    // FIXME if there is a size 0 then the node is not deleted. However, it seems
    // that if there is a size greater then 0 the instructions say to delete it
    // What's correct?
    //
    void * ret_ptr = malloc(ptr, size);
    if (ret_ptr == -1) {
    }
    delete_data(ptr);
    // TODO realloc needs to be called
    

}

void memcheck537(void *ptr, size_t size) {
    KeyVals * data = look_up_data(ptr);
    if (NULL == data) {
        fprintf("Error in memcheck537, memory at %p has not been allocated.\n", ptr);
        exit(-1);
    } else if (((int)size) != data->len) {
        fprintf("Error in memcheck537, memory block at %p is not the size %d.\n",ptr, size);
        exit(-1);
    } else if (data->free) {
        fprintf("Error in memcheck537, memory at %p is free\n", ptr);
        exit(-1);
    }
}

