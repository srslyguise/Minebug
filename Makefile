CC=g++
LIBS=-lSDL -lGL -lGLU

all: mbug

mbug: mbug.o utils.o cube.o
	$(CC) -o mbug mbug.o utils.o cube.o $(LIBS)

mbug.o: main.cpp utils.hpp cube.hpp
	$(CC) -c -o mbug.o main.cpp

utils.o: utils.cpp utils.hpp
	$(CC) -c -o utils.o utils.cpp

cube.o: cube.cpp cube.hpp
	$(CC) -c -o cube.o cube.cpp

clean:
	rm -f *.o
	rm -f mbug
