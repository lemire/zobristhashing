# zobristhashing
Zobrist hashing in C

[Zobrist hashing](https://en.wikipedia.org/wiki/Zobrist_hashing) is the simplest form of [tabulation-based hashing](https://en.wikipedia.org/wiki/Tabulation_hashing). It can be shown to be 3-wise independent. The Zobrist approach tested here is used in real systems, e.g., Gigablast https://www.gigablast.com/ Alternatively, one could use a tabulation-based function as a complement to other hash functions: first hash the content down to a few bytes (e.g., 4) and then apply a tabulation-based hash on the result.

Tabulation-based hashing uses a lot of memory and is susceptible to cache faults. Moreover, its speed is limited (in part) by the system's ability to issue random access loads.

This C code expects a GCC-like compiler on an x64 system.

The code demonstrates that it is difficult on a x64 to hash much more than 0.65 bytes per cycle on recent Intel processors, even when
repeatedly hashing the same short string. In contrast, it is possible to hash 4 to 10 bytes per cycle using fast hash 
families. See https://github.com/lemire/StronglyUniversalStringHashing



## C Usage
```C
zobrist_t k;
init_zobrist(& k);// call once

// then you can hash as many strings as you want:
uint64_t hashvalue = zobrist (mystring, mystringsize, &k)

// for null-terminated strings, you can use:
uint64_t hashvalue = zobrist_nt (mystring,  &k)

// strings longer than 256 bytes fail the theoretical bounds
```

## Usage 

```
make
./benchmark
```

## Relevant software libraries

 - https://github.com/lemire/StronglyUniversalStringHashing
 - https://github.com/lemire/clhash


## References

- Daniel Lemire, The universality of iterated hashing over variable-length strings, Discrete Applied Mathematics 160 (4-5), 2012. http://arxiv.org/abs/1008.1715
- Owen Kaser, Daniel Lemire, Strongly universal string hashing is fast, Computer Journal 57(11), 2014. http://arxiv.org/abs/1202.4961
- Daniel Lemire, Owen Kaser, Faster 64-bit universal hashing using carry-less multiplications, Journal of Cryptographic Engineering (to appear) http://arxiv.org/abs/1503.03465


