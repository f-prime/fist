#include <stdio.h>
#include <stdlib.h>
#include "indexer.h"
#include "hashmap.h"

void process_text(char *text, char *val) {
    t_index index = indexer(text, 10);   
    
    t_hval *map = h_create();
    
    for(int x = 0; x < index.length; x++) {
        map = h_add(map, index.index[x], val); 
    }
    map = h_add(map, "is", "2");
    map = h_add(map, "is", "3");
    t_hval item = h_get(map, "is");
    
    if(item.length == 1) {
        printf("[%s]", item.values[0]);
    } else {
        for(int x = 0; x < item.length; x++) {
            if(x == 0) {
                printf("[%s, ", item.values[x]);
            } else if(x == item.length - 1){
                printf("%s]", item.values[x]);
            } else {
                printf("%s, ", item.values[x]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("You need to pass a string as the second argument");
        exit(1);
    }
    process_text(argv[1], "1");
    return 0;
}
