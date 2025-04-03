all: a.out
	./a.out

a.out: main.o
	g++ main.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *.o *.out
