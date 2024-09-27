#include <stdio.h>
#include "../library.h"
#include "tests.h"

void tests_modular_vectors(void) {

    printf("Testing initialization functions...\n");
    test_mv_new();
    test_mv_from_array();
    test_mv_set_element_size();

    printf("\nTesting data modification functions...\n");
    test_mv_push();
    test_mv_get();
    test_mv_pop();

    printf("\nModular vectors tests finished\n");
}


int main(void) {
    // mv_vector vector = mv_set_element_size(mv_new(), sizeof(double));
    // int val = 104;
    // mv_push(&vector, &val);
    // int valA = 105;
    // mv_push(&vector, &valA);
    // int* val2 = mv_get(&vector, 0);
    // int* val3 = mv_get(&vector, 1);
    // printf("%d\n", *val2);
    // printf("%d\n", *val3);

    // mv_vector vector;
    // int tab[5];
    // for (int i = 0; i < 5; i++) {
    //     tab[i] = i*i;
    // }
    // vector = mv_from_array(tab, 5, sizeof(int));
    // int data = 999000;
    // mv_push(&vector, &data);
    // for (int i = 0; i < 6; i++) {
    // printf("%d, ", * (int*) mv_get(&vector, i));
    // };

    tests_modular_vectors();
    return 0;
}
