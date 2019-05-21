#include <string.h>
#include <stdio.h>
#include "dstring.h"
#include <stdlib.h>

int dequals(dstring s1, dstring s2) {
    return !strcmp(s1.text, s2.text); 
}

dstring dappendc(dstring input, char character) {
    int new_size = input.length + 2;
    char *string = realloc(input.text, sizeof(char) * new_size);
    string[input.length] = character;
    string[input.length + 1] = 0;
    input.length++;
    input.text = string;
    return input;
}

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

int dcount(dstring input, char character) {
    int occurances = 0;
    for(int i = 0; i < input.length; i++) {
        if(input.text[i] == character)
            occurances++;
    }

    return occurances;
}

int dindexof(dstring input, char character) {
    int index = -1;
    for(int i = 0; i < input.length; i++) {
        if(input.text[i] == character) {
            index = i;
            break;
        }
    }

    return index;
}

dstringa dcreatea() {
    dstring *empty = malloc(sizeof(dstring));
    dstringa strings = {0, empty}; 
    return strings;
}

dstringa dpush(dstringa array, dstring input) {
    dstring new = dcreate(input.text); // Created new object
    int new_length = array.length + 1;
    dstring *new_array = realloc(array.values, sizeof(dstring) * new_length);
    new_array[array.length] = new;
    dstringa new_dstringa = {new_length, new_array};
    return new_dstringa;
}

int dindexofa(dstringa array, dstring input) {
    int index = -1;
    for(int i = 0; i < array.length; i++) {
        if(!strcmp(array.values[i].text, input.text)) {
            index = i;
            break;
        }
    }

    return index;
}

dstring djoin(dstringa array, char with) {
    dstring output = dempty();
    for(int i = 0; i < array.length; i++) {
        output = dappend(output, array.values[i].text);
        if( i != array.length - 1)
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
    dstringa array = dcreatea();
    dstring string = dempty();
    for(int i = 0; i < input.length; i++) {
        char on = input.text[i];
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
        output = dappendc(output, input.text[i]);
    }
    dfree(input);
    return output;
}

dstring dtrim(dstring input) {
    int end_index = input.length - 1;
    char end_char = input.text[end_index];
    while((end_char == ' ' || end_char == '\n' || end_char == '\r' || end_char == '\t') && end_index > 0) {
        end_index--;
        end_char = input.text[end_index];
    }

    int start_index = 0;
    char start_char = input.text[0];
    while(start_index < end_index && (start_char == '\n' || start_char == ' ' || start_char == '\t' || start_char == '\r')) {
        start_index++;
        start_char = input.text[start_index];
    }

    dstring output = dsubstr(input, start_index, end_index);

    return output;
}

dstring dreplace(dstring input, char character, char with) {
    dstring new_string = dempty();
    for(int i = 0; i < input.length; i++) {
        char on = input.text[i];
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
    free(string.text);
    return string.length;
}
