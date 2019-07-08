#include "bst.h"
#include "dstring.h"
#include "hashmap.h"
#include "indexer.h"
#include "minunit.h"
#include "serializer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run = 0;

static char *test_empty_dstring() {
    dstring empty = dempty();
    mu_assert("dempty: Length 0", empty.length == 0);
    mu_assert("dempty: Is empty", strlen(dtext(empty)) == 0);
    return 0;
}

static char *test_create_dstring() {
    dstring string = dcreate("Hello World!");
    mu_assert("dcreate: Length Correct", string.length == strlen("Hello World!"));
    mu_assert("dcreate: Equals 'Hello World!'", !strcmp(dtext(string), "Hello World!"));
    return 0;
}

static char *test_append_dstring() {
    dstring string = dcreate("Hello");
    mu_assert("dappend: Length Correst", string.length == strlen("Hello"));
    mu_assert("dappend: Equals 'Hello'", !strcmp(dtext(string), "Hello"));
    string = dappend(string, " World!");
    mu_assert("dappend: Append Properly", !strcmp(dtext(string), "Hello World!"));
    mu_assert("dappend: Length Updated", string.length == strlen("Hello World!"));

    dstring empty = dempty();
    empty = dappend(empty, "Empty What?");
    mu_assert("dappend: Empty Append Length", empty.length == strlen("Empty What?"));
    mu_assert("dappend: Empty Append Text", !strcmp("Empty What?", dtext(empty)));

    return 0;
}

static char *test_reverse_dstring() {
    dstring string = dcreate("Reverse");
    dstring reversed = dreverse(string);
    mu_assert("dreverse: Reversed", !strcmp(dtext(reversed), "esreveR"));
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
    mu_assert("dappendc: Char added", !strcmp(dtext(string), "Hello!"));
    mu_assert("dappendc: Length correct", string.length == 6);
    char *other_chars = " How are you?";
    for(int i = 0; i < strlen(other_chars); i++) {
        string = dappendc(string, other_chars[i]);
    }
    mu_assert("dappendc: Other chars added", !strcmp(dtext(string), "Hello! How are you?"));
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
    mu_assert("dpush: Pushing first value check val",
              !strcmp(dtext(array.values[0]), dtext(test_val)));
    array = dpush(array, test_val_2);
    mu_assert("dpush: Pushing second value length", array.length == 2);
    mu_assert("dpush: Pushing second value check val",
              !strcmp(dtext(array.values[1]), dtext(test_val_2)));

    mu_assert("dpush: Check first and second val",
              !strcmp(dtext(array.values[0]), dtext(test_val)) &&
                  !strcmp(dtext(array.values[1]), dtext(test_val_2)));

    dfreea(array);
    dfree(test_val);
    dfree(test_val_2);
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

    dfree(test_val_1);
    dfree(test_val_2);
    dfreea(array);
    return 0;
}

static char *test_pop_array_dstring() {
    dstring test_val_1 = dcreate("one");
    dstring test_val_2 = dcreate("two");
    dstringa array = dcreatea();
    array = dpush(array, test_val_1);
    array = dpush(array, test_val_2);
    mu_assert("dpop: Last item correct", !strcmp(dtext(array.values[1]), dtext(test_val_2)));
    array = dpop(array);
    mu_assert("dpop: Correct size", array.length == 1);

    dfree(test_val_1);
    dfree(test_val_2);
    dfreea(array);
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

    dfree(test_val_1);
    dfree(test_val_2);
    dfreea(array);
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
    mu_assert("dset: First index reset", !strcmp(dtext(array.values[0]), dtext(test_replace_val)));

    dfree(test_val_1);
    dfree(test_val_2);
    dfree(test_replace_val);
    dfreea(array);
    return 0;
}

static char *test_substr_dstring() {
    dstring test_val = dcreate("Hello World!");
    dstring substr = dsubstr(test_val, 6, 10);
    mu_assert("dsubstr: Equals World", !strcmp(dtext(substr), "World"));
    return 0;
}

