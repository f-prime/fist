#include <string.h>
#include <stdio.h>
#include "dstring.h"
#include <stdlib.h>

dstring dappend(dstring input, char *characters) {
    int increase_by = strlen(characters) + 1;
    int new_size = strlen(input.text) + increase_by;
    char *new_dstring = realloc(input.text, sizeof(char) * new_size);
    strncat(new_dstring, characters, increase_by - 1);
    new_dstring[new_size - 1] = 0;
    input.length += increase_by - 1;
    input.text = new_dstring;
    return input;
}

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

dstring dreverse(dstring input) {
    char *reversed = malloc(sizeof(char) * input.length + 1);
    memset(reversed, 0, input.length + 1);
    int reversed_buffer_on = 0;
    for(int i = input.length - 1; i >= 0; i--) {
        reversed[reversed_buffer_on] = input.text[i];
        reversed_buffer_on++;
    }
    dstring reversed_dstring = {input.length, reversed};
    return reversed_dstring;
}

int dfree(dstring string) {
    free(string.text);
    return string.length;
}
