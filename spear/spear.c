#include <stdio.h>
#include <stdlib.h>
#include "indexer.h"

void process_text(char *text) {
    indexer(text, 10);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("You need to pass a string as the second argument");
        exit(1);
    }
    process_text(argv[1]);
    return 0;
}
