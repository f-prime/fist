#ifndef H_UTILS
#define H_UTILS

#define MIN(a, b)                                \
  ({ __typeof__ (a) _a = (a);			 \
    __typeof__ (b) _b = (b);			 \
    _a < _b ? _a : _b; })

#endif
