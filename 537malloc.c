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
    return range_data.key;
}


void free537(void *ptr) {
    mark_data_free(ptr);    
    free(ptr);
}


void *realloc537(void *ptr, size_t size) {
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
        mark_data_free(ptr);
        if (NULL != look_up(ret_ptr).key) {
            fprintf(stderr, "Realloc cannot allocate data at a spot that is previously allocated");
            exit(-1);
        }
        KeyVals data = {ret_ptr, size, false};
        insert_data(data);
        return ret_ptr;
    }
}

/**
 * Check to see if the val node is fully inside inclusive
 * the target node
 */
bool fully_inside(void * targ_left, void * targ_right,
        void * val_left, void * val_right) {
    return (targ_left <= val_left) && (targ_right >= val_right);
}

void memcheck537(void *ptr, size_t size) {
    NodeList * list = lookup_range(ptr, (int) size);
    if (list->len != 1) {
        fprintf(stderr, "Error, this size spans %d allocations.\n", list->len);
        exit(-1);
    }
    Node * targ = list->frst_node->nxt_node->payload;
    if ( !fully_inside(targ->info.key, targ->info.key + targ->info.len,
                ptr, ptr + ((int) size)) ) {
        fprintf(stderr, "Pointer with size is not fully within an allocated node\n");
        exit(-1);
    } else if (NULL == targ->info.key) {
        fprintf(stderr, "Error in memcheck537, memory at %p has not been allocated.\n", ptr);
        exit(-1);
    } else if (targ->info.free) {
        fprintf(stderr, "Error in memcheck537, memory at %p is free\n", ptr);
        exit(-1);
    }
}

