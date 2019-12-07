#Makefile #
all: TP1

TP1: main.o function.o 
	gcc -o TP1 main.o function.o

main.o: main.c function.h
	gcc -o main.o main.c -c -W -Wall -ansi

function.o: function.c function.h
	gcc -o function.o function.c -c -W -Wall -ansi 
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf TP1