// file to test logic for minimax algorithm and alpha-beta pruning
#include "log.h"

int main() {
  // create board
  static Board *board = init_board();
  static int player = U;   // user starts first
  coordinate *userMove;
  coordinate *compMove;
  Node *tree;
  int DEPTH = 3;
  
  // Gameplay
  while (player != 0) {
    if (player == U) {
      // user makes random move
      userMove = makeRandomMove(board, player);

      // if there is no available move, skip turn
      if (userMove != NULL)
	updateBoard(board, userMove[0], userMove[1], player);
    }
    else {
      // computer follows using minimax algorithm
      tree = buildTree(board, DEPTH, player);
      compMove = tree->bestMove;

      // if there is no available move, skip turn
      if (compMove != NULL)
	updateBoard(board, compMove[0], compMove[1], player);
    }

    // find if anyone won, return score and exit game
    if (board->USER == 0) {
      player = 0;
      cout << "You lose :(" << endl;
      exit(0);
    }
    if (board->COMPUTER == 0) {
      player = 0;
      cout << "You win! Pieces remaining: %d" << board->USER << endl;
    }
  }
  
  return 0;
}
