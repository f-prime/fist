#include "dstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dequals(dstring s1, dstring s2) {
    return !strcmp(dtext(s1), dtext(s2));
}

dstring dappendc(dstring input, char character) {
    int new_size = input.length + 2;
    char *string;
    if(input.alloc_len == 0) {
        if(new_size <= DSTRING_SMALL) {
            string = input.static_text;
        } else {
            string = malloc(sizeof(char) * new_size);
            memcpy(string, input.static_text, input.length);
            input.alloc_len = new_size;
            input.text = string;
        }
    } else {
        string = realloc(dtext(input), sizeof(char) * new_size);
        input.alloc_len = new_size;
        input.text = string;
    }
    string[input.length] = character;
    string[input.length + 1] = 0;
    input.length++;
    return input;
}

dstring dappend(dstring input, char *characters) {
    int increase_by = strlen(characters) + 1;
    int new_size = strlen(dtext(input)) + increase_by;
    char *new_dstring = NULL;

    if(input.alloc_len == 0) {
        if(new_size <= DSTRING_SMALL) {
            new_dstring = input.static_text;
        } else {
            new_dstring = malloc(sizeof(char) * new_size);
            strcpy(new_dstring, input.static_text);
            input.alloc_len = new_size;
            input.text = new_dstring;
        }
    } else {
        new_dstring = realloc(input.text, sizeof(char) * new_size);
        input.alloc_len = new_size;
        input.text = new_dstring;
    }
    memcpy(&new_dstring[input.length], characters, increase_by);

    input.length += increase_by - 1;
    return input;
}

dstring dappendd(dstring input, dstring word) {
    return dappend(input, dtext(word));
}

dstring dempty() {
    dstring empty_dstring = {0, NULL, 0, {'\0'}};
    return empty_dstring;
}

dstring dcreate(char *initial) {
    return dappend(dempty(), initial);
}

dstring dreverse(dstring input) {
    dstring reversed = dempty();
    for(int i = input.length - 1; i >= 0; i--) {
        reversed = dappendc(reversed, dtext(input)[i]);
    }
    return reversed;
}

int dcount(dstring input, char character) {
    int occurances = 0;
    for(int i = 0; i < input.length; i++) {
        if(dtext(input)[i] == character)
            occurances++;
    }

    return occurances;
}

int dindexof(dstring input, char character) {
    int index = -1;
    for(int i = 0; i < input.length; i++) {
        if(dtext(input)[i] == character) {
            index = i;
            break;
        }
    }

    return index;
}

dstringa dcreatea() {
    dstringa strings = {0, NULL};
    return strings;
}

dstringa dpush(dstringa array, dstring input) {
    dstring new = dcreate(dtext(input)); // Created new object
    int new_length = array.length + 1;
    dstring *new_array = realloc(array.values, sizeof(dstring) * new_length);
    new_array[array.length] = new;
    dstringa new_dstringa = {new_length, new_array};
    return new_dstringa;
}

int dindexofa(dstringa array, dstring input) {
    int index = -1;
    for(int i = 0; i < array.length; i++) {
        if(dequals(array.values[i], input)) {
            index = i;
            break;
        }
    }
    return index;
}

dstring djoin(dstringa array, char with) {
    dstring output = dempty();
    for(int i = 0; i < array.length; i++) {
        output = dappend(output, dtext(array.values[i]));
        if(i != array.length - 1)
            output = dappendc(output, with);
    }

    return output;
}

dstringa drange(dstringa array, int start, int end) {
    if(start > end) {
        int tmp = start;
        start = end;
        end = tmp;
    }

    if(start < 0) {
        start = 0;
    } else if(start >= array.length) {
        start = array.length - 1;
    }

    if(end < 0) {
        end = 0;
    } else if(end >= array.length) {
        end = array.length - 1;
    }

    dstringa output = dcreatea();
    for(int i = start; i <= end; i++) {
        output = dpush(output, array.values[i]);
    }

    return output;
}

dstringa dsplit(dstring input, char at) {
    dstring new = dcreate(dtext(input));
    dstringa array = dcreatea();
    dstring string = dempty();
    for(int i = 0; i < new.length; i++) {
        char on = dtext(new)[i];
        if(on == at && string.length > 0) {
            array = dpush(array, string);
            string = dempty();
        } else {
            string = dappendc(string, on);
        }
    }

    if(string.length > 0) {
        array = dpush(array, string);
    }
    dfree(string);
    return array;
}

int dfreea(dstringa array) {
    for(int i = 0; i < array.length; i++) {
        dfree(array.values[i]);
    }

    free(array.values);
    return array.length;
}

dstringa dpop(dstringa array) {
    if(array.length == 0)
        return array;
    int new_length = array.length - 1;
    dfree(array.values[new_length]);
    dstring *shrunk = realloc(array.values, sizeof(dstring) * new_length);
    dstringa shrunk_dstringa = {new_length, shrunk};
    return shrunk_dstringa;
}

dstringa dremove(dstringa array, dstring input) {
    int index = dindexofa(array, input);
    if(index == -1)
        return array;

    dstringa new_array = dcreatea();
    for(int i = 0; i < array.length; i++) {
        if(i != index) {
            new_array = dpush(new_array, array.values[i]);
        }
    }
    dfreea(array);
    return new_array;
}

dstringa dset(dstringa array, unsigned int index, dstring with) {
    if(index > array.length) {
        array = dpush(array, with);
        return array;
    }

    dstringa new_array = dcreatea();
    for(int i = 0; i < array.length; i++) {
        if(i == index) {
            new_array = dpush(new_array, with);
        } else {
            new_array = dpush(new_array, array.values[i]);
        }
    }

    dfreea(array);
    return new_array;
}

dstring dsubstr(dstring input, unsigned int start, unsigned int end) {
    if(start > input.length - 1 || end > input.length - 1) {
        return input;
    }

    if(end < start) {
        int tmp = end;
        end = start;
        start = tmp;
    }

    dstring output = dempty();
    for(int i = start; i <= end; i++) {
        output = dappendc(output, dtext(input)[i]);
    }
    dfree(input);
    return output;
}

dstring dtrim(dstring input) {
    int end_index = input.length - 1;
    char end_char = dtext(input)[end_index];
    while((end_char == ' ' || end_char == '\n' || end_char == '\r' || end_char == '\t') &&
          end_index > 0) {
        end_index--;
        end_char = dtext(input)[end_index];
    }

    int start_index = 0;
    char start_char = dtext(input)[0];
    while(start_index < end_index &&
          (start_char == '\n' || start_char == ' ' || start_char == '\t' || start_char == '\r')) {
        start_index++;
        start_char = dtext(input)[start_index];
    }

    dstring output = dsubstr(input, start_index, end_index);

    return output;
}

dstring dreplace(dstring input, char character, char with) {
    dstring new_string = dempty();
    for(int i = 0; i < input.length; i++) {
        char on = dtext(input)[i];
        if(on == character) {
            new_string = dappendc(new_string, with);
        } else {
            new_string = dappendc(new_string, on);
        }
    }

    dfree(input);
    return new_string;
}

int dfree(dstring string) {
    if(string.alloc_len != 0)
        free(string.text);
    return string.length;
}
