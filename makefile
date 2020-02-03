all: main.o
	gcc -o prog.out main.o
	./prog.out

main.o: main.c
	gcc -c main.c
