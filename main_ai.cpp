// file to test logic for minimax algorithm and alpha-beta pruning
#include "log.h"

int main() {
  // create board
  static Board *board = init_board(12*3, 12*3);
  char player = 'u';   // user starts first
  coordinate *userMove;
  coordinate *compMove;
  Node *tree;
  int DEPTH = 3;

  // Gameplay
  while (player != '-') {
    cout << endl << "========================" << endl;
    cout << "COMPUTER: " << board->COMPUTER << " vs USER: " << board->USER << endl;
    cout <<  "========================" << endl;
    if (player == 'u') {
      // user makes random move
      userMove = makeRandomMove(board, player);
      
      // if there is no available move, skip turn
      if (userMove != NULL)
  	updateBoard(board, userMove[0], userMove[1], player);
      cout << endl << "User move: " << endl << "    ";
      print_move(userMove);
      cout << endl;
      toString(board, 0);
      
      player = 'c';
    }
    else {
      // computer follows using minimax algorithm
      Board *newboard = copyBoard(board);
      tree = buildTree(newboard, DEPTH, player);
      minimax(tree, DEPTH, true, INT_MIN, INT_MAX);
      compMove = tree->bestMove;

      // if there is no available move, skip turn
      if (compMove != NULL)
  	updateBoard(board, compMove[0], compMove[1], player);

      cout << endl << "Computer move: " << endl << "    ";
      print_move(compMove);
      cout << endl;
      toString(board, 0);
      
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
      cout << "You win!" << endl;
    }
  }

  // free stuff
  free(board);
  return 0;
}
