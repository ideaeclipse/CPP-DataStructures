#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <iostream>

namespace ideaeclipse_utils {
/*
 * Max binomial heap implmentation of type T
 *
 * All functions are implemented in logarithmic time.
 * The functionality is the same as a max heap but allows for the union of two heaps.
 */
template<typename T>
class binomial_heap {
private:

  /*
   * Internal data structure for each node within the graph
   */
  struct node {

    // Priority of the node. Higher the priority the sooner it is released from the heap
    const unsigned int priority;

    // Data associated with the node. User defined.
    const T data;

    // Degree of the tree. See the definition of a binomial tree for more info.
    unsigned int order;

    // Parent pointer. If a node is a root node this is null.
    node * parent = nullptr;

    // Child pointer. Points to the left most child.
    node * child = nullptr;

    // Sibling pointer. Points to the child to the right.
    node * sibling = nullptr;

    /*
     * @param priority sets the priority.
     * @param order sets the default order. Should be 0
     */
    node(const int priority, const T &data) : priority(priority), data(data), order(0) {}
  };

  /*
   * Takes the child node. Loops through all siblings and makes a recursive call.
   *
   * @param root frees the tree with a root node.
   */
  void free_tree(node *root) {
    node *child = root->child;
    while(child != nullptr) {
      this->free_tree(child);
      delete child;
      child = child->sibling;
    }
  }

  /*
   * Similiar to free_tree but prints the priority and order
   *
   * @param root root node for the tree
   */
  void print_tree(node *root) {
    if(root == nullptr) return;

    node *child = root->child;
    node *ref = child;
    while(child != nullptr) {
      std::cout << child->priority << ":" << child->order << " ";
      child = child->sibling;
    }
    std::cout << "\n";
    this->print_tree(ref);
  }

  /*
   * Links the trees together.
   *
   * @param tree1 higher priority tree
   * @param tree2 lower priority tree
   */
  void link(node *tree1, node *tree2) {
    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->order++;
  }

  /*
   * Merges two heaps.
   *
   * @param merg heap to merg
   */
  void merge(node *merge) {
    if(this->head == nullptr) {
      this->head = merge;
      return;
    }

    node * curr_heap = this->head;
    node * merge_heap = merge;
    node * new_heap = nullptr;
    node * new_heap_root = nullptr;

    // Set the new_heap to which ever heap starts earlier
    if(curr_heap->order <= merge_heap->order) {
      new_heap = curr_heap;
      curr_heap = curr_heap->sibling;
    } else {
      new_heap = merge_heap;
      merge_heap = merge_heap->sibling;
    }

    new_heap_root = new_heap;

    // Order the list so that the trees of less order are in order from the head to the end.
    while(curr_heap != nullptr && merge_heap != nullptr) {
      if(curr_heap->order <= merge_heap->order) {
        new_heap->sibling = curr_heap;
        curr_heap = curr_heap->sibling;
      } else {
        new_heap->sibling = merge_heap;
        merge_heap = merge_heap->sibling;
      }

      new_heap = new_heap->sibling;
    }


    // Add the remaining trees in the current heap if any.
    if(curr_heap != nullptr) {
      while(curr_heap != nullptr) {
        new_heap->sibling = curr_heap;
        curr_heap = curr_heap->sibling;
        new_heap = new_heap->sibling;
      }
    } else if(merge_heap != nullptr) {
      while(merge_heap != nullptr) {
        new_heap->sibling = merge_heap;
        merge_heap = merge_heap->sibling;
        new_heap = new_heap->sibling;
      }
    }

    // Reset the new_heap to its root node.
    new_heap = new_heap_root;

    node *previous = nullptr;
    node *next = new_heap->sibling;

    while(next != nullptr) {
      // If the two adjacent trees are of the same order then skip
      // If the next three trees are of the same degree then skip
      if((new_heap->order != next->order) || (next->sibling != nullptr && new_heap->order == next->sibling->order)) {
        previous = new_heap;
        new_heap = next;
      } else {

        /*
         * This function merges the two trees based on which one has a higher priority
         * TODO: explain
         */
        if(new_heap->priority >= next->priority) {
          new_heap->sibling = next->sibling;
          this->link(new_heap, next);
        } else {
          if(previous == nullptr) {
            new_heap_root = next;
          } else {
            previous->sibling = next;
          }

          this->link(next, new_heap);
          new_heap = next;
        }
      }
      next = new_heap->sibling;
    }

    this->head = new_heap_root;
  }

  // Head of the heap
  node *head = nullptr;

public:

	/*
	 * @return if head is null then the heap is empty
	 */
	bool is_empty(){
		return this->head == nullptr;
	}

  /*
   * Merges a singleton node with the heap.
   *
   * @param data user data
   * @param priority priority of that data
   */
  void insert(const T &data, const unsigned int priority = 0) {
    this->merge(new node(priority, data));
  }

  /*
   * @param heap heap to merge
   */
  void merge(binomial_heap<T> &heap) {
    this->merge(heap.head);
    heap.head = nullptr;
  }

  /*
   * @param heap heap to merge
   */
  void merge(binomial_heap<T> &&heap) {
    this->merge(heap.head);
    heap.head = nullptr;
  }

  /*
   * @return max element
   */
  const T& get_max() {
    node *max = nullptr;

    node *ref = this->head;

    while(ref != nullptr) {
      if(max == nullptr || ref->priority > max->priority) max = ref;
      ref = ref->sibling;
    }
    return max->data;
  }

  /*
   * Gets the max data and removes it from the heap.
   *
   * @return data from the max node
   */
  const T extract_max() {
    node * max_previous = nullptr;
    node * max_node = nullptr;

    node *ref_previous = nullptr;
    node *ref = this->head;

    /*
     * Find the max node and the node before it.
     */
    while(ref != nullptr) {
      if(max_node == nullptr || ref->priority > max_node->priority) {
        max_node = ref;
        max_previous = ref_previous;
      }

      ref_previous = ref;
      ref = ref->sibling;
    }

    /*
     * If the max_previous exists the set its previous sibling to the next sibling.
     * Else move the head up one sibling
     */
    if(max_previous != nullptr) max_previous->sibling = max_node->sibling;
    else this->head = this->head->sibling;

    T max_data = max_node->data;
    std::size_t number_of_children = max_node->order;

    //Only re-order the children if there are any.
    if(number_of_children > 0) {
      node *children[number_of_children];
      std::size_t counter = 0;
      node *max_child = max_node->child;

      while(max_child != nullptr) {
        max_child->parent = nullptr;
        children[counter++] = max_child;
        max_child = max_child->sibling;
      }

      for(std::size_t i = number_of_children - 1; i > 0; i --) {
        children[i]->sibling = children[i - 1];
      }

      children[0]->sibling = nullptr;

      this->merge(children[number_of_children - 1]);
    }

    delete max_node;

    return max_data;
  }

  /*
   * Prints the entire heap to stdout
   */
  void print() {
    node * ref = this->head;
    while(ref != nullptr) {
      std::cout << ref->priority << ":" << ref->order << std::endl;
      this->print_tree(ref);
      ref = ref->sibling;
    }
  }

  /*
   * Garbage collects all nodes.
   */
  ~binomial_heap() {
    node *root = this->head;
    while(root != nullptr) {
      node *temp = root;
      this->free_tree(temp);
      delete temp;
      root = root->sibling;
    }
  }
};
}

#endif
