# zobristhashing
Zobrist hashing in C

Zobrist hashing is the simplest form of tabulation-based hashing. See https://en.wikipedia.org/wiki/Zobrist_hashing

It can be shown to be 3-wise independent.

We implemented a version that can hash strings up length up to 256 bytes using 512 KB of random bits. 

This C code expects a GCC-like compiler on an x64 system.

The code demonstrates that it is difficult on a x64 to hash much more than 2 bytes per cycle, at least with 
straight-forward C code. The 2 bytes per cycle bound can deteriorate quickly because of cache faults.
 In contrast, it is possible to hash 5 to 10 bytes per cycle using fast hash 
families while using much less code. See https://github.com/lemire/StronglyUniversalStringHashing

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


