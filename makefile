ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o prog.out main.o
	./prog.out

main.o: main.c
	$(CC) -c main.c

haskell: main.o
	$(CC) -o prog.out main.o
	stack ghc Main.hs
	./prog.out haskell | ./main > pic.ppm

clean:
	rm *.o *.out *.ppm
