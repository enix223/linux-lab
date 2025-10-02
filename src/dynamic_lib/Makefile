#####################
# Build dynamic lib
#####################

.PHONY: clean

SRC = $(PWD)/../lib_shared/
LIB = $(PWD)

all: main

main: libalgebra
	gcc $(SRC)/main.c -I $(SRC) -L $(LIB) -lalgebra -o main

run: main
	LD_LIBRARY_PATH=$(LIB) ./main

deps: main
	LD_LIBRARY_PATH=$(LIB) ldd main

libalgebra: algebra.o
	gcc -shared -o libalgebra.so algebra.o

# -fPIC: Generate Position-Independent Code (required for shared libraries)
algebra.o:
	gcc -fPIC -c $(SRC)/algebra.c -Wall -o algebra.o -I $(SRC)

clean:
	rm -rf *.o *.so main
