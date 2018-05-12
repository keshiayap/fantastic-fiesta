#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <memory>
#include <QDebug>
#define C 1
#define U 0

using namespace std;

class Board {
 public:
  int COMPUTER; int USER; // # of pieces at start of a game
  coordinate compList[12];
  coordinate userList[12];

  char board[8][8];
  void updateBoard(coordinate current, coordinate next, char turn, bool jump);
  void flip(); // reverse direction (change turn)
  Board(); // construct new board
  int count(char turn); // count number of C(omputer) or U(ser) pieces left on\
   the board
     void toString(); // print to stdout

};

// easy tuple to use to find a position on the board
typedef struct coordinate {
  int x;
  int y;
} coordinate;

void check_null(void *ptr, char *msg);
coordinate *init(int a, int b);
coordinate *buildMove(int r1, int c1, int r2, int c2);
bool canMove(int player, int r1, int c1, int r2, int c2);
bool canJump(int player, int r1, int c1, int r2, int c2);
coordinate **getMoves(int player);
coordinate *getJumps(int player);
