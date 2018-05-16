#include "log.h"

// create a coordinate with x=a and y=b
coordinate init(int a, int b) {
  coordinate tmp;
  tmp.row = a;
  tmp.col = b;
  return tmp;
}

// create two coordinates, starting position (r1,c1) ending position (r2,c2)
coordinate *buildMove(int r1, int c1, int r2, int c2) {
  coordinate *move = (coordinate *) malloc(sizeof(coordinate) * 2);
  check_null(move, "Unable to allocate move\n");
  move[0] = init(r1, c1);
  move[1] = init(r2, c2);
  return move;
}

// check if player can move from (r1,c1) to (r2,c2)
bool canMove(Board *board, char player, int r1, int c1, int r2, int c2) {
  if (r2 < 0 || r2 >= 8 || c2 < 0 || c2 >= 8) {
        return false;
    }
    if (board->board[r2][c2] != '-') {
        return false; // there is already a pawn at (x2, y2)
    }
    if (player == 'c') {
      if (tolower(board->board[r1][c1]) == 'c' && r2 < r1) {
            return false; // can only move down
        }
        return true;
    }
    else {
      if (tolower(board->board[r1][c1]) == 'u' && r2 > r1) 
	return false;
      return true;
    }
}

// check if player can jump from (r1,c1) to (r2,c2)
bool canJump(Board *board, char player, int r1, int c1, int r2, int c2) {
    int r3 = (r1 + r2)/2; // coordinates of what's in between the jump
    int c3 = (c1 + c2)/2;
    if (r2 < 0 || r2 >= 8 || c2 < 0 || c2 >= 8) {
        return false;
    }
    if (board->board[r2][c2] != '-') {
        return false; // there is already a pawn at (r2, c2)
    }
    if (player == 'c') {
      if (tolower(board->board[r1][c1]) == 'c' && islower(board->board[r1][c1]) && r2 < r1) {
            return false; // can only move down
        }
      if (board->board[r3][c3] != 'u') // if the square in between not H then can't jump
            return false;
        return true;
    }
    else {
      if (tolower(board->board[r1][c1]) == 'u' && islower(board->board[r1][c1]) && r2 > r1) {
            return false;
        }
      if (board->board[r3][c3] != 'c') // if the square in between not C then can't jump
            return false;
        return true;
    }
}

// return all possible moves for a player in an array
coordinate **getMoves(Board *board, char player) {
  // create list of possible moves; there are at most 2 moves for 12 pieces
  coordinate **list = new coordinate*[24];
  for (int i = 0; i < 24; i++)
    list[i] = (coordinate *) NULL;
  int i = 0;

  // loop through the whole board 
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (tolower(board->board[row][col]) == player) {
	if (canMove(board, player, row, col, row+1, col+1)) {
	  list[i] = buildMove(row, col, row+1, col+1);
	  i++;
	}
	if (canMove(board, player, row, col, row+1, col-1)) {
	  list[i] = buildMove(row, col, row+1, col-1);
	  i++;
	}
	if (canMove(board, player, row, col, row-1, col+1)) {
	  list[i] = buildMove(row, col, row-1, col+1);
	  i++;
	}
	if (canMove(board, player, row, col, row-1, col-1)) {
	  list[i] = buildMove(row, col, row-1, col-1);
	  i++;
	}
      }
    }
  }
  return list;
}

// return all possible jumps for a player in an array
coordinate **getJumps(Board *board, char player) {
  // create list of possible moves; there are at most 2 jumps for 12 pieces
  // each piece only allowed to make one jump!
  // create list of possible moves; there are at most 2 moves for 12 pieces
  coordinate **list = new coordinate*[24];
  for (int i = 0; i < 24; i++)
    list[i] = (coordinate *) NULL;
  int i = 0;

    // loop through the whole board to check
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (tolower(board->board[row][col]) == player) {
	if (canJump(board, player, row, col, row+2, col+2)) {
	  list[i] = buildMove(row, col, row+2, col+2);
	  i++;
	}
	if (canJump(board, player, row, col, row+2, col-2)) {
	  list[i] = buildMove(row, col, row+2, col-2);
	  i++;
	}
	if (canJump(board, player, row, col, row-2, col+2)) {
	  list[i] = buildMove(row, col, row-2, col+2);
	  i++;
	}
	if (canJump(board, player, row, col, row-2, col-2)) {
	  list[i] = buildMove(row, col, row-2, col-2);
	  i++;
	}
      }
    }
  }
  return list;
}

void print_move(coordinate* move) {
  cout << "Piece (" << move[0].row << ", "  << move[0].col << ") moved to (" << move[1].row << ", " << move[1].col << ")" << endl;
}
