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
    // The 1.5 here could be made as a setting var in the mv_vector type
  if (vec->__allocated_size == vec->__logic_size || vec->__allocated_size - vec->__logic_size >= 1.5 * vec->__block_size) {
    vec->__allocated_size = vec->__block_size + vec->__logic_size;
    // the alloc'd size in bytes
    size_t new_alloc_b_size = vec->__block_size * vec->__allocated_size;
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
  // equal to : vec->data[vec->__logic_size * vec->__elements_size]
  void *dest = vec->data + (vec->__logic_size * vec->__elements_size);
  vec->__logic_size++;
  memcpy(dest, data, vec->__elements_size);

  return *vec;
}

void *mv_get(mv_vector *vec, size_t index) {
  return vec->data + index * vec->__elements_size;
}

mv_vector mv_from_array(void *data, size_t num, size_t element_size) {
  mv_vector v = mv_set_element_size(mv_new(), element_size);

  int mallocd_size = (num + 5) * element_size;
  v.data = malloc(mallocd_size * sizeof(char));
  if (v.data == NULL) {
    fprintf(stderr, "Failed to allocate memory in mv_from_array\n");
    exit(1);
  }
  
  memcpy(v.data, data, num * element_size);
  v.__logic_size = num;
  v.__allocated_size = mallocd_size;
  __mv_block_alloc(&v);

  return v;
}

void *mv_pop(mv_vector *vec) {
  void *val = mv_get(vec, --(vec->__logic_size));
  __mv_block_alloc(vec);
  return val;
}

void mv_free(mv_vector *vec) { free(vec->data); }

void mv_free_zeroise(mv_vector *vec) {
  char zero = 0;
  for (int i = 0; i < vec->__logic_size * vec->__elements_size; i++) {
    memcpy(&vec->data[i], &zero, 1);
  }
}

void mv_qsort(mv_vector *vec, int compar(const void* a, const void* b)) {
  qsort(vec->data, vec->__logic_size, vec->__elements_size, compar);
}

mv_vector mv_push_front(mv_vector *vec, const void* data) {
  __mv_block_alloc(vec);
  void* source = vec->data;
  void* dest = source + vec->__elements_size;
  size_t bytesSize = vec->__elements_size * vec->__logic_size;

  // memcpy(tmpDest, vec->data, bytesSize);
  memcpy(dest, source, bytesSize);
  // cpy input data to the front of the array
  memcpy(vec->data, data, vec->__elements_size);

  vec->__logic_size++;
  return *vec;
}

void *mv_pop_front(mv_vector *vec) {
  void *val = mv_get(vec, 0);

  void *dest = vec->data, *source = vec->data + vec->__elements_size;
  memcpy(dest, source, vec->__elements_size * --vec->__logic_size);

  *vec = __mv_block_alloc(vec);
  return val;
}

mv_vector mv_clone(mv_vector vec) {
  mv_vector newVec = mv_from_array(vec.data, vec.__logic_size, vec.__elements_size);

  return newVec;
}

mv_vector mv_concat(mv_vector a, mv_vector b) {
  if (a.__elements_size != b.__elements_size) {
    printf("Error in modular vectors mv_concat func, elements size should be the same for a and b\n");
    exit(-1);
  }
  const size_t elemSize = a.__elements_size;
  const size_t numElem = a.__logic_size + b.__logic_size;
  const size_t totalByteSize = numElem * elemSize;
  void* concArr = malloc(totalByteSize);
  if (concArr == NULL) {
    printf("Error in modular vectors mv_concat func, malloc failed\n");
    exit(-1);
  }

  memcpy(concArr, a.data, elemSize * a.__logic_size);
  memcpy(concArr + a.__logic_size * elemSize, b.data, elemSize * b.__logic_size);
  mv_vector vec = mv_from_array(concArr, numElem, elemSize);

  free(concArr);
  return vec;
}

void mv_concat_to(mv_vector *a, mv_vector b) {
    size_t size = a->__logic_size * a->__elements_size;
    a->__logic_size += b.__logic_size;
    __mv_block_alloc(a);

   memcpy(a->data + size, b.data, b.__elements_size * b.__logic_size);
}