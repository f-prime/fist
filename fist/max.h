#ifndef H_MAX
#define H_MAX

// https://stackoverflow.com/a/3437484
#define MAX(a,b)                                \
  ({ __typeof__ (a) _a = (a);                   \
    __typeof__ (b) _b = (b);                    \
    _a > _b ? _a : _b; })

#endif
