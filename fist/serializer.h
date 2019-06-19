#ifndef H_SERIALIZER
#define H_SERIALIZER

#include "hashmap.h"
#include "dstring.h"

void sdump(hashmap *hmap);
hashmap *sload();

#endif
