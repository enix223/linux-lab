#####################
# Build static lib
#####################

.PHONY: clean

SRC = $(PWD)/../lib_shared/
LIB = $(PWD)

all: main

main: libalgebra
	gcc $(SRC)/main.c -I $(SRC) -L $(LIB) -lalgebra -o main

libalgebra: algebra.o
	ar rcs libalgebra.a algebra.o

algebra.o:
	gcc -c $(SRC)/algebra.c -Wall -o algebra.o -I $(SRC)

clean:
	rm -rf *.o *.a main
