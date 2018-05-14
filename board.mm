#include "log.h"

// construct new board, computer starts first
Board::Board() {
  // store values of pieces for each player
  // normal pieces worth 3 units, kings worth 5
  this->COMPUTER = 12 * 3;
  this->USER = 12 * 3;
  
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

// duplicate board, for children
Board Board::copyBoard(Board board) {
  Board newBoard = malloc(sizeof(Board));
  check_null(newBoard, "Unable to allocate board");
  newBoard->COMPUTER = board->COMPUTER;
  newBoard->USER = board->USER;

  // copy board array
  for (int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++)
      newBoard->board[i][j] = board->board[i][j];
  }
}
  
  
// make a legit move
void Board::updateBoard(coordinate curr, coordinate next, char player, bool jump) {
  // must check if turn is legit first somewhere else
  if (jump) {
    int enemyR = (curr.row + next.row)/2;
    int enemyC = (curr.col + next.col)/2;
    
    int enemyPieceValue = 3; // assume normal piece was destroyed
    if (isupper(board[enemyR][enemyC])
	enemyPieceValue = 5; // king was destroyed
	
    this -> board[enemyR][enemyC] = '-'; // die
    if (tolower(player) == 'u') // enemy loses one piece
      this->COMPUTER-enemyPieceValue;
    else
      this->USER-enemyPieceValue;
  }
    
  // shift position of piece
  this -> board[next.row][next.col] = this->board[curr.row][curr.col];
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
