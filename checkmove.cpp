#include "log.h"

bool isEmpty(void **ptr) {
  int num = *(&ptr + 1) - ptr;
  bool isempty = true;
  for (int i = 0; i < num; i++) {
    if (ptr[i] != NULL)
      isempty = false;
  }
  return isempty;
}
    
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
bool canMove(Board *board, int player, int r1, int c1, int r2, int c2) {
    if (r2 < 0 || r2 >= 8 || c2 < 0 || c2 >= 8) {
        return false;
    }
    if (board->board[r2][c2] != '-') {
        return false; // there is already a pawn at (x2, y2)
    }
    if (player == C) {
        if (board->board[r1][c1] == C && r2 > r1) {
            return false; // can only move down
        }
        return true;
    }
    else {
        if (board->board[r1][c1] == U && r2 < r1) {
            return false;
        }
        return true;
    }
}

// check if player can jump from (r1,c1) to (r2,c2)
bool canJump(Board *board, int player, int r1, int c1, int r2, int c2) {
    int r3 = (r1 + r2)/2; // coordinates of what's in between the jump
    int c3 = (c1 + c2)/2;
    if (r2 < 0 || r2 >= 8 || c2 < 0 || c2 >= 8) {
        return false;
    }
    if (board->board[r2][c2] != '-') {
        return false; // there is already a pawn at (r2, c2)
    }
    if (player == C) {
        if (board->board[r1][c1] == C && r2 > r1) {
            return false; // can only move down
        }
        if (board->board[r3][c3] != U) // if the square in between not H then can't jump
            return false;
        return true;
    }
    else {
        if (board->board[r1][c1] == U && r2 < r1) {
            return false;
        }
        if (board->board[r3][c3] != C) // if the square in between not C then can't jump
            return false;
        return true;
    }
}

// return all possible moves for a player in an array
coordinate **getMoves(Board *board, int player) {
  // create list of possible moves; there are at most 2 moves for 12 pieces
  coordinate **list = (coordinate **) malloc(sizeof(coordinate *)*12*2);
  check_null(list, "Unable to allocate list for getMoves()");
  memset(list, (int) NULL, sizeof(coordinate *)*12*2);
  int i = 0;

  // loop through the whole board 
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (board->board[row][col] == player) {
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
coordinate **getJumps(Board *board, int player) {
  // create list of possible moves; there are at most 2 jumps for 12 pieces
  // each piece only allowed to make one jump!
  coordinate **list = (coordinate **) malloc(sizeof(coordinate *)*12*2);
  check_null(list, "Unable to allocate list for getJumps()");
  memset(list, (int) NULL, sizeof(coordinate *)*12*2);
  int i = 0;

  // loop through the whole board to check
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if (board->board[row][col] == player) {
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
