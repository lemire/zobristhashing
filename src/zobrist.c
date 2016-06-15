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
    for (size_t i = 0 ; i < length ; i++ )
      h ^= k->hashtab [ i % MAX_ZOBRIST_LENGTH ] [(unsigned char)s[i]];
    return h;
}
