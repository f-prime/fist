#ifndef H_DSTRING
#define H_DSTRING

// Size of a small word that we want to keep on the stack to avoid multiple alloc/realloc calls.
// Increasing this will reduce malloc overhead, improve cache hits, but increase memory wasatage.
#define DSTRING_SMALL 32

typedef struct dstring {
    int length;
    char *text;
	int alloc_len;
    char static_text[DSTRING_SMALL];
} dstring;

typedef struct dstringa {
    int length;
    dstring *values;
} dstringa;

#define dtext(input) (!input.alloc_len ? input.static_text : input.text)

int dequals(dstring s1, dstring s2);
dstring dappendc(dstring input, char character); // Apppend single char to string
dstring dappend(dstring input, char *characters); // Appends a string to the end of the dstring
dstring dtrim(dstring input); // Trims whitespace and new line characters from beginning and end of dstring
dstring dreverse(dstring input); // Reverses a dstring
dstring dreplace(dstring input, char there, char with); // Replaces char with another
int dindexof(dstring input, char character); // Returns the index of a character or -1
dstring dcreate(char *initial); // Creates and returns a new dstring
dstring dempty(); // Creates an empty dstring
dstring dsubstr(dstring input, unsigned int start, unsigned int end); // Returns the string between to indices of the input dstring
int dcount(dstring input, char character); // Count occurances of a character in the dstring
int dfree(dstring string); // Frees a dstring's memory
dstring dappendd(dstring input, dstring word); // Append two dstrings together

// List of dstrings

dstringa dsplit(dstring input, char at); // Splits string at character
dstringa dcreatea(); // Create empty array of dstrings
dstringa dpush(dstringa array, dstring input); // Push dstring to list of dstrings
dstringa dremove(dstringa array, dstring input); // Remove item from dstring array
dstringa dpop(dstringa array); // Pop from stack
int dindexofa(dstringa array, dstring input); // Find index of dstring
dstringa dset(dstringa array, unsigned int index, dstring with); // Replace index in dstring array with another dstring
dstringa drange(dstringa array, int start, int end); // Return new array between two ranges
int dfreea(dstringa array); // Frees a dstring array
dstring djoin(dstringa array, char with); // Joins a string with a character
#endif