static char *test_trim_dstring() {
    dstring test_val = dcreate("\r\n Hello World! \r\n");
    mu_assert("dtrim: Has Spaces", strcmp(dtext(test_val), "Hello World!"));
    test_val = dtrim(test_val);
    mu_assert("dtrimg: Does not have spaces", !strcmp(dtext(test_val), "Hello World!"));
    dfree(test_val);
    return 0;
}

static char *test_replace_dstring() {
    dstring test_val = dcreate("Hello World!");
    mu_assert("dreplace: Original Correct", !strcmp(dtext(test_val), "Hello World!"));
    test_val = dreplace(test_val, 'l', '1');
    mu_assert("dreplace: Repalced Correct", !strcmp(dtext(test_val), "He11o Wor1d!"));
    return 0;
}

static char *test_dsplit_dstring() {
    dstring test_val = dcreate("Hello my name is Frankie");
    dstringa split = dsplit(test_val, ' ');
    mu_assert("dsplit: Length", split.length == 5);
    mu_assert("dsplit: 0", !strcmp(dtext(split.values[0]), "Hello"));
    mu_assert("dsplit: 1", !strcmp(dtext(split.values[1]), "my"));
    mu_assert("dsplit: 2", !strcmp(dtext(split.values[2]), "name"));
    mu_assert("dsplit: 3", !strcmp(dtext(split.values[3]), "is"));
    mu_assert("dsplit: 4", !strcmp(dtext(split.values[4]), "Frankie"));

    dfreea(split);
    dfree(test_val);

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
    dfree(value);
    dfree(value2);
    hfree(hm);
    return 0;
}

static char *test_indexer() {
    dstring test = dcreate("This is very cool");
    dstringa answers = dcreatea();
    answers = dpush(answers, dcreate("This"));
    answers = dpush(answers, dcreate("is"));
    answers = dpush(answers, dcreate("very"));
    answers = dpush(answers, dcreate("cool"));
    answers = dpush(answers, dcreate("This is"));
    answers = dpush(answers, dcreate("is very"));
    answers = dpush(answers, dcreate("very cool"));
    answers = dpush(answers, dcreate("This is very"));
    answers = dpush(answers, dcreate("is very cool"));
    answers = dpush(answers, dcreate("This is very cool"));

    dstringa index = indexer(test, 10);

    answers = dsorta(answers);
    index = dsorta(index);

    for(int i = 0; i < answers.length; i++) {
        int found = 0;
        for(int j = 0; j < index.length; j++) {
            if(dequals(answers.values[i], index.values[j])) {
                found = 1;
                break;
            }
        }

        char *buffer = malloc(sizeof(char) * 1024);
        sprintf(buffer, "%s not in index", dtext(answers.values[i]));
        mu_assert(buffer, found);
        free(buffer);
    }
    dfreea(answers);
    dfreea(index);
    return 0;
}

static char *test_drange_dstring() {
    dstringa test = dcreatea();
    test = dpush(test, dcreate("Hello"));
    test = dpush(test, dcreate("this"));
    test = dpush(test, dcreate("is"));
    test = dpush(test, dcreate("really"));
    test = dpush(test, dcreate("cool"));

    dstringa test1 = drange(test, 2, 4);
    mu_assert("drange: Basic 1", dequals(test1.values[0], dcreate("is")));
    mu_assert("drange: Basic 2", dequals(test1.values[1], dcreate("really")));
    mu_assert("drange: Basic 3", dequals(test1.values[2], dcreate("cool")));

    dstringa test2 = drange(test, -1, 100);

    mu_assert("drange: Bad ranges 1", dequals(test2.values[0], dcreate("Hello")));
    mu_assert("drange: Bad ranges 2", dequals(test2.values[4], dcreate("cool")));

    dstringa test3 = drange(test, 100, -1);

    mu_assert("drange: Bad ranges 3", dequals(test3.values[0], dcreate("Hello")));
    mu_assert("drange: Bad ranges 4", dequals(test3.values[4], dcreate("cool")));

    dstringa test4 = drange(test, 0, 0);

    mu_assert("drange: Same start and end", dequals(test4.values[0], dcreate("Hello")));

    dfreea(test);
    dfreea(test1);
    dfreea(test2);
    dfreea(test3);
    dfreea(test4);

    return 0;
}

