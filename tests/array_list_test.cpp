#include "../array_list.hpp"
#include <iostream>

int main(void) {

  ideaeclipse_utils::array_list<int> array(2);

  array.push(2);

  array.push(3);

  std::cout << array.get(0) << std::endl;

  std::cout << array.get(1) << std::endl;

  array.push(5);

  std::cout << array.get(2) << std::endl;

  array.set(2, 10);

  std::cout << array.get(2) << std::endl;

  for(int i = 0; i < array.size_int(); i ++) {
    std::cout << array.get(i) << std::endl;
  }

  return 0;
}

