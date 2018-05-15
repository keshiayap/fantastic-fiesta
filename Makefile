all : main

board.o: board.cpp
	g++ -std=c++0x -Wall -c board.cpp

checkmove.o: checkmove.cpp
	g++ -std=c++0x -Wall -c checkmove.cpp

node.o: node.cpp
	g++ -std=c++0x -Wall -c node.cpp

ai.o: ai.cpp
	g++ -std=c++0x -Wall -c ai.cpp

main.o: main_ai.cpp
	g++ -std=c++0x -Wall -c main_ai.cpp

#main: board.cpp checkmove.cpp node.cpp ai.cpp main_ai.cpp
#	g++ -std=c++0x -Wall board.cpp checkmove.cpp node.cpp ai.cpp main_ai.cpp

main: board.o checkmove.o  node.o ai.o main_ai.o
	g++ -std=c++0x -Wall -o main board.o checkmove.o  node.o ai.o main_ai.o

clean:
	rm *.o main
