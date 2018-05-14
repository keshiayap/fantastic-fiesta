all : main board.o

board.o: board.cpp
	g++ -c board.cpp

checkmove.o: checkmove.cpp
	g++ -c checkmove.cpp

node.o: node.cpp
	g++ -c node.cpp

ai.o: ai.cpp
	g++ -c ai.cpp


log.o: board.cpp checkmove.cpp node.cpp ai.cpp
	g++ -c board.cpp checkmove.cpp node.cpp ai.cpp

main: log.o main.cpp
	g++ -std=c++0x -Wall -o main main.cpp log.o

clean:
	rm log.o main.o main
