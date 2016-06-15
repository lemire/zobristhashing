#include <stdlib.h>


#include "zobrist.h"

static uint64_t get64rand() {
    return
    (((uint64_t) rand() <<  0) & 0x000000000000FFFFull) |
    (((uint64_t) rand() << 16) & 0x00000000FFFF0000ull) |
    (((uint64_t) rand() << 32) & 0x0000FFFF00000000ull) |
    (((uint64_t) rand() << 48) & 0xFFFF000000000000ull);
}

void init_zobrist(zobrist_t * k) {
	for ( int32_t i = 0 ; i < MAX_ZOBRIST_LENGTH ; i++ ) {
		for ( int32_t j = 0 ; j < ( 1 << CHAR_BIT) ; j++ ) {
			k->hashtab [i][j]  = get64rand();
		}
  }
}

uint64_t zobrist (const char *signeds, size_t length, const zobrist_t * k) {
    const unsigned char *s = (const unsigned char *) signeds;
    uint64_t h = 0;
    if(length > MAX_ZOBRIST_LENGTH) length = MAX_ZOBRIST_LENGTH;
    size_t i = 0;
    for ( ; i + 7  < length ; i += 8 ) {
      h ^= k->hashtab [ i ] [s[i]];
      h ^= k->hashtab [ i + 1 ] [s[i + 1]];
      h ^= k->hashtab [ i + 2 ] [s[i + 2]];
      h ^= k->hashtab [ i + 3 ] [s[i + 3]];
      h ^= k->hashtab [ i + 4 ] [s[i + 4]];
      h ^= k->hashtab [ i + 5 ] [s[i + 5]];
      h ^= k->hashtab [ i + 6 ] [s[i + 6]];
      h ^= k->hashtab [ i + 7 ] [s[i + 7]];
    }
    for (; i < length ; i++ )
      h ^= k->hashtab [ i ] [s[i]];
    return h;
}

uint64_t zobrist_nt (const char *signeds, const zobrist_t * k) {
    const unsigned char *s = (const unsigned char *) signeds;
    uint64_t h = 0;
    for (size_t i = 0; s[i] ; i++ )
      h ^= k->hashtab [ i % MAX_ZOBRIST_LENGTH ] [s[i]];
    return h;
}


