// main file for intelligence

#include "log.h"

Node *buildTree(Board board, coordinate *move, int depth, char player) {
  Node *t = init_node();
  // update board with relevant moves

  // leaf, so return 
  if (depth == 0)
    t->value = (t->COMPUTER) - (t->USER);
  else {
    coordinate **list = getJumps(player); // jumps only if possible
    bool jump = true;
    if (isEmpty(list)) { // no possible jumps
      list = getMoves(player);
      jump = false;
    } 
    if (isEmpty(list)) // check if there are still no possible  moves
      return NULL; // skip turn

    for (int i = 0; i < board->numChildren; i++) {
      // numChildren should be updated when getMoves or getJumps are called
      Board newBoard = copyBoard(board);
      if (player == 'c')
	player = 'u';
      else
	player = 'c';
      updateBoard(move[0], move[1], player, jump);

      // create child node and add to t->children
    }
  } 
}

// return best move 
coordinate *minimax(Node *t, int depth, bool isMaximizingPlayer, int alpha, int beta) {
  if (depth == 0) // return difference in # of pieces
    return t->value;

  int value, bestVal;
  if (isMaximizingPlayer) {
    bestVal = INT_MIN;

    // recur for all children
    for (int i = 0; i < t->numChildren; i++) {
      value = minimax(t->children[i], depth-1, false, alpha, beta);
      best = max(best, val); // return move instead CHANGE
      alpha = max(alpha, best);

      // Alpha Beta Pruning
      if (alpha > beta)
	break;
    }
    return best;
  } else {
    int best = INT_MAX;

    // recur for all children
    for(int i = 0; i < t->numChildren; i++) {
      value = minimax(t->children[i], depth-1, true, alpha, beta);
      best = max(best, val);
      beta = max(beta, best);

      // Alpha Beta Pruning
      if (alpha > beta)
	break;
    }
    return best;
  }
}
