#include <stdlib.h>
#include <stdio.h>
#include "537malloc.h"
#include "rb_tree.h"

void *malloc537(size_t size) {
    if (size == 0) {
        fprintf(stderr, "Allocating memory with size 0 is odd, are you sure?\n"); 
    }
    
    KeyVals range_data;
    range_data.key = malloc(size);
    range_data.len = size;

    NodeList *old_data;
    if ((old_data = lookup_range(range_data.key, range_data.len))->frst_node != NULL) {
        coalesce(old_data, range_data.key);
        insert_data(range_data);      
    } else {
        insert_data(range_data);
    }
}


void free537(void *ptr) {
    mark_data_free(ptr);    
    free(ptr);
}


void *realloc537(void *ptr, size_t size) {
    if (size < 0) {
        fprintf(stderr, "Cannot allocate negative amount of memory\n");
        exit(-1);
    }

    if (NULL == ptr)
        return malloc537(size);
    if (NULL == look_up(ptr).key) {
        fprintf(stderr, "Invalid pointer, data at %p does not exist\n", ptr);
        exit(-1);
    }
    if (0 == size) {
        fprintf(stderr,"Size of realloc is 0\n");
        //FIXME free_data, right? the realloc frees I think
        mark_data_free(ptr);
        // FIXME is this correct behavior? we are mallocing without
        // adding anything to the tree
        return realloc(ptr, size);
    }
    void * ret_ptr = realloc(ptr, size);
    if (ret_ptr == NULL) {
        fprintf(stderr, "Error with stdlib realloc call\n");
        exit(-1);
    }
    if (ptr == ret_ptr) {
        set_len(ptr, (int) size);
        return ret_ptr;
    } else {
        delete_data(ptr); //Used to be free data
        if (NULL != look_up(ret_ptr).key) {
            fprintf(stderr, "Realloc cannot allocate data at a spot that is previously allocated");
            exit(-1);
        }
        KeyVals data = {ret_ptr, size, false};
        insert_data(data);
        return ret_ptr;
    }
}

void memcheck537(void *ptr, size_t size) {
    KeyVals data = look_up(ptr);
    if (NULL == data.key) {
        fprintf(stderr, "Error in memcheck537, memory at %p has not been allocated.\n", ptr);
        exit(-1);
    } else if (((int)size) != data.len) {
        fprintf(stderr, "Error in memcheck537, memory block at %p is not the size %lu.\n",ptr, size);
        exit(-1);
    } else if (data.free) {
        fprintf(stderr, "Error in memcheck537, memory at %p is free\n", ptr);
        exit(-1);
    }
}

