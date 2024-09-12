#ifndef MODULAR_VECTORS_LIBRARY_H
#define MODULAR_VECTORS_LIBRARY_H

#include "ctype.h"

typedef struct mv_vector {
    /**
     * @brief The array of the structure, where the actual data is stored\n
     *
     * An array of pointers on void to make it usable for any data type you want.\n
     * You need to cast every time you use the data otherwise it could go wrong
     */
    void **data;

    /**
     * @brief The logic length of the vector aka the number of element
     *
     * You should only access this value by using the mv_len() function.
     */
    size_t __logic_size;

    /**
     * @brief The allocated size of the vector
     *
     * For optimisation reasons, the heap allocated to the vector is not reallocated every time a value
     * is pushed to it; the allocation is made by "blocks", the size of these blocks may be defined with
     * the TODO : mv_set_block_size() method
     */
    size_t __allocated_size;

    size_t __block_size;
} mv_vector;

/**
 * @brief Create a new empty vector
 * @return The new empty vector
 */
mv_vector mv_new();


/**
 * @brief Create a vector using the data provided
 * @param data : An array of data that is cloned into the new vector
 * @param size : The size of the input array in number of elements
 * @return The new vector with the data provided
 */
mv_vector mv_from_array(void *data, size_t size);

/**
 * @brief Sets how much bytes must be allocated everytime there isn't enough already allocated for the data pushed
 * @param v mv_vector
 * @param block_size The number of bytes reallocated every time it is needed
 * @return The reference to the vector given as parameter, with the __block_size value changed
 */
mv_vector* mv_set_block_size(mv_vector *v, size_t block_size);


/**
 * @brief Apply all changes you declared with the set functions
 * @param v mv_vector type
 */
void mv_apply(mv_vector* v);

size_t mv_len(mv_vector *v);


#endif //MODULAR_VECTORS_LIBRARY_H
