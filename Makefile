CXX_FLAG = --std=c++11 -g

all: ./runMovies

runMovies: main.o movies.o
	g++ $(CXX_FLAG) -o runMovies main.o movies.o

main.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp

movies.o: movies.cpp
	g++ -c $(CXX_FLAG) movies.cpp

clean:
	rm -f runMovie *.o