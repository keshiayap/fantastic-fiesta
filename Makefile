all : main

log.o: board.mm checkmove.mm log.h
	g++ -c board.mm checkmove.mm log.h

ai.o: ai.mm log.h
	g++ -c ai.mm log.h

main: ai.o log.o
	g++ -std=c++0x -Wall -o main main ai.o log.o

clean:
	rm *.o main
