#include "log.h"

// initialize tree node with children
Node *init_node(Board *board) {
  Node *n = (Node *) malloc(sizeof(Node *));
  check_null(n, "Unable to allocate node");
  n->board = board;
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
    free(t->list);
    free(t);
  }

}

// prints tree values using inorder traversal
void print_tree(Node *t, int tab, int depth) {
  if (depth == 0) {
    cout << "Value = %d" << t->value << endl;
    toString(t->board);
    cout << endl;
  } else {
    cout << endl;
    toString(t->board);
    cout << endl;

    for (int i = 0; i < t->numChildren; i++) {
      for (int j = 0; j < tab; i++)
	cout << " ";
      cout << endl;
      print_tree(t->children[i], tab + 4, depth-1);
    }
  }
}

