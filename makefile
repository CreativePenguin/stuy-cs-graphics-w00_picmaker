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

clean:
	rm *.o *.out
