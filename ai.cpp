// main file for intelligence

#include "log.h"

int size(coordinate **list) {
  return *(&list + 1) - list;
}

bool isEmpty(coordinate **list) {
  int num = size(list);
  bool isempty = true;
  for (int i = 0; i < num; i++) {
    if (list[i] != NULL)
      isempty = false;
  }
  return isempty;
}

coordinate *makeRandomMove(Board *board, char player) {
  // jumps preferred
  coordinate **list = getJumps(board, player);
  if (isEmpty(list))
    list = getMoves(board, player);
  if (isEmpty(list)) // list of possible moves  still empty
    return (coordinate *) NULL;
  
  int r = rand() % size(list);
  return list[r];
}
    
Node *buildTree(Board *board, int depth, char player) {
  Node *t = init_node(board);
 
  if (depth == 0) { // leaf, so update value and return node
    t->value = (board->COMPUTER) - (board->USER);
    return t;
  }
  else {
    // find list of possible moves; prefer jumps if available
    t->list = getJumps(board, player); 
    if (isEmpty(t->list)) { // no possible jumps
      t->list = getMoves(board, player);
    } 
    if (isEmpty(t->list)) // if there are still no possible  moves,
      return (Node *)  NULL; // skip turn

    // find how many possible moves there are and create a child node for each
    int num = size(t->list);
    t->numChildren = num;
    t->children = (Node **) malloc(sizeof(Node *) * num);
    
    // recur on each possible move - make children nodes
    for (int i = 0; i < num; i++) {
      Board *newboard = copyBoard(board);
      updateBoard(newboard, t->list[i][0], t->list[i][1], player);

      if (tolower(player) == 'c')
	player = 'u';
      else
	player = 'c';
      
      // create child node and add to t->children
      (t->children)[i] = buildTree(newboard, depth-1, -player);
    }
  } 
  return t;
}

// return best move 
int minimax(Node *t, int depth, bool isMaximizingPlayer, int alpha, int beta) {
  if (depth == 0) // return difference in # of pieces
    return t->value;

  int value, best;
  if (isMaximizingPlayer) {
    best = INT_MIN;
    t->alpha = alpha;
    
    // recur for all children
    for (int i = 0; i < t->numChildren; i++) {
      value = minimax(t->children[i], depth-1, false, alpha, beta);
      if (value > best)
	best = value;
      if (best > t->alpha) {
	t->alpha = best;
	t->bestMove = t->list[i]; // child that promises highest return value
      }

      // Alpha Beta Pruning
      if (t->alpha >= t->beta)
	break;
    }
    return best;
  }
  
  // similar for minimizing player, but no need to set bestMove
  else {
    best = INT_MAX;

    // recur for all children
    for (int i = 0; i < t->numChildren; i++) {
      value = minimax(t->children[i], depth-1, true, alpha, beta);
      best = min(best, value);
      t->beta = min(t->beta, best);

      // Alpha Beta Pruning
      if (t->alpha >= t->beta)
	break;
    }
    return best;
  }
}
