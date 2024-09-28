#include "tests.h"
#include "../library.h"
#include <stdio.h>

void test_mv_new() {
  mv_vector v = mv_new();
  if (v.__allocated_size == 0 && v.__logic_size == 0 && v.data == NULL &&
      v.__block_size == 5) {
    printf("Test mv_new passed.\n");
  } else {
    printf("Test mv_new failed.\n");
  }
  mv_free(&v);
}

void test_mv_set_element_size() {
  mv_vector v = mv_new();
  v = mv_set_element_size(v, sizeof(int));

  if (v.__elements_size == sizeof(int)) {
    printf("Test mv_set_element_size passed.\n");
  } else {
    printf("Test mv_set_element_size failed.\n");
  }
  mv_free(&v);
}

void test_mv_push() {
  mv_vector v = mv_set_element_size(mv_new(), sizeof(int));

  int val = 42;
  v = mv_push(&v, &val);

  int *retrieved = (int *)mv_get(&v, 0);

  if (*retrieved == 42 && v.__logic_size == 1) {
    printf("Test mv_push passed.\n");
  } else {
    printf("Test mv_push failed.\n");
  }
  mv_free(&v);
}

void test_mv_get() {
  mv_vector v = mv_set_element_size(mv_new(), sizeof(int));

  int val = 100;
  v = mv_push(&v, &val);

  int *retrieved = (int *)mv_get(&v, 0);

  if (*retrieved == 100) {
    printf("Test mv_get passed.\n");
  } else {
    printf("Test mv_get failed.\n");
  }
  mv_free(&v);
}

void test_mv_pop() {
  mv_vector v = mv_set_element_size(mv_new(), sizeof(int));

  int val = 99;
  v = mv_push(&v, &val);

  int *retrieved = (int *)mv_pop(&v);

  int part1 = 0;
  if (*retrieved == 99 && v.__logic_size == 0)
    part1 = 1;
  mv_free(&v);

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  size_t element_size = sizeof(int);
  mv_vector v1 = mv_from_array(arr, 11, element_size);

  // from 11 to 4 elements in vec :
  mv_pop(&v1);
  mv_pop(&v1);
  mv_pop(&v1);
  mv_pop(&v1);
  mv_pop(&v1);
  mv_pop(&v1);
  mv_pop(&v1);

  int part2 = 0;
  if (v1.__allocated_size == 9) {
    part2 = 1;
  }

  if (part1 && part2) {
    printf("Test mv_pop passed.\n");
  } else {
    printf("Test mv_pop failed : ");
    if (!part1)
      printf("Part 1 failed  ");
    if (!part2)
      printf("Part 2 failed  ");
    printf("\n");
  }
  mv_free(&v1);
}

void test_mv_from_array() {
  int arr[] = {1, 2, 3, 4, 5};
  mv_vector v = mv_from_array(arr, 5, sizeof(int));

  int success = 1;
  for (int i = 0; i < 5; i++) {
    int value = *(int *)mv_get(&v, i);
    if (value != arr[i]) {
      success = 0;
      break;
    }
  }

  if (success) {
    printf("Test mv_from_array passed.\n");
  } else {
    printf("Test mv_from_array failed.\n");
  }
  mv_free(&v);
}
