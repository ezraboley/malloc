#include "safe_malloc.h"
#include <stdlib.h>


void *malloc537(size_t size) {
    if (size == 0) {
        fprintf(stderr, "Allocating memory with size 0, are you sure you wanted to do that?\n");
    }
    Data range_data;
    
    range_data.addr = malloc(size);
    Data old_data;
    if ((old_data = look_up_data(range_data.addr)) != NULL) {
        if (old_data->freed) {
            //Reallocate
        } else {
            fprintf("Error allocating memory, malloc used an inuse address\n"
            
        }
    }
}


void free537(void *ptr) {

}


void *realloc(void *ptr, size_t size) {

}

void memcheck537(void *ptr, size_t size) {

}

