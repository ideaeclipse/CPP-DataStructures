#include "../binomial_heap.hpp"

#include <iostream>

using node = ideaeclipse_utils::binomial_heap::node;
using binomial_heap = ideaeclipse_utils::binomial_heap;

int main(void) {
  /*
  std::map<unsigned int, node*> forest_one;

  for(int i = 0; i < 6; i ++) forest_one.insert(std::make_pair(i, init_node(i, 1)));

  std::map<unsigned int, node*> forest_two;

  forest_two.insert(std::make_pair(0, init_node(0, 1)));
  //forest_two.insert(std::make_pair(3, init_node(3, 1)));

  binomial_heap heap(forest_two);

  heap.merge(forest_one);

  std::cout << "Trees exist at the following indexes in the heap:" << std::endl;

  for(auto &x: heap.forest) {
  std::cout << x.first << std::endl;
  }
  */

  binomial_heap heap;

  for(int i = 0; i < 100; i ++) {
    heap.insert(i);
  }

  heap.print_trees();

  std::cout << "max priority: " << heap.extract_max() << std::endl;

	heap.print_trees();

	std::cout << "max priority: " << heap.get_max() << std::endl;

	/*
  int arr[] = {2, 5, 6};

  for(int a: arr) {
    std::cout << a << "'th tree" << std::endl;
    node * sixth_tree = heap.forest.at(a);

    while(true) {
      std::cout << sixth_tree->order << ":" << sixth_tree->priority;

      node *siblings = sixth_tree->sibling;

      while(siblings != nullptr) {
        std::cout << " " << siblings->order << ":" << siblings->priority;
        siblings = siblings->sibling;
      }
      std::cout << "\n";

      if(sixth_tree->order == 0) break;
      sixth_tree = sixth_tree->child;
    }

    std::cout << "\n";
		
  }
	*/

  return 0;
}
