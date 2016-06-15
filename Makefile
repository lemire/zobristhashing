# minimalist makefile
.SUFFIXES:
#
.SUFFIXES: .cpp .o .c .h
ifeq ($(DEBUG),1)
CFLAGS = -fPIC  -std=c99 -ggdb -march=native -Wall -Wextra -Wshadow -fsanitize=undefined  -fno-omit-frame-pointer -fsanitize=address
else
CFLAGS = -fPIC -std=c99 -O3  -march=native -Wall -Wextra -Wshadow
endif # debug
OBJECTS=zobrist.o
all: benchmark  $(OBJECTS)
HEADERS=./include/zobrist.h

zobrist.o: ./src/zobrist.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/zobrist.c -Iinclude

benchmark: zobrist.o ./benchmarks/benchmark.c $(HEADERS)
	$(CC) $(CFLAGS) -o benchmark ./benchmarks/benchmark.c zobrist.o -Iinclude
clean:
	rm -f  *.o benchmark
