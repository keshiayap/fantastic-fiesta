// file to test logic for minimax algorithm and alpha-beta pruning
#include "log.h"

int main() {
  // create board
  static Board *board = init_board();
  char player = 'u';   // user starts first
  coordinate *userMove;
  coordinate *compMove;
  Node *tree;
  int DEPTH = 3;

  // Gameplay
  while (player != '-') {
    if (player == 'u') {
      // user makes random move
      userMove = makeRandomMove(board, player);
      cout << endl << "User move: " << endl << "    ";
      print_move(userMove);
      toString(board, 0);
      
      // if there is no available move, skip turn
      if (userMove != NULL)
  	updateBoard(board, userMove[0], userMove[1], player);

      player = 'c';
    }
    else {
      // computer follows using minimax algorithm
      Board *newboard = copyBoard(board);
      tree = buildTree(newboard, DEPTH, player);
      minimax(tree, DEPTH, true, INT_MIN, INT_MAX);
      compMove = tree->bestMove;
      cout << endl << "Computer move: " << endl << "    ";
      print_move(compMove);
      toString(board, 0);
      
      // if there is no available move, skip turn
      if (compMove != NULL)
  	updateBoard(board, compMove[0], compMove[1], player);

      free_tree(tree);
      player = 'u';
    }
    
    // find if anyone won, return score and exit game
    if (board->USER == 0) {
      player = '-';
      cout << "You lose :(" << endl;
      exit(0);
    }
    if (board->COMPUTER == 0) {
      player = '-';
      cout << "You win! Pieces remaining: %d" << board->USER << endl;
    }
  }

  // free stuff
  free(board);
  return 0;
}
