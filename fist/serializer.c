#include "serializer.h"
#include "dstring.h"
#include "hashmap.h"
#include "lzf.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

void sdump_compress(unsigned char *data, uint64_t original_size) {
    FILE *compressed = fopen("fist.db", "wb");
    fwrite(&original_size, sizeof(original_size), 1, compressed);

    char *buffer = malloc(original_size * 3);
    long size;
    if(!(size = lzf_compress(data, original_size, buffer, original_size * 3))) {
        printf("Compression error\n");
    }
    fwrite(buffer, size, 1, compressed);
    fclose(compressed);
}

void sdump(hashmap *hmap) {
    // Write binary data to a temporary file, load the temp file into memory, compress it, save it
    // to disk.

    FILE *dump = tmpfile();

    uint32_t num_indices = 0;

    for(int i = 0; i < HMAP_SIZE; i++) {
        // Get number of indices that have values
        hashmap on = hmap[i];
        if(on.length > 0)
            num_indices++;
    }
    unsigned int size = 0;

    size += fwrite(&num_indices, sizeof(num_indices), 1, dump);
    // Iterate through hashmap and write key and array of values to file

    for(int i = 0; i < HMAP_SIZE; i++) {
        hashmap on = hmap[i];
        if(on.length > 0) {
            for(int key = 0; key < on.length; key++) {
                keyval object = on.maps[key];
                uint32_t length = object.key.length;
                // Writes key length and key name to db file

                size += fwrite(&length, sizeof(length), 1, dump);
                size += fwrite(dtext(object.key), object.key.length, 1, dump);

                uint32_t num_values = object.values.length;
                // Writes number of values associated with key to db file
                size += fwrite(&num_values, sizeof(num_values), 1, dump);
                for(int value = 0; value < object.values.length; value++) {
                    // Writes value to db file
                    dstring value_on = object.values.values[value];
                    uint32_t val_length = value_on.length;

                    size += fwrite(&val_length, sizeof(val_length), 1, dump);
                    size += fwrite(dtext(value_on), value_on.length, 1, dump);
                }
            }
        }
    }

    fseek(dump, 0, SEEK_END);
    uint64_t len = ftell(dump);
    fseek(dump, 0, SEEK_SET);
    unsigned char *buffer = malloc(len);
    fread(buffer, 1, len, dump);

    sdump_compress(buffer, len);

    fclose(dump);
}

FILE *sload_compressed() {
    FILE *db;
    if((db = fopen("fist.db", "rb"))) {
        uint64_t original_size;
        fread(&original_size, 8, 1, db);

        fseek(db, 0, SEEK_END);
        long length = ftell(db);
        fseek(
            db, 0,
            SEEK_SET); // Skip first 8 bytes which are to indicate the original size of the db file.

        length -= 8;
        fseek(db, 8, SEEK_CUR);

        unsigned char *data = malloc(length);
        fread(data, 1, length, db);

        unsigned char *decompressed = malloc(original_size);
        int size;

        if(!(size = lzf_decompress(data, length, decompressed, original_size))) {
            printf("Error decompressing DB file");
            return 0;
        }

        fclose(db);

        FILE *tmp = tmpfile();
        fwrite(decompressed, original_size, 1, tmp);
        rewind(tmp);
        return tmp;
    }

    return 0;
}

hashmap *sload() {
    hashmap *hmap = hcreate();

    FILE *db;

    if((db = sload_compressed())) {
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
