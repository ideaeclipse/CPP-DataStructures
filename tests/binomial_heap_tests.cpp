#include "../binomial_heap.hpp"

#include <iostream>

using binomial_heap = ideaeclipse_utils::binomial_heap<std::string>;

int main(void) {
  binomial_heap heap;
  binomial_heap heap_2;

  for(int i = 0; i < 100; i ++) {
    heap.insert(std::to_string(i) + ":" + "heap", i);
    heap_2.insert(std::to_string(i + 1) + ":" + "heap_2", i + 1);
  }

	std::cout << "Heap 1" << std::endl;

  heap.print();

	std::cout << "heap 2" << std::endl;

	heap_2.print();

	heap.merge(heap_2);

	std::cout << "union" << std::endl;
	heap.print();

	for(int i = 0; i < 10; i ++){
		std::cout << heap.extract_max() << std::endl;
		//heap.print();
	}

  return 0;
}
