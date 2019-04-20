#include <stdio.h>
#include <stdlib.h>
#include "indexer.h"
#include "hashmap.h"

void process_text(char *text) {
    //indexer(text, 10);
    t_hval *map = h_create();
    t_hval *n_map = h_add(map, "Test", "dsjsfjsdfTer");
    t_hval entry = h_get(n_map, "Test");
    printf("%s %s\n", entry.key, entry.values[0]);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("You need to pass a string as the second argument");
        exit(1);
    }
    process_text(argv[1]);
    return 0;
}
