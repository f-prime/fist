#include <stdio.h>
#include <stdlib.h>
#include "create_indices.h"
#include "hashmap.h"
#include "linkedlist.h"

void process_text(char *text, char *val) {
    l_item *hm = h_create();
    hm = h_add(hm, "KEY", "VAL");
    hm = h_add(hm, "KEY", "VAL2");
    hm = h_add(hm, "K2", "VAL3");

    for(int i = 0; i < 10000; i++) {
        char buffer[1000];
        sprintf(buffer, "Key%d", i);
        hm = h_add(hm, buffer, "VALUE");
    }

    l_item k = h_get(hm, "KEY3");
    printf("%s %s\n", k->key, k->values[0]);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("You need to pass a string as the second argument");
        exit(1);
    }
    process_text(argv[1], "1");
    return 0;
}
