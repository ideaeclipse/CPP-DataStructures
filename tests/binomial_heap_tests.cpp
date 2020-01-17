#include "../binomial_heap.hpp"

#include <iostream>

using node = ideaeclipse_utils::binomial_heap::node;
using binomial_heap = ideaeclipse_utils::binomial_heap;

int main(void) {
  node *tree1 = new node();

  tree1->order = 0;
  tree1->priority = 1;

  /*
  node *child1 = new node();
  child1->parent = tree1;
  tree1->child = child1;
  */

  node *tree2 = new node();
  tree2->order = 0;
  tree2->priority = 2;

  /*
  node *child2 = new node();
  child2->parent = tree2;
  tree2->child = child2;
  */

  printf("Tree1: %p, Tree2: %p\n", tree1, tree2);

  binomial_heap heap;
  heap._merge(tree1, tree2);

  printf("Root: %p, child: %p, childs parent: %p\n", tree2, tree2->child, tree2->child->parent);

  delete tree1;
  delete tree2;

  return 0;
}