static char *test_djoin_dstring() {
    dstringa test = dcreatea();
    test = dpush(test, dcreate("Hello"));
    test = dpush(test, dcreate("this"));
    test = dpush(test, dcreate("is"));
    test = dpush(test, dcreate("really"));
    test = dpush(test, dcreate("cool"));

    dstring answer = dcreate("Hello,this,is,really,cool");
    dstring joined = djoin(test, ',');
    mu_assert("djoin", dequals(answer, joined));

    dfreea(test);
    dfree(answer);
    dfree(joined);

    return 0;
}

static char *test_dappendd_dstring() {
    dstring text = dcreate("Hello");
    dstring append = dcreate(" World");
    text = dappendd(text, append);
    mu_assert("dappendd", dequals(text, dcreate("Hello World")));
    dfree(text);
    dfree(append);
    return 0;
}

static char *test_serialize_hmap() {
    rename("fist.db", "fist.db.real");
    hashmap *hm = hcreate();
    dstring key = dcreate("index");
    dstring key2 = dcreate("index2");
    dstring value = dcreate("d1");
    dstring value2 = dcreate("d2");
    dstring value3 = dcreate("d3");
    hm = hset(hm, key, value);
    hm = hset(hm, key, value2);
    hm = hset(hm, key2, value3);
    sdump(hm);
    hashmap *loaded = sload();
    dstringa get_from_loaded = hget(loaded, key2);
    dstringa key1vals = hget(loaded, key);
    mu_assert("Serialized data size", get_from_loaded.length == 1);
    mu_assert("key2 == value3", dequals(get_from_loaded.values[0], value3));
    mu_assert("key1 contains value", dequals(key1vals.values[0], value));
    mu_assert("key2 contains value2", dequals(key1vals.values[1], value2));
    rename("fist.db.real", "fist.db");
    hfree(hm);
    dfree(value);
    dfree(value2);
    dfree(value3);
    hfree(loaded);
    return 0;
}

static char *test_create_bst() {
    struct bst_node *root = bst_create("Hello", NULL);
    mu_assert("bst_create: Equals 'Hello'", !strcmp(root->key, "Hello"));
    bst_free(root);
    return 0;
}

static char *test_insert_and_search_bst() {
    struct bst_node *root = bst_create("Hello World", NULL);
    bst_insert(&root, "BSTn", NULL);
    mu_assert("bst_search: Equals 'NULL'", bst_search(root, "BSTn") == NULL);
    int a = 2;
    bst_insert(&root, "nodeb", &a);
    mu_assert("bst_search: Equals address of a", bst_search(root, "nodeb") == &a);
    char *str = "abc";
    bst_insert(&root, "33333", str);
    mu_assert("bst_search: Equals 'abc'", bst_search(root, "33333") == str);
    bst_insert(&root, "b4", test_create_bst);
    mu_assert("bst_search: Equals 'test_create_bst'", bst_search(root, "b4") == test_create_bst);
    bst_free(root);
    return 0;
}

static char *all_tests() {
    mu_run_test(test_serialize_hmap);
    mu_run_test(test_dappendd_dstring);
    mu_run_test(test_djoin_dstring);
    mu_run_test(test_drange_dstring);
    mu_run_test(test_indexer);
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
    mu_run_test(test_create_bst);
    mu_run_test(test_insert_and_search_bst);
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
