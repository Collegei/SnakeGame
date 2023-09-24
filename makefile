
all:main

main:main.o input.o snake.o
	g++ main.o input.o snake.o -o main -lncurses

main.o:main.cpp
	g++ -c main.cpp -o main.o

input.o:input.cpp
	g++ -c input.cpp -o input.o

snake.o:snake.cpp
	g++ -c snake.cpp -o snake.o

clean:
	rm -f *.o main
