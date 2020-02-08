ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: build
	./prog.out

build: main.o
	$(CC) main.o -o prog.out

main.o: main.c
	$(CC) -c main.c

haskell: main.o
	$(CC) -o prog.out main.o
	stack ghc Main.hs
	./prog.out haskell | ./main > pic.ppm

memtest:
	valgrind --leak-check=yes ./prog.out

debug:
	gcc -g tmp.c

clean:
	rm *.o *.out *.ppm
