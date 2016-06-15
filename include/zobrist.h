#ifndef ZOBRIST_H
#define ZOBRIST_H

#include <limits.h>
#include <stdint.h>
#include <stddef.h>

enum {MAX_ZOBRIST_LENGTH=256};

typedef struct zobrist_s {
  uint64_t hashtab[MAX_ZOBRIST_LENGTH][1 << CHAR_BIT] ;
} zobrist_t;

void init_zobrist(zobrist_t * k);

/**
* hash string s of length "length" given keys, length should
* not exceed MAX_ZOBRIST_LENGTH or theoretical analysis fails.
*/
uint64_t zobrist (const char *s, size_t length, const zobrist_t * k);

/**
* Same but for null-terminated strings.
*/
uint64_t zobrist_nt (const char *s, const zobrist_t * k);


#endif
