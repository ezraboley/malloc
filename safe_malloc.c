#include "safe_malloc.h"

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

}


void *realloc(void *ptr, size_t size) {

}

void memcheck537(void *ptr, size_t size) {

}

