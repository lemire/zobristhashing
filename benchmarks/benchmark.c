#include <stdio.h>
#include <stdlib.h>

#include "zobrist.h"

#define RDTSC_START(cycles)                                                   \
    do {                                                                      \
        register unsigned cyc_high, cyc_low;                                  \
        __asm volatile(                                                       \
            "cpuid\n\t"                                                       \
            "rdtsc\n\t"                                                       \
            "mov %%edx, %0\n\t"                                               \
            "mov %%eax, %1\n\t"                                               \
            : "=r"(cyc_high), "=r"(cyc_low)::"%rax", "%rbx", "%rcx", "%rdx"); \
        (cycles) = ((uint64_t)cyc_high << 32) | cyc_low;                      \
    } while (0)

#define RDTSC_FINAL(cycles)                                                   \
    do {                                                                      \
        register unsigned cyc_high, cyc_low;                                  \
        __asm volatile(                                                       \
            "rdtscp\n\t"                                                      \
            "mov %%edx, %0\n\t"                                               \
            "mov %%eax, %1\n\t"                                               \
            "cpuid\n\t"                                                       \
            : "=r"(cyc_high), "=r"(cyc_low)::"%rax", "%rbx", "%rcx", "%rdx"); \
        (cycles) = ((uint64_t)cyc_high << 32) | cyc_low;                      \
    } while (0)


/*
 * Prints the best number of operations per cycle where
 * test is the function call,  repeat is the number of times we should repeat and size is the
 * number of operations represented by test.
 */
#define BEST_TIME(test, expected, repeat, pre, size)                           \
    do {                                                              \
        printf("%s: ", #test);                                        \
        fflush(NULL);                                                 \
        uint64_t cycles_start, cycles_final, cycles_diff;             \
        uint64_t min_diff = (uint64_t)-1;                             \
        int wrong_answer = 0;                                         \
        for (int i = 0; i < repeat; i++) {                            \
            __asm volatile("" ::: /* pretend to clobber */ "memory"); \
            pre;                                                      \
            RDTSC_START(cycles_start);                                \
            if (test != expected) wrong_answer = 1;                     \
            RDTSC_FINAL(cycles_final);                                \
            cycles_diff = (cycles_final - cycles_start);              \
            if (cycles_diff < min_diff) min_diff = cycles_diff;       \
        }                                                             \
        uint64_t S = (uint64_t)size;                                  \
        float cycle_per_op = (min_diff) / (float)S;                   \
        printf("size = %d,  %.2f cycles per operation", size, cycle_per_op);           \
        if (wrong_answer) printf(" [ERROR]");                         \
        printf("\n");                                                 \
        fflush(NULL);                                                 \
    } while (0)

static void flush(const char *s, size_t length, const zobrist_t * k) {
  for (size_t i = 0 ; i < length ; i++ ) {
    __builtin_ia32_clflush(k->hashtab [ i % MAX_ZOBRIST_LENGTH ] + (unsigned char)s[i]);
    __builtin_ia32_clflush(s + i);
  }
}

void demo() {
    int repeat = 500;
    zobrist_t k;
    init_zobrist(& k);
    for(int size = 1; size < MAX_ZOBRIST_LENGTH; ++size) {
      char * data = malloc(size);
      for(int z = 0; z < size; ++z) data[z] = (char) rand();
      uint64_t expected = zobrist (data, size, &k);
      BEST_TIME(zobrist (data, size, &k), expected, repeat, , size);
      BEST_TIME(zobrist (data, size, &k), expected, repeat, flush(data, size, &k), size);
      free(data);
    }
}

int main() {
    demo();
}
