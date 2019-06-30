#ifndef H_SERIALIZER
#define H_SERIALIZER

#include "dstring.h"
#include "hashmap.h"

void sdump(hashmap *hmap);
hashmap *sload();

#endif
