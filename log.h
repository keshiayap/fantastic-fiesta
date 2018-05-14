#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <memory>
//#include <QDebug>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <random>
#include <limits.h>

using namespace std;
#define C 1
#define U 0

typedef struct coordinate {
  int row;
  int col;
} coordinate;

typedef struct Board {
  static int COMPUTER, USER; // # of pieces at start of a game
  static char board[8][8];
} Board;
  
// board functions
Board init_board(int COMPUTER = 12*3, int USER = 12*3); // construct new board
void updateBoard(Board board, coordinate current, coordinate next, char turn, bool jump);
void flip(Board board); // reverse direction (change turn)
void toString(Board board); // print to stdout
Board copyBoard(Board board); // duplicate

// node structure for tree
typedef struct Node {
  Board board;
  struct Node **children; // array of either pieces that can jump (preferred), or just move
  coordinate *bestMove;
  int numChildren;
  int alpha;
  int beta;
  int value; // # pieces: COMPUTER - USER;
} Node;

// move functions
void check_null(void *ptr, char const *msg);
coordinate init(int a, int b);
coordinate *buildMove(int r1, int c1, int r2, int c2);
bool canMove(int player, int r1, int c1, int r2, int c2);
bool canJump(int player, int r1, int c1, int r2, int c2);
coordinate **getMoves(int player);
coordinate **getJumps(int player);

// node functions
Node init_node(); // initialize tree node
void free_tree(Node *t); // free mallocs
void print_tree(Node *t); // prints tree using preorder traversal (for checking)

// intelligence functions
int size(coordinate **list);
bool isEmpty(coordinate **list);
coordinate *makeRandomMove(Board board, char player);
Node *buildTree(Board board, coordinate *move, int depth, char player, bool jump);
int minimax(Node *t, int depth, bool isMaximizingPlayer, int alpha, int beta, coordinate *bestMove);

#endif
