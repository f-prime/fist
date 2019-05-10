#include <stdio.h>
#include "minunit.h"
#include "dstring.h"
#include <string.h>

int tests_run = 0;

static char *test_empty_dstring() {
    dstring empty = dempty();
    mu_assert("Length 0", empty.length == 0);
    mu_assert("Is empty", strlen(empty.text) == 0);
    return 0;
}

static char *all_tests() {
    mu_run_test(test_empty_dstring);
    return 0;
}

void run_tests() {
    char *result = all_tests();
    if(result != 0) {
        printf("FAILED: %s\n", result);
    } else {
        printf("All tests passed\n");
    }
}
