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
  if (t != NULL)
    free(t);
}

// prints tree values using inorder traversal
void print_tree(Node *t, char *tab, int depth) {
  if (depth == 0) {
    cout << "Value = %d" << t->value << endl;
    toString(t->board);
    cout << endl;
  } else {
    cout << endl;
    toString(t->board);
    cout << endl;

    for (int i = 0; i < t->numChildren; i++) {
      tab = strcat(tab, "Child ");
      const char s[2] = {(char) (i+'0'), '\0'};
      tab = strcat(tab, s);
      tab = strcat(tab, "    ");
      print_tree(t->children[i], tab, depth-1);
    }
  }
}

