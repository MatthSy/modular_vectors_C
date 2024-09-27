#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mv_vector mv_new() {
    mv_vector v;

    v.data = NULL;

    v.__allocated_size = 0;
    v.__logic_size = 0;
    v.__block_size = 5;
    v.__elements_size = 0;
    return v;
}

mv_vector mv_set_element_size(mv_vector v, size_t element_size) {
    v.__elements_size = element_size;
    return v;
}

mv_vector __mv_block_alloc(mv_vector *vec) {
    if (vec->__allocated_size == 0) {
        size_t alloc_size = vec->__block_size * vec->__elements_size;
        vec->data = malloc(alloc_size * sizeof(char));
        vec->__allocated_size = vec->__block_size;
    }
    if (vec->__allocated_size == vec->__logic_size || vec->__allocated_size - vec->__logic_size >= 1.5 * vec->__block_size) {
        // The 1.5 here could be made as a setting var in the
        // mv_vector type
        vec->__allocated_size = vec->__block_size + vec->__logic_size;
        // _b_size for byte size
        size_t new_alloc_b_size = vec->__block_size * vec->__allocated_size;
        // char** data = &(vec->data);
        // free(vec->data);
        // vec->data = malloc(new_alloc_b_size * sizeof(char));
        vec->data = realloc(vec->data, vec->__allocated_size * vec->__elements_size * sizeof(char));
    }
    if (vec->data == NULL) {
        fprintf(stderr, "Failed to allocate memory for the block allocation\n");
        exit(1);
    }
    return *vec;
}

mv_vector mv_push(mv_vector *vec, void *data) {
    __mv_block_alloc(vec);
    void *dest = vec->data + vec->__logic_size * vec->__elements_size; // equal to : vec->data[vec->__logic_size * vec->__elements_size]
    vec->__logic_size++;
    memcpy(dest, data, vec->__elements_size);

    return *vec;
}

void *mv_get(mv_vector *vec, size_t index) {
    return vec->data + index * vec->__elements_size;
}

mv_vector mv_from_array(void *data, size_t num, size_t element_size) {
    mv_vector v = mv_set_element_size(mv_new(), element_size);
    // TODO : Modif to not use a for loop, just memcpy data into vec
    for (int i = 0; i < num; i++) {
        void *val = &data[i * element_size];
        mv_push(&v, val);
    }

    return v;
}

void *mv_pop(mv_vector *vec) {
    void *val = mv_get(vec, --(vec->__logic_size));
    __mv_block_alloc(vec);
    return val;
}
