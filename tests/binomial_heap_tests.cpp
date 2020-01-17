#include "../binomial_heap.hpp"

#include <iostream>

using node = ideaeclipse_utils::binomial_heap::node;
using binomial_heap = ideaeclipse_utils::binomial_heap;

node * init_node(const unsigned int order, const unsigned int priority) {
  node *_new = new node();

  _new->order = order;
  _new->priority = priority;

  return _new;
}

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

	for(int i = 0; i < 100; i ++){
		heap.insert(i);
	}

	heap.print_trees();

	std::cout << "max priority: " << heap.get_max_priority() << std::endl;

	node * sixth_tree = heap.forest.at(6);

	while(sixth_tree != nullptr){
		std::cout << sixth_tree->order << ":" << sixth_tree->priority << std::endl;
		sixth_tree = sixth_tree->child;
	}

  return 0;
}
