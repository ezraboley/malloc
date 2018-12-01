#include <stdio.h>
#include <stdlib.h>

void FatalError(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(-1);
}
