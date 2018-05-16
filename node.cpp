#include "log.h"

// initialize tree node with children
Node *init_node(Board *board) {
  Node *n = (Node *) malloc(sizeof(Node));
  check_null(n, "Unable to allocate node");
  n->board = board;
  n->bestMove = NULL;

  n->list = NULL;
  n->numChildren = 0;
  n->alpha = INT_MIN;
  n->beta = INT_MAX;
  n->value = (board->COMPUTER)-(board->USER);
  
  return n;
}

// free mallocs for all nodes in the tree using post-order traversal
void free_tree(Node *t) {
  for (int i = 0; i < t->numChildren; i++)
    free_tree(t->children[i]);
  if (t != NULL) {
    free(t->board);
    for (int i = 0; i < t->numChildren; i++) 
      free(t->list[i]);
    delete [] t->list;
    free(t);
  }

}

// prints tree values using inorder traversal
void print_tree(Node *t, int tab, int depth) {
  if (depth == 0) { // is a leaf
    cout << "Value = " << t->value << endl;
    toString(t->board, tab);
    cout << endl;
  }

  else { // not a leaf
    toString(t->board, tab);
    cout << endl;

    for (int i = 0; i < t->numChildren; i++) {
      print_tree(t->children[i], tab *2, depth-1);
    }
  }
}

