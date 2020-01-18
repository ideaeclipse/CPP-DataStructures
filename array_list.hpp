#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <utility>

namespace ideaeclipse_utils {

/*
 * This class is used for a dynamic primitive array.
 *
 * Runtime Per functions (n is size of data added to the array by the user):
 *
 * get: O(1)
 *
 * push / set: O(1) (if load factor is not hit)
 *
 * push / set: O(n) (if the load factor is hit)
 *
 * member: O(n) (TODO: Try to get this to logn or better)
 *
 * Space complexity is O(m) where m is the size of the primitive data (Default is 50 you can also send a custom default sizing). If n > m then m will scale.
 *
 * TODO: Custom load factor
 * TODO: Exception Classes
 *
 */
template<typename T>
class array_list {
private:

  /* Default Size, this is the default size of the primitive array */
  const std::size_t default_size = 50;

	/* Default load factor. This represents the percentage of the default array that needs to be filled in order for there to be a copy function called */
  const float default_load_factor = 1.0f;

	/* Load factor, either default_load_factor or user defined*/
  float load_factor;

	/* Primitive array size */
  std::size_t array_size;

	/* Size of user inputs */
  std::size_t dynamic_size;

	/* Primitive array */
  T *data;

	/*
	 * Doubles the primitive array size and copies all the data from the original array to the new array. Then resets the data pointer to the new array
	 */
  void copy() {
    this->array_size *= 2;

    T* new_data = new T[this->array_size]();

    for(int i = 0; i < this->dynamic_size; i ++) new_data[i] = this->data[i];

    delete[] this->data;

    this->data = new_data;
  }

	/*
	 *
	 * @param position
	 * @return true if valid index and false if invalid
	 */
	bool index_check(const std::size_t position){
		return position > 0 && position < this->dynamic_size;
	}

public:

	/* */
  array_list(const std::size_t default_capacity, const float load_factor) : array_size(default_capacity), load_factor(load_factor), data(new T[array_size]()) {}

	/* */
  array_list(const std::size_t default_capacity) : array_list(default_capacity, default_load_factor) {}

	/* */
  array_list() : array_list(default_size, default_load_factor) {}

	/*
	 */
  const T& get(const std::size_t position) {
    if(!this->index_check()) throw "Out of bounds";

    return this->data[position];
  }

	/*
	 */
  void push(const T& data) {
    if(this->dynamic_size >= this->load_factor * this->array_size) this->copy();

    this->data[this->dynamic_size++] = data;
  }

	/*
	 */
  void set(const std::size_t position, const T& data) {
    if(!this->index_check()) throw "Out of bounds";

    this->data[position] = data;
  }

	/*
	 */
  std::size_t size() {
    return this->dynamic_size;
  }

	/*
	 */
  int size_int() {
    return this->dynamic_size;
  }

	/*
	 */
  ~array_list() {
    delete[] this->data;
  }

};
}

#endif
