all : main

log.o: board.cpp checkmove.cpp node.cpp ai.cpp
	g++ -c board.cpp checkmove.cpp node.cpp ai.cpp

main: log.o main.cpp
	g++ -std=c++0x -Wall -o main main.cpp log.o

clean:
	rm log.o main.o main
