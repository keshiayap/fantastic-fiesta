#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <memory>
#include <QDebug>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define C 1
#define U 0

using namespace std;

class Board {
 public:
  int COMPUTER; int USER; // # of pieces at start of a game
  /* coordinate compList[12]; */
  /* coordinate userList[12]; */

  char board[8][8];
  void updateBoard(coordinate current, coordinate next, char turn, bool jump);
  void flip(); // reverse direction (change turn)
  Board(); // construct new board
  int count(char turn); // count number of C(omputer) or U(ser) pieces left on\
   the board
     void toString(); // print to stdout

};

// Board functions
Board::Board();
void Board::updateBoard(coordinate curr, coordinate next, char player, bool jump);
void Board::flip();
void Board::toString();
Board Board::copyBoard(Board board);

// easy tuple to use to find a position on the board
typedef struct coordinate {
  int x;
  int y;
} coordinate;

// move functions
void check_null(void *ptr, char *msg);
coordinate init(int a, int b);
coordinate *buildMove(int r1, int c1, int r2, int c2);
bool canMove(int player, int r1, int c1, int r2, int c2);
bool canJump(int player, int r1, int c1, int r2, int c2);
coordinate **getMoves(int player);
coordinate **getJumps(int player);
coordinate getPiece(coordinate *move);
coordinate getDest(coordinate *move);


// node structure for tree
typedef struct Node {
  Board board;
  struct Node *children; // array of either pieces that can jump (preferred), or just move
  int depth;
  int alpha;
  int beta;
  int value; // # pieces: COMPUTER - USER;
} Node;

Node *init_node(); // initialize tree node
void free_tree(Node *t); // free mallocs
void print_tree(Node *t); // prints tree using preorder traversal (for checking)
