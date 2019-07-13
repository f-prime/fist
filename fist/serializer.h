#ifndef H_SERIALIZER
#define H_SERIALIZER

#include "dstring.h"
#include "hashmap.h"

void sdump(const char *path, hashmap *hmap);
hashmap *sload(const char *path);

#endif
