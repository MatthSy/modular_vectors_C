#include "tests.h"

#include <stdbool.h>

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

    int *retrieved = (int *) mv_get(&v, 0);

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

    int *retrieved = (int *) mv_get(&v, 0);

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

    int *retrieved = (int *) mv_pop(&v);

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
    if (v1.__allocated_size == 10) {
        part2 = 1;
    }

    if (part1 && part2) {
        printf("Test mv_pop passed.\n");
    } else {
        printf("Test mv_pop failed : ");
        if (!part1)
            printf("Part 1 failed  ");
        if (!part2)
            printf("Part 2 failed  %ld", v1.__allocated_size);
        printf("\n");
    }
    mv_free(&v1);
}

void test_mv_from_array() {
    int arr[] = {1, 2, 3, 4, 5};
    mv_vector v = mv_from_array(arr, 5, sizeof(int));

    int success = 1;
    for (int i = 0; i < 5; i++) {
        int value = *(int *) mv_get(&v, i);
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

int __comparFn(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

void test_mv_qsort() {
    int arr[] = {5, 3, 2, 4, 1};
    mv_vector v = mv_from_array(arr, 5, sizeof(int));
    mv_qsort(&v, __comparFn);

    bool cond = true;
    for (int i = 0; i < 5; i++) {
        if (*(int *) mv_get(&v, i) != i + 1) cond = false;
    }

    if (cond) {
        printf("Test mv_qsort passed.\n");
    } else {
        printf("Test mv_qsort failed : ");
        for (int i = 0; i < 5; i++) {
            printf("Val %d : %d   ", i, *(int *) mv_get(&v, i));
        }
        printf("\n");
    }
}


void test_mv_pushf() {
    int arr[] = {1, 2, 3, 4};
    int val = 5;
    mv_vector v = mv_from_array(arr, 4, sizeof(int));
    mv_push_front(&v, &val);

    int cond = 1;
    if (*(int *) mv_get(&v, 0) != 5) cond = 0;
    for (int i = 1; i < 5; i++) {
        if (*(int *) mv_get(&v, i) != i) cond = 0;
    }
    if (v.__logic_size != 5) cond++;

    if (cond) {
        printf("Test mv_pushf passed.\n");
    } else {
        printf("Test mv_pushf failed\n");
        for (int i = 0; i < 5; i++) {
            printf("Val %d : %d\n", i, *(int *) mv_get(&v, i));
        }
    }
}

void test_mv_popf() {
    int arr[] = {1, 2, 3, 4, 5};
    mv_vector v = mv_from_array(arr, 5, sizeof(int));
    mv_pop_front(&v);

    int cond = 0;
    for (int i = 0; i < 4; i++) {
        if (*(int *) mv_get(&v, i) != i + 2) {
            cond++;
        }
    }
    if (v.__logic_size != 4) cond++;

    if (!cond) {
        printf("Test mv_popf passed.\n");
    } else {
        printf("Test mv_popf failed.\n");
    }
    mv_free(&v);
}

void test_mv_clone() {
    int arr[] = {1, 2, 3, 4, 5};
    mv_vector v = mv_from_array(arr, 5, sizeof(int));
    mv_vector v1 = mv_clone(v);

    int cond = 0;
    for (int i = 0; i < 5; i++) {
        if (*(int *) mv_get(&v, i) != *(int *) mv_get(&v1, i)) cond++;
    }

    if (cond) {
        printf("Test mv_clone failed");
    } else {
        printf("Test mv_clone passed");
    }
    mv_free(&v);
    mv_free(&v1);
}

void test_mv_concat() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};

    mv_vector v1 = mv_from_array(arr1, 5, sizeof(int));
    mv_vector v2 = mv_from_array(arr2, 5, sizeof(int));
    mv_vector result = mv_concat(v1, v2);

    int cond = 0;
    for (int i = 0; i < 10; i++) {
        if (*(int*) mv_get(&result, i) != i+1) cond++;
    }

    if (!cond) {
        printf("Test mv_concat passed.\n");
    } else {
        printf("Test mv_concat failed.\n");
    }
    mv_free(&v1);
    mv_free(&v2);
    mv_free(&result);
}

void test_mv_concat_to() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};

    mv_vector v1 = mv_from_array(arr1, 5, sizeof(int));
    mv_vector v2 = mv_from_array(arr2, 5, sizeof(int));
    mv_concat_to(&v1, v2);

    int cond = 0;
    for (int i = 0; i < 10; i++) {
        if (*(int*) mv_get(&v1, i) != i+1) cond++;
    }
    if (v1.__logic_size != 10) cond++;

    if (!cond) {
        printf("Test mv_concat_to passed.\n");
    } else {
        printf("Test mv_concat_to failed -> %d errors.\n", cond);
        for (int i = 0; i < 10; i++) {
            printf("Val %d : %d\n", i, *(int *) mv_get(&v1, i));
        }
    }
    mv_free(&v1);
    mv_free(&v2);
}
