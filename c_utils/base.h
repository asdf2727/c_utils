#ifndef C_UTILS_BASE_H
#define C_UTILS_BASE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // memcopy
#include <math.h>
#include <assert.h>

#define DEBUG

#define min(a, b) \
    ({  __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; })
#define max(a, b) \
    ({  __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b; })

#ifdef DEBUG

#include <stdio.h>

#define str(s) #s
#define assertf(condition, msg) \
    if(!(condition)) { fprintf(stderr, "Fatal error: "str(msg)"\n\n"); assert(condition); }
#else
#define assertf(condition, msg) \
	if(!(A)) { assert(0); }
#endif

#endif //C_UTILS_BASE_H
