#ifndef __537MALLOC__H__
#define __537MALLOC__H__


/////////////////////////////////////////////////
/* The four big functions we HAVE to implement */
/////////////////////////////////////////////////

/**
 *  This function does the standard allocation while also keeping
 *  track of a tuple (addr, len) of that particular piece of memory.
 *  Note: Checks if the size is zero even though that is not an error
 */
void *malloc537(size_t size);


/**
 * This will first do a safety check on the attempted free to see if 
 * the requested free is actually valid. It checks three main things:
 *
 *  1. Memory being freed must be allocated by malloc537
 *  2. Memory being freed must be freed by the address of the first byte
 *  3. Memory being freed must not have been previously freed
 *
 * If the requested free passes these checks, it will perform the free
 * as needed and make a note of it
 */
void free537(void *ptr);


/**
 * When the ptr passed in is NULL, it has the same functionality as malloc537
 * In the case where size is zero and the ptr isnt NULL, it does free537
 * 
 * If neither of those cases are true, it calls realloc and then updates
 * the stored data about that memorys location
 */
void *realloc537(void *ptr, size_t size);


/**
 * This will check if a memory section has already been allocated by malloc537
 * It makes sure that the memory is valid and not yet freed
 */
void memcheck537(void *ptr, size_t size);


#endif
