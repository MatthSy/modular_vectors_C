#include "tests.h"
#include <stdio.h>
#include "../library.h"


void test_mv_new() {
    mv_vector v = mv_new();
    if (v.__allocated_size == 0 && v.__logic_size == 0 && v.data == NULL && v.__block_size == 5) {
        printf("Test mv_new passed.\n");
    } else {
        printf("Test mv_new failed.\n");
    }
}

void test_mv_set_element_size() {
    mv_vector v = mv_new();
    v = mv_set_element_size(v, sizeof(int));

    if (v.__elements_size == sizeof(int)) {
        printf("Test mv_set_element_size passed.\n");
    } else {
        printf("Test mv_set_element_size failed.\n");
    }
}

void test_mv_push() {
    mv_vector v = mv_set_element_size(mv_new(), sizeof(int));

    int val = 42;
    v = mv_push(&v, &val);

    int* retrieved = (int*)mv_get(&v, 0);

    if (*retrieved == 42 && v.__logic_size == 1) {
        printf("Test mv_push passed.\n");
    } else {
        printf("Test mv_push failed.\n");
    }
}

void test_mv_get() {
    mv_vector v = mv_set_element_size(mv_new(), sizeof(int));

    int val = 100;
    v = mv_push(&v, &val);

    int* retrieved = (int*)mv_get(&v, 0);

    if (*retrieved == 100) {
        printf("Test mv_get passed.\n");
    } else {
        printf("Test mv_get failed.\n");
    }
}

void test_mv_from_array() {
    int arr[] = {1, 2, 3, 4, 5};
    size_t element_size = sizeof(int);
    mv_vector v = mv_from_array(arr, 5, element_size);

    int success = 1;
    for (int i = 0; i < 5; i++) {
        int* value = (int*)mv_get(&v, i);
        if (*value != arr[i]) {
            success = 0;
            break;
        }
    }

    if (success) {
        printf("Test mv_from_array passed.\n");
    } else {
        printf("Test mv_from_array failed.\n");
    }
}
