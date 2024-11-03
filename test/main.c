#include <stdio.h>
#include "../library.h"
#include "tests.h"

void tests_modular_vectors(void) {

    printf("\tTesting initialization functions...\n\n");
    test_mv_new();
    test_mv_from_array();
    test_mv_set_element_size();
    test_mv_clone();

    printf("\n\n\n\tTesting data modification functions...\n\n");
    test_mv_push();
    test_mv_pushf();
    test_mv_get();
    test_mv_pop();
    test_mv_popf();
    test_mv_qsort();

    printf("\nModular vectors tests finished");
}


int main(void) {
    tests_modular_vectors();
    return 0;
}
