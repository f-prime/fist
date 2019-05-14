#ifndef H_DSTRING
#define H_DSTRING

typedef struct dstring {
    int length;
    char *text;
} dstring;

typedef struct dstringa {
    int length;
    char *dstring;
} dstringa;

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
dstring dsubstr(dstring input, int start, int end); // Returns the string between to indices of the input dstring
int dcount(dstring input, char character); // Count occurances of a character in the dstring
int dfree(dstring string); // Frees a dstring's memory

// List of dstrings 

dstringa dcreatea(); // Create empty array of dstrings
dstringa dpush(dstringa array, dstring input); // Push dstring to list of dstrings
dstringa dremove(dstringa array, dstring input); // Remove item from dstring array
dstringa dpop(dstringa array); // Pop from stack
int dindexofa(dstringa array, dstring input); // Find index of dstring
dstringa dset(dstringa array, int index, dstring with); // Replace index in dstring array with another dstring
int dfreea(dstringa array);

#endif
