using namespace std;

class Coordinate {
  int row;
  int col;

  int atLeft(); // at left edge
  int atRight(); // at right edge
  int atEnd(); // reached other end of board
}
  
class Board {
  int COMPUTER; int USER; // # of pieces at start of a game
  char board[8][8];

  void updateBoard(Coordinate current, Coordinate next, char turn);
  void flip(); // reverse direction (change turn)
  Board(); // construct new board
  int count(char turn); // count number of C(omputer) or U(ser) pieces left on the board
  void toString(); // print to stdout
  
};

void updateBoard(Coordinate curr, Coordinate next, char turn, bool jump) {
  // must check if turn is legit first somewhere else
  if (jump) {
    int enemyR = (curr->row + next->row)/2;
    int enemyC = (curr->col + next->col)/2;
    this -> board[enemyR][enemyC] = '-'; // die
    if (turn == 'C')
      COMPUTER--;
    else
      USER--;
  }
  this -> board[next->row][next->col] = turn;
  this -> board[curr->row][curr->col] = '-';
}

// reverse direction (change turn)
void flip() {
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
Board() {
  int COMPUTER::12;
  int USER::12;

  // initialize all as '-'
  for (int i = 0; i < 8; i++) { 
    for(int j = 0; j < 8; j++) 
      this->board[i][j] = '-';
  }

  // initialize user pieces
  bool skip = true;
  for (int i = 0; i < 3; i++) { 
    for(int j = 0; j < 8; j++) {
      if (!skip)
	this->board[i][j] = 'U';
      skip = !skip;
    }
    skip = !skip;
  }

  // initialize computer pieces
  bool skip = false;
  for (int i = 5; i < 8; i++) { 
    for(int j = 0; j < 8; j++) {
      if (!skip)
	this->board[i][j] = 'C';
      skip = !skip;
    }
    skip = !skip;
  }
}

// count number of C(omputer) or U(ser) pieces left on the board
int count(char turn) {
  int number = 0;
  for (int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      if (this->board[i][j] = turn)
	number++;
    }
  }
  
}

// print to stdout
void toString() {
  for (int i=0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << this->board[i][j] << endl;
    }
    cout << '\n' << endl;
  }
}
