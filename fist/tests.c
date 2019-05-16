#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "dstring.h"
#include "hashmap.h"

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

static char *test_free_array_dstring() {
    dstring test_val = dcreate("Eml1");
    dstring test_val_2 = dcreate("Eml2");
    dstringa array = dcreatea();
    array = dpush(array, test_val);
    array = dpush(array, test_val_2);
    int freed = dfreea(array);
    mu_assert("dfreea: Free array", freed == array.length);
    return 0;
}

static char *test_indexof_array_dstring() {
    dstring test_val_1 = dcreate("one");
    dstring test_val_2 = dcreate("two");
    dstringa array = dcreatea();
    array = dpush(array, test_val_1);
    array = dpush(array, test_val_2);
    int index = dindexofa(array, test_val_2);
    mu_assert("dindexof: Index correct", index == 1);
    return 0;
}

static char *test_pop_array_dstring() {
    dstring test_val_1 = dcreate("one");
    dstring test_val_2 = dcreate("two");
    dstringa array = dcreatea();
    array = dpush(array, test_val_1);
    array = dpush(array, test_val_2);
    mu_assert("dpop: Last item correct", !strcmp(array.values[1].text, test_val_2.text));
    array = dpop(array);
    mu_assert("dpop: Correct size", array.length == 1);
    return 0;
}

static char *test_remove_array_dstring() {
    dstring test_val_1 = dcreate("one");
    dstring test_val_2 = dcreate("two");
    dstringa array = dcreatea();
    array = dpush(array, test_val_1);
    array = dpush(array, test_val_2);
    mu_assert("dremove: Item exists", dindexofa(array, test_val_1) == 0);
    mu_assert("dremove: Length correct", array.length == 2); 
    array = dremove(array, test_val_1);
    mu_assert("dremove: Item removed", dindexofa(array, test_val_1) == -1);
    mu_assert("dremove: Length changed", array.length == 1);
    return 0;
}

static char *test_set_array_dstring() {
    dstring test_val_1 = dcreate("one");
    dstring test_val_2 = dcreate("two");
    dstring test_replace_val = dcreate("three");
    dstringa array = dcreatea();
    array = dpush(array, test_val_1);
    array = dpush(array, test_val_2);
    array = dset(array, 0, test_replace_val);
    mu_assert("dset: First index reset", !strcmp(array.values[0].text, test_replace_val.text));
    return 0;
}

static char *test_substr_dstring() {
    dstring test_val = dcreate("Hello World!");
    dstring substr = dsubstr(test_val, 6, 10);
    mu_assert("dsubstr: Equals World", !strcmp(substr.text, "World"));
    return 0;
}

static char *test_trim_dstring() {
    dstring test_val = dcreate("\r\n Hello World! \r\n");
    mu_assert("dtrim: Has Spaces", strcmp(test_val.text, "Hello World!"));
    test_val = dtrim(test_val);
    mu_assert("dtrimg: Does not have spaces", !strcmp(test_val.text, "Hello World!"));
    return 0;
}

static char *test_replace_dstring() {
    dstring test_val = dcreate("Hello World!");
    mu_assert("dreplace: Original Correct", !strcmp(test_val.text, "Hello World!"));
    test_val = dreplace(test_val, 'l', '1');
    mu_assert("dreplace: Repalced Correct", !strcmp(test_val.text, "He11o Wor1d!"));
    return 0;
}

static char *test_dsplit_dstring() {
    dstring test_val = dcreate("Hello my name is Frankie");
    dstringa split = dsplit(test_val, ' ');
    mu_assert("dsplit: Length", split.length == 5);
    mu_assert("dsplit: 0", !strcmp(split.values[0].text, "Hello"));
    mu_assert("dsplit: 1", !strcmp(split.values[1].text, "my")); 
    mu_assert("dsplit: 2", !strcmp(split.values[2].text, "name"));
    mu_assert("dsplit: 3", !strcmp(split.values[3].text, "is"));
    mu_assert("dsplit: 4", !strcmp(split.values[4].text, "Frankie"));

    return 0;
}

static char *test_getset_hm() {
    hashmap *hm = hcreate();
    dstring key = dcreate("key");
    dstring key2 = dcreate("key2");
    dstring value = dcreate("value");
    dstring value2 = dcreate("value2");
    hm = hset(hm, key, value);
    dstringa output = hget(hm, key);
    mu_assert("hset+hget: Test basic get", dequals(output.values[0], value));
    hm = hset(hm, key, value2);
    output = hget(hm, key);
    mu_assert("hset+hget: Test new value same key", dequals(output.values[1], value2));
    hm = hset(hm, key2, value);
    output = hget(hm, key2);
    mu_assert("hset+hget: Test new value new key", dequals(output.values[0], value)); 
    hm = hset(hm, key2, value2);
    output = hget(hm, key2);
    mu_assert("hset+hget: Test new value same key", dequals(output.values[1], value2)); 
    return 0;
}

static char *all_tests() {
    mu_run_test(test_getset_hm);
    mu_run_test(test_dsplit_dstring);
    mu_run_test(test_replace_dstring);
    mu_run_test(test_trim_dstring);
    mu_run_test(test_substr_dstring);
    mu_run_test(test_set_array_dstring);
    mu_run_test(test_remove_array_dstring);
    mu_run_test(test_pop_array_dstring);
    mu_run_test(test_indexof_array_dstring);
    mu_run_test(test_free_array_dstring);
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
