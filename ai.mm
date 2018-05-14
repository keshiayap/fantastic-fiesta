// main file for intelligence

#include "log.h"

Node *buildTree(Board board, coordinate *move, int depth, char player, bool jump) {
  Node *t = init_node();
 
  if (depth == 0) { // leaf, so update value and return node
    t->value = (t->COMPUTER) - (t->USER);
    return t;
  }
  else {
    // only consider jumps if possible
    coordinate **list = getJumps(player); 
    bool jump = true;
    if (isEmpty(list)) { // no possible jumps
      list = getMoves(player);
      jump = false;
    } 
    if (isEmpty(list)) // if there are still no possible  moves,
      return NULL; // skip turn

    // find how many possible moves there are and create a child node for each
    int numChildren = sizeof(list)/sizeof(*list);
    t->numChildren = numChildren;
    t->children = malloc(sizeof(Node *)*numChildren);
    
    // recur on each possible move - make children nodes
    for (int i = 0; i < numChildren; i++) {
      Board newBoard = copyBoard(board);

      // update player
      if (player == 'c')
	player = 'u';
      else
	player = 'c';

      // update board with relevant moves and set it to this node
      Board newboard = copyBoard(board);
      newboard.updateBoard(move[0], move[1], player, jump);
      
      // create child node and add to t->children
      children[i] = buildTree(newboard, list[i], depth-1, player, jump);
    }
  } 
}

// return best move 
int minimax(Node *t, int depth, bool isMaximizingPlayer, int alpha, int beta, int *bestMove) {
  if (depth == 0) // return difference in # of pieces
    return t->value;

  int value, best;
  if (isMaximizingPlayer) {
    best = MIN;

    // make array of possible values
    int values[numChildren];
    
    // recur for all children
    for (int i = 0; i < t->numChildren; i++) {
      *bestMove = i;
      values[i] = minimax(t->children[i], depth-1, false, alpha, beta, bestMove);
      best = max(best, val);
      t->alpha = max(t->alpha, best);

      // Alpha Beta Pruning
      if (t->alpha > t->beta)
	break;
    }
    return best;
  }
  
  // similar for minimizing player
  else {
    best = MAX;

    // recur for all children
    for (int i = 0; i < t->numChildren; i++) {
      value = minimax(t->children[i], depth-1, true, alpha, beta, bestMove);
      best = min(best, val);
      t->beta = min(t->beta, best);

      // Alpha Beta Pruning
      if (t->alpha > t->beta)
	break;
    }
    return best;
  }
}

int main() {
  
  return 0;
}
