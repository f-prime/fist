#ifndef H_DSTRING
#define H_DSTRING

typedef struct dstring {
    int length;
    char *text;
} dstring;

dstring dappendc(dstring input, char character); // Apppend single char to string
dstring dappend(dstring input, char *characters); // Appends a string to the end of the dstring
dstring dstrip(dstring input, char character); // Strips a character from the string
dstring *dsplit(dstring input, char at); // Splits string at character
dstring dtrim(dstring input); // Trims whitespace and new line characters from beginning and end of dstring
dstring dreverse(dstring input); // Reverses a dstring
dstring dreplace(dstring input, char there, char with); // Replaces char with another
int dindexof(dstring input, char character); // Returns the index of a character or -1
dstring dcreate(char *initial); // Creates and returns a new dstring
dstring dempty(); // Creates an empty dstring
dstring dsplice(dstring input, int start, int end); // Splices a string between to indices
int dcount(dstring input, char character); // Count occurances of a character in the dstring
int dfree(dstring string); // Frees a dstring's memory

#endif
