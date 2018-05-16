#include "log.h"

// check if mallocs were done correctly
void check_null(void *ptr, char const *msg) {
  if (ptr == NULL) {
    cerr << "%s\n" << msg;
    exit(EXIT_FAILURE);
  }
}

// construct new board, computer starts first
Board *init_board(int COMPUTER, int USER) {
  // store values of pieces for each player
  // normal pieces worth 3 units, kings worth 5
  Board *board = (Board *) malloc(sizeof(Board));
  check_null(board, "Unable to allocate board\n");

  board->COMPUTER = COMPUTER;
  board->USER = USER;

  // initialize all as '-'
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++)
      board->board[i][j] = '-';
  }
  
  // initialize computer pieces
  bool skip = true;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 8; j++) {
      if (!skip) 
	board->board[i][j] = 'c';
      skip = !skip;
    }
    skip = !skip;
  }
  
  // initialize user pieces
  skip = false;
  for (int i = 5; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (!skip)
	board->board[i][j] = 'u';
      skip = !skip;
    }
    skip = !skip;
  }
  return board;
}


// duplicate board, for children
Board *copyBoard(Board *board) {
  Board *newBoard = init_board(board->COMPUTER, board->USER);

  // copy board array
  for (int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++)
      newBoard->board[i][j] = board->board[i][j];
  }
  return newBoard;
}

// make a legit move
void updateBoard(Board *board, coordinate curr, coordinate next, char player) {
  bool jump = 0;
  if (curr.row - next.row == 1 || curr.row - next.col == -1)
    jump = 1;
  
  // must check if turn is legit first somewhere else
  if (jump) {
    int enemyR = (curr.row + next.row)/2;
    int enemyC = (curr.col + next.col)/2;
    
    int enemyPieceValue = 3; // assume normal piece was destroyed
    if (isupper(board->board[enemyR][enemyC]))
      enemyPieceValue = 5; // king was destroyed
	
    board->board[enemyR][enemyC] = '-'; // die
    if (player < 0) // enemy loses one piece
      board->COMPUTER -= enemyPieceValue;
    else
      board->USER -= enemyPieceValue;
  }
    
  // shift position of piece
  board->board[next.row][next.col] = board->board[curr.row][curr.col];
  board->board[curr.row][curr.col] = '-';

  // make king if they reached the end
  if (next.row == 0 || next.row == 7)
    board->board[next.row][next.col] = toupper(board->board[next.row][next.col]);
}


// print to stdout
void toString(Board *board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) 
      cout << board->board[i][j];
    cout << endl;
  }
}

// // reverse direction (change turn)
// void flip(Board *board) {
//   char tempBoard[4][8];
//   // flip and copy top half of board to temp
//   for (int i = 0; i < 4; i++) {
//     for(int j = 0; j < 8; j++)
//       tempBoard[i][j] = board->board[3-i][7-j];
//   }

//   // flip and copy bottom half of board to top half
//   for (int i = 0; i < 4; i++) {
//     for(int j = 0; j < 8; j++)
//       board->board[i][j] = board->board[7-i][7-j];
//   }
  
//   // copy temp back to bottom half of board
//   for (int i = 4; i < 8; i++) {
//     for(int j = 0; j < 8; j++)
//       board->board[i][j] = tempBoard[i-4][j-4];
//   }
// }
