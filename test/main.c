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
    test_mv_pushf();
    test_mv_get();
    test_mv_pop();
    test_mv_qsort();

    printf("\nModular vectors tests finished\n");
}


int main(void) {
    tests_modular_vectors();
    return 0;
}
