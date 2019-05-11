#ifndef H_DSTRING
#define H_DSTRING

typedef struct dstring {
    int length;
    char *text;
} dstring;

dstring dappend(dstring input, char *characters); // Appends a string to the end of the dstring
dstring dstrip(dstring input, char character); // Strips a character from the string
dstring *dsplit(dstring input, char at); // Splits string at character
dstring dtrim(dstring input); // Trims whitespace and new line characters from beginning and end of dstring
dstring dreverse(dstring input); // Reverses a dstring
dstring dcreate(char *initial); // Creates and returns a new dstring
dstring dempty(); // Creates an empty dstring
dstring dsplice(dstring input, int start, int end); // Splices a string between to indices
int dfree(dstring string); // Frees a dstring's memory

#endif
