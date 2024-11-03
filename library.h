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

/// Creates a new empty vec, you should use mv_set_element_size() directly after that
mv_vector mv_new();

/// Should not be used externally, makes sure the memory is correctly allocated for the vec to work properly
mv_vector __mv_block_alloc(mv_vector *vec);

/// Create a new vec from the input array
mv_vector mv_from_array(void *data, size_t num, size_t element_size);

/// Sets the size of the elements that will be stored in the vec, should be set before using it and not changed
mv_vector mv_set_element_size(mv_vector v, size_t element_size);

/// Push input element to the end of the vec
mv_vector mv_push(mv_vector *vec, void *data);

/// Returns the requested element
void *mv_get(mv_vector *vec, size_t index);

/// Pop an elemnt at the end of the vec, returns it
void *mv_pop(mv_vector *vec);

/// Free the vec
void mv_free(mv_vector *vec);

/// Free the vec and put all used bytes to zero
void mv_free_zeroise(mv_vector *vec);

/**
 * @brief Sets how much bytes must be allocated everytime there isn't enough
 * room for the data pushed
 * @param v mv_vector
 * @param block_size The number of bytes reallocated every time it is needed
 * @return The reference to the vector given as parameter, with the __block_size
 * value changed. The address might have changed
 */
mv_vector *mv_set_block_size(mv_vector *v, size_t block_size);

/// returns the lenght of the vec
size_t mv_len(mv_vector *v);

/// Sort the vec with input compar function, see the standard qsort func for more info
void mv_qsort(mv_vector *vec, int compar(const void* a, const void* b));

/// Push input element to the front of the vec
mv_vector mv_push_front(mv_vector *vec, const void* data);

/// Pop the front element from the vec
void *mv_pop_front(mv_vector *vec);

/// Clone input vec and returns it
mv_vector mv_clone(mv_vector vec);

/// Concat b to a and returns a new vec from it, a and b must be freed after if they are not needed anymore
mv_vector mv_concat(mv_vector a, mv_vector b);

/// Concat b to a in place, b should be freed manually if not needed anymore
void mv_concat_to(mv_vector *a, mv_vector b);

#endif // MODULAR_VECTORS_LIBRARY_H