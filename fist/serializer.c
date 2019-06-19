#include "stdlib.h"
#include "stdio.h"
#include "hashmap.h"
#include "dstring.h"
#include "serializer.h"
#include <arpa/inet.h>

void sdump(hashmap *hmap) {
    /*
     * Data gets written to files in little endian form. We need to convert
     * it to little endian here so that when it gets written it is written in
     * big endian format so that when we deserialize the data it's easyier. 
     */

    // Write size of hashmap to file. (# keys)
    // htonl changes from big endian to little endian 

    FILE *dump = fopen("fist.db", "wb");

    // Iterate through hashmap and write key and array of values to file
    
    for(int i = 0; i < HMAP_SIZE; i++) {
        hashmap on = hmap[i];
        if(on.length > 0) {
            for(int key = 0; key < on.length; key++) {
                keyval object = on.maps[key];
                int length = htonl(object.key.length);
                // Writes key length and key name to db file
                fwrite(&length, sizeof(length), 1, dump);
                fwrite(object.key.text, object.key.length, 1, dump);
                
                int num_values = htonl(object.values.length);
                // Writes number of values associated with key to db file
                fwrite(&num_values, sizeof(num_values), 1, dump);
                for(int value = 0; value < object.values.length; value++) {
                    // Writes value to db file
                    dstring value_on = object.values.values[value];
                    int val_length = htonl(value_on.length);
                    fwrite(&val_length, sizeof(val_length), 1, dump);
                    fwrite(value_on.text, value_on.length, 1, dump);
                }
            }
        }
    }
    fclose(dump);
}

hashmap *sload() {
    hashmap *hmap = hcreate();
    FILE *db;
    if((db = fopen("fist.db", "rb"))) {
        
    } 
    return hmap;
}
