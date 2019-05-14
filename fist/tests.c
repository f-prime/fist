#include <stdio.h>
#include "minunit.h"
#include "dstring.h"
#include <string.h>

int tests_run = 0;

static char *test_empty_dstring() {
    dstring empty = dempty();
    mu_assert("dempty: Length 0", empty.length == 0);
    mu_assert("dempty: Is empty", strlen(empty.text) == 0);
    return 0;
}

static char *test_create_dstring() {
    dstring string = dcreate("Hello World!");
    mu_assert("dcreate: Length Correct", string.length == strlen("Hello World!"));
    mu_assert("dcreate: Equals 'Hello World!'", !strcmp(string.text, "Hello World!"));
    return 0;
}

static char *test_append_dstring() {
    dstring string = dcreate("Hello");
    mu_assert("dappend: Length Correst", string.length == strlen("Hello"));
    mu_assert("dappend: Equals 'Hello'", !strcmp(string.text, "Hello"));
    string = dappend(string, " World!");
    mu_assert("dappend: Append Properly", !strcmp(string.text, "Hello World!"));
    mu_assert("dappend: Length Updated", string.length == strlen("Hello World!"));
    
    dstring empty = dempty();
    empty = dappend(empty, "Empty What?");
    mu_assert("dappend: Empty Append Length", empty.length == strlen("Empty What?"));
    mu_assert("dappend: Empty Append Text", !strcmp("Empty What?", empty.text));
   
    return 0;
}

static char *test_reverse_dstring() {
    dstring string = dcreate("Reverse");
    dstring reversed = dreverse(string);
    mu_assert("dreverse: Reversed", !strcmp(reversed.text, "esreveR"));
    mu_assert("dreverse: Reversed Length", reversed.length == string.length);
    return 0;
}

static char *test_free_dstring() {
    dstring string = dcreate("Create then free it");
    int freed = dfree(string);
    mu_assert("dfree: Test Free", freed == strlen("Create then free it"));
    return 0;
}

static char *test_dappendc_dstring() {
    dstring string = dcreate("Hello");
    string = dappendc(string, '!');
    mu_assert("dappendc: Char added", !strcmp(string.text, "Hello!"));
    mu_assert("dappendc: Length correct", string.length == 6);
    char *other_chars = " How are you?";
    for(int i = 0; i < strlen(other_chars); i++) {
        string = dappendc(string, other_chars[i]);
    }
    mu_assert("dappendc: Other chars added", !strcmp(string.text, "Hello! How are you?"));
    mu_assert("dappendc: Length other chars", string.length == 19);
    return 0;
}

static char *test_count_dstring() {
    char *test_val = "Hello Harry";
    int occurances = 2;
    dstring string = dcreate(test_val);
    mu_assert("dcount: Count Correct", dcount(string, 'H') == occurances);
    return 0;
}

static char *test_indexof_dstring() {
    char *test_val = "Hello World";
    int test_index = 6;
    int test_not_in = -1;
    dstring string = dcreate(test_val);
    int index = dindexof(string, 'W');
    int index2 = dindexof(string, 'z');
    mu_assert("dindexof: Correct Index", index == test_index);
    mu_assert("dindexof: Not in string", index2 == test_not_in);
    return 0;
}

static char *test_create_array_dstring() {
    dstringa array = dcreatea();
    mu_assert("dcreatea: Initialized to zero", array.length == 0);
    return 0;
}

static char *test_push_array_dstring() {
    dstring test_val = dcreate("Test");
    dstring test_val_2 = dcreate("test2");
    dstringa array = dcreatea();
    array = dpush(array, test_val);
    mu_assert("dpush: Pushing first value length", array.length == 1);
    mu_assert("dpush: Pushing first value check val", !strcmp(array.values[0].text, test_val.text));
    array = dpush(array, test_val_2);
    mu_assert("dpush: Pushing second value length", array.length == 2);
    mu_assert("dpush: Pushing second value check val", !strcmp(array.values[1].text, test_val_2.text));

    mu_assert("dpush: Check first and second val", !strcmp(array.values[0].text, test_val.text) && !strcmp(array.values[1].text, test_val_2.text));

    return 0;
}

static char *all_tests() {
    mu_run_test(test_push_array_dstring);
    mu_run_test(test_create_array_dstring);
    mu_run_test(test_indexof_dstring);
    mu_run_test(test_empty_dstring);
    mu_run_test(test_create_dstring);
    mu_run_test(test_append_dstring);
    mu_run_test(test_reverse_dstring);
    mu_run_test(test_dappendc_dstring);
    mu_run_test(test_free_dstring);
    mu_run_test(test_count_dstring);
    return 0;
}

void run_tests() {
    char *result = all_tests();
    if(result != 0) {
        printf("FAILED: %s\n", result);
    } else {
        printf("All %d tests passed\n", tests_run);
    }
}
