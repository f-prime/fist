#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "linkedlist.h"
#include "indexer.h"
#include "server.h"

void test() {
    /*
    l_item *hm = h_create();
    hm = h_add(hm, "KEY", "VAL");
    hm = h_add(hm, "KEY", "VAL2");
    hm = h_add(hm, "K2", "VAL3");

    for(int i = 0; i < 100000; i++) {
        char buffer[1000];
        sprintf(buffer, "KEY%d", i);
        hm = h_add(hm, buffer, "VALUE");
    }
    printf("STARTED GET\n");
    l_item k = h_get(hm, "KEY10000");
    printf("%s %s\n", k->key, k->values[0]);
    */
}

int main(int argc, char *argv[]) {
    //test();
    start_server("127.0.0.1", 5575);
    return 0;
}
