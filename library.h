#ifndef MODULAR_VECTORS_LIBRARY_H
#define MODULAR_VECTORS_LIBRARY_H

#include <stddef.h>

/**
 * TODO : add comments with use case examples
 */
typedef struct mv_vector {
  char *data;

  size_t __logic_size;
  size_t __allocated_size;
  size_t __block_size;
  size_t __elements_size;
} mv_vector;

/**@brief Create a new empty vector
 * @return The new empty vector */
mv_vector mv_new();

mv_vector __mv_block_alloc(mv_vector *vec);

/**@param data An array of data to be loaded in the Vector during initialization
 * @param num Number of element in the 'data' array
 * @param element_size The size of the type in the 'data' array
 * @return A new vector with the input 'data' array in it */
mv_vector mv_from_array(void *data, size_t num, size_t element_size);

mv_vector mv_set_element_size(mv_vector v, size_t element_size);

mv_vector mv_push(mv_vector *vec, void *data);

void *mv_get(mv_vector *vec, size_t index);

void *mv_pop(mv_vector *vec);

void mv_free(mv_vector *vec);

void mv_free_zeroise(mv_vector *vec);
/**
 * @brief Sets how much bytes must be allocated everytime there isn't enough
 * already allocated for the data pushed
 * @param v mv_vector
 * @param block_size The number of bytes reallocated every time it is needed
 * @return The reference to the vector given as parameter, with the __block_size
 * value changed
 */
mv_vector *mv_set_block_size(mv_vector *v, size_t block_size);

size_t mv_len(mv_vector *v);

void mv_qsort(mv_vector *vec, int compar(const void* a, const void* b));

mv_vector mv_pushf(mv_vector *v, void* data);

#endif // MODULAR_VECTORS_LIBRARY_H
