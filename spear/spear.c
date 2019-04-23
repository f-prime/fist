#include <stdio.h>
#include <stdlib.h>
#include "create_indices.h"
#include "hashmap.h"
#include "linkedlist.h"

void process_text(char *text, char *val) {
    l_item ll = ll_create();
    ll = ll_add(ll, "Ley", "Test");
    ll = ll_add(ll, "Yel", "A");
    ll = ll_add(ll, "TEST", "BOI");
    ll = ll_add(ll, "TEST", "AY");
    ll = ll_add(ll, "TEST", "GOOD");
    
    //l_item v1 = ll_key(ll, "Yel");
    l_item values = ll_get(ll, 2);
    //printf("%d\n", values->num_vals);
    for(int i = 0; i < values->num_vals; i++) {
        printf("WOW: %s\n", values->values[i]);
    }

    
    /*
    t_index index = indexer(text, 10);   
    
    t_hval *map = h_create();
    
    for(int x = 0; x < index.length; x++) {
        map = h_add(map, index.index[x], val); 
    }
    t_hval item = h_get(map, "test");
    
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
    */
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("You need to pass a string as the second argument");
        exit(1);
    }
    process_text(argv[1], "1");
    return 0;
}
