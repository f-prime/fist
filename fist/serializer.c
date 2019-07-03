#include "serializer.h"
#include "dstring.h"
#include "hashmap.h"
#include "lzf.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

void sdump(hashmap *hmap) {
    // Write size of hashmap to file. (# keys)

    FILE *dump = fopen("fist.db", "wb");
    FILE *dump_compressed = fopen("fist.db.compressed", "wb");

    uint32_t num_indices = 0;

    for(int i = 0; i < HMAP_SIZE; i++) {
        // Get number of indices that have values
        hashmap on = hmap[i];
        if(on.length > 0)
            num_indices++;
    }
    unsigned int current_size = sizeof(num_indices);
    void *buffer = malloc(current_size);
    memcpy(buffer, &num_indices, sizeof(num_indices));

    fwrite(&num_indices, sizeof(num_indices), 1, dump);
    // Iterate through hashmap and write key and array of values to file

    for(int i = 0; i < HMAP_SIZE; i++) {
        hashmap on = hmap[i];
        if(on.length > 0) {
            for(int key = 0; key < on.length; key++) {
                keyval object = on.maps[key];
                uint32_t length = object.key.length;
                // Writes key length and key name to db file

                current_size += sizeof(length);
                buffer = realloc(buffer, current_size);
                memcpy(buffer, &length, sizeof(length));
                fwrite(&length, sizeof(length), 1, dump);

                current_size += object.key.length;
                buffer = realloc(buffer, current_size);
                memcpy(buffer, dtext(object.key), object.key.length);
                fwrite(dtext(object.key), object.key.length, 1, dump);

                uint32_t num_values = object.values.length;
                // Writes number of values associated with key to db file
                current_size += sizeof(num_values);
                buffer = realloc(buffer, current_size);
                memcpy(buffer, &num_values, sizeof(num_values));
                fwrite(&num_values, sizeof(num_values), 1, dump);
                for(int value = 0; value < object.values.length; value++) {
                    // Writes value to db file
                    dstring value_on = object.values.values[value];
                    uint32_t val_length = value_on.length;

                    current_size += sizeof(val_length);
                    buffer = realloc(buffer, current_size);
                    memcpy(buffer, &val_length, sizeof(val_length));
                    fwrite(&val_length, sizeof(val_length), 1, dump);

                    current_size += sizeof(value_on.length);
                    buffer = realloc(buffer, current_size);
                    memcpy(buffer, dtext(value_on), value_on.length);
                    fwrite(dtext(value_on), value_on.length, 1, dump);
                }
            }
        }
    }

    printf("%d\n", current_size);
    fwrite(buffer, current_size, 1, dump_compressed);
    fclose(dump_compressed);
    fclose(dump);
}

hashmap *sload() {
    hashmap *hmap = hcreate();
    FILE *db;
    if((db = fopen("fist.db", "rb"))) {
        uint32_t num_keys;
        fread(&num_keys, sizeof(num_keys), 1, db);
        for(int i = 0; i < num_keys; i++) {
            uint32_t key_size;
            fread(&key_size, sizeof(key_size), 1, db);
            char key[key_size + 1];
            key[key_size] = 0;
            fread(key, key_size, 1, db);
            uint32_t num_vals;
            fread(&num_vals, sizeof(num_vals), 1, db);

            for(int j = 0; j < num_vals; j++) {
                uint32_t val_size;
                fread(&val_size, sizeof(val_size), 1, db);
                char value[val_size + 1];
                value[val_size] = 0;
                fread(value, val_size, 1, db);
                hmap = hset(hmap, dcreate(key), dcreate(value));
            }
        }

        printf("Database file has been loaded. Previous state restored.\n");
        fclose(db);
    } else {
        printf("No previous state found. Creating new database file.\n");
    }

    return hmap;
}
