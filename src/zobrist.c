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

uint64_t zobrist (const char *s, size_t length, const zobrist_t * k) {
    uint64_t h = 0;
    if(length > MAX_ZOBRIST_LENGTH) length = MAX_ZOBRIST_LENGTH;
    size_t i = 0;
    for ( ; i + 3  < length ; i+= 4 ) {
      h ^= k->hashtab [ i ] [(unsigned char)s[i]];
      h ^= k->hashtab [ i + 1 ] [(unsigned char)s[i+1]];
      h ^= k->hashtab [ i + 2 ] [(unsigned char)s[i+2]];
      h ^= k->hashtab [ i + 3 ] [(unsigned char)s[i+3]];
    }
    for (; i < length ; i++ )
      h ^= k->hashtab [ i ] [(unsigned char)s[i]];
    return h;
}
