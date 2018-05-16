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
    // print current score tally
    cout << endl << "========================" << endl;
    cout << "COMPUTER: " << board->COMPUTER << " vs USER: " << board->USER << endl;
    cout <<  "========================" << endl;

    // player makes move
    if (player == 'u') {
      userMove = makeRandomMove(board, player); // user finds a random move to make
      
      // if there is no available move, skip turn
      if (userMove != NULL) {
  	updateBoard(board, userMove[0], userMove[1], player); // make move

	// print updates
	cout << endl << "User move: ";
	print_move(userMove);
	cout << endl << "Final board: " << endl;
	toString(board, 0);
      } else
	cout << "User has no move. Skip. " << endl;
      
      player = 'c';
    }
    else {
      // computer follows using minimax algorithm
      Board *newboard = copyBoard(board);
      tree = buildTree(newboard, DEPTH, player); // create tree of possible moves
      if (tree != NULL) {       // if there is no available move, skip turn
	minimax(tree, DEPTH, true, INT_MIN, INT_MAX); // find best move
	compMove = tree->bestMove; 
	updateBoard(board, compMove[0], compMove[1], player); // make best move

	// print updates
	cout << endl << "Computer move: ";
	print_move(compMove);
	cout << endl << "Final board: " << endl;
	toString(board, 0);
      
	free_tree(tree);
      }
      else {
	cout << "Computer has no move. Skip. " << endl;
      }
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
