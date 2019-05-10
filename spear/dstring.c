#include <string.h>
#include <stdio.h>
#include "dstring.h"
#include <stdlib.h>

dstring dempty() {
    char *empty = malloc(sizeof(char));
    empty[0] = 0;
    dstring empty_dstring = {0, empty};
    return empty_dstring;
}

dstring dcreate(char *initial) {
    int string_length = strlen(initial);
    int buff_size = strlen(initial) + 1;
    char *buffer = malloc(sizeof(char) * buff_size);
    memset(buffer, 0, buff_size);
    memcpy(buffer, initial, string_length);
    dstring new_dstring = {string_length, buffer};
    return new_dstring;
}
