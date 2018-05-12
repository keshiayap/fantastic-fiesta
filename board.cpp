#include "log.h"

void Board::updateBoard(coordinate curr, coordinate next, char turn, bool jump) {
  // must check if turn is legit first somewhere else
  if (jump) {
    int enemyR = (curr.row + next.row)/2;
    int enemyC = (curr.col + next.col)/2;
    this -> board[enemyR][enemyC] = '-'; // die
    if (turn == 'C')
      this->COMPUTER--;
    else
      this->USER--;
  }
  this -> board[next.row][next.col] = turn;
  this -> board[curr.row][curr.col] = '-';
}

// reverse direction (change turn)
void Board::flip() {
  char tempBoard[4][8];
  // flip and copy top half of board to temp
  for (int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++)
      tempBoard[i][j] = this->board[3-i][7-j];
  }

  // flip and copy bottom half of board to top half
  for (int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++)
      this->board[i][j] = this->board[7-i][7-j];
  }
  
  // copy temp back to bottom half of board
  for (int i = 4; i < 8; i++) {
    for(int j = 0; j < 8; j++)
      this->board[i][j] = tempBoard[i-4][j-4];
  }
}

// construct new board, computer starts first
Board::Board() {
  this->COMPUTER = 12;
  this->USER = 12;
  
  // initialize all as '-'
  for (int i = 0; i < 8; i++) { 
    for(int j = 0; j < 8; j++) 
      this->board[i][j] = '-';
  }

  // initialize user pieces
  bool skip = true;
  for (int i = 0; i < 3; i++) { 
    for(int j = 0; j < 8; j++) {
      if (!skip) {
	this->board[i][j] = 'c';
	//add coordinate to userList
      }
      skip = !skip;
    }
    skip = !skip;
  }

  // initialize computer pieces
  skip = false;
  for (int i = 5; i < 8; i++) { 
    for(int j = 0; j < 8; j++) {
      if (!skip) {
	this->board[i][j] = 'u';
	//add coordinate to compList
      }
      skip = !skip;
    }
    skip = !skip;
  }
}

// print to stdout
void Board::toString() {
  for (int i=0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << this->board[i][j];
    }
    cout << endl;
  }
}

int main() {
  Board board;
  board.toString();
  return 0;
}
