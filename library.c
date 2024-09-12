#include "library.h"
#include <stdio.h>
#include <stdlib.h>

mv_vector mv_new() {
    mv_vector v;

    v.data = NULL;

    v.__allocated_size = 0;

    v.__logic_size = 0;

    v.__block_size = 5;

    return v;
}


mv_vector mv_from_array(void *data, const size_t size) {
    mv_vector v = mv_new();
    v.data = (void *)malloc((size + v.__block_size) * sizeof(void *));
    for(size_t i = 0; i < size; i++) {
        v.data[i] = &(data[i]);
    }

    return v;
}


void mv_apply(mv_vector* v);
