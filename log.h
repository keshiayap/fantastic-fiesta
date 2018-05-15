// contains all declarations

#ifndef LOG_H
#define LOG_H

//#include <QDebug>
#include <iostream>
#include <memory>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <random>
#include <limits.h>

using namespace std;
#define C 1 // computer regular piece
#define CK 2 // computer king piece
#define U -1 // user regular piece
#define UK -2 // user king piece

/* ------------------------------------------ */
/* -----------------STRUCTS------------------ */
/* ------------------------------------------ */

// tuple for finding position on board
typedef struct coordinate {
  int row;
  int col;
} coordinate;

// Board array and total player values
typedef struct Board {
  static int COMPUTER, USER; // # of pieces at start of a game
  static char board[8][8];
} Board;
  
// node structure for minimax tree
typedef struct Node {
  Board board;
  struct Node **children; // array of either pieces that can jump (preferred), or just move
  coordinate **list;
  coordinate *bestMove;
  int numChildren;
  int alpha;
  int beta;
  int value; // diff in # pieces: COMPUTER - USER;
} Node;

/* ------------------------------------------ */
/* ----------------FUNCTIONS----------------- */
/* ------------------------------------------ */

// board.cpp functions
void check_null(void *ptr, char const *msg);
Board *init_board(int COMPUTER = 12*3, int USER = 12*3); // construct new board, default parameters
Board *copyBoard(Board *board); // duplicate
void updateBoard(Board *board, coordinate curr, coordinate next, char player, bool jump);
/* void flip(Board *board); // reverse direction (change turn) */
void toString(Board *board); // print to stdout

// checkmove.cpp move functions
bool isEmpty(void **ptr);
coordinate init(int a, int b);
coordinate *buildMove(int r1, int c1, int r2, int c2);
bool canMove(Board *board, int player, int r1, int c1, int r2, int c2);
bool canJump(Board *board, int player, int r1, int c1, int r2, int c2);
coordinate **getMoves(Board *board, int player);
coordinate **getJumps(Board *board, int player);

// node.cpp functions
Node *init_node(Board *board); // initialize tree node
void free_tree(Node *t); // free mallocs
void print_tree(Node *t, char *tab, int depth); // prints tree using preorder traversal (for checking)

// ai.cpp intelligence functions
int size(coordinate **list);
bool isEmpty(coordinate **list);
coordinate *makeRandomMove(Board board, char player);
Node *buildTree(Board board, coordinate *move, int depth, char player, bool jump);
int minimax(Node *t, int depth, bool isMaximizingPlayer, int alpha, int beta, coordinate *bestMove);

#endif
