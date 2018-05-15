all : main board.o

board.o: board.cpp
	g++ -std=c++0x -Wall -c board.cpp

checkmove.o: checkmove.cpp
	g++ -std=c++0x -Wall -c checkmove.cpp

node.o: node.cpp
	g++ -std=c++0x -Wall -c node.cpp

ai.o: ai.cpp
	g++ -std=c++0x -Wall -c ai.cpp


log.o: board.cpp checkmove.cpp node.cpp ai.cpp
	g++ -std=c++0x -Wall -c board.cpp checkmove.cpp node.cpp ai.cpp

main: log.o main.cpp
	g++ -std=c++0x -Wall -o main main.cpp log.o

clean:
	rm log.o main.o main
