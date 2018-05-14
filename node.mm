#include "log.h"

// initialize tree node with children
Node *init_node() {
  Node *n = malloc(sizeof(Node));
  check_null(n, "Unable to allocate node");

  return n;
}

// free mallocs for all nodes in the tree using post-order traversal
void free_tree(Node *t) {
    if (t->left != NULL)
      free_tree(t->left);
    if (t->right != NULL)
      free_tree(t->right);
    if (t != NULL) {
      free(t);
    }
}

// prints tree values using preorder traversal (for checking)
void print_tree(Node *t) {
  if (isLeaf(t))
    printf(" %d ", (t->COMPUTER)-(t->USER));
  else {
    printf("-"); // to check tree for testing
    print_tree(t->left);
    print_tree(t->right);
  }
}
