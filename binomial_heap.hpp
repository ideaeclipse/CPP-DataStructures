#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <unordered_map>

namespace ideaeclipse_utils {
class binomial_heap {
public:

  struct node {
    unsigned int priority;
    unsigned int order;

    node * parent;
    node * child;
    node * sibling;

    node() : parent(nullptr), child(nullptr), sibling(nullptr) {}
  };

  node * head = nullptr;

public:

  void insert(const unsigned int priority) {
    node * _new = new node();

    _new->order = 0;
    _new->priority = priority;

    this->merge(_new);
  }

  /*
   * Cases:
   *
   * Carry Over exists:
   * 	outdated:
   * 		loop until either there is no carry over or the carry over is the same rank as the next tree in the queue.
   * 			conflict with heap tree:
   * 				merge to produce new carry over.
   * 			no-conflict:
   * 				insert carry over at position. Break out of loop. As there can not be a carry over produced.
   * 	not outdated:
   * 		conflict:
   * 			merge the trees at the current order in the heap and in the to_merge forest. Then insert the carry over at that rank in the heap.
   * 		no-conflict:
   * 			conflict with heap:
   * 				merge with heap tree to produce new carry over
   * 			no conflict with heap:
   * 				insert into heap.
   *
   * Carry over doesn't exist:
   * 	conflict:
   * 		merge both the current tree in the heap with the same ordered tree in the forest to merger produces carry over.
   * 	no conflict:
   * 		insert the to_merge tree into the heaps forest.
   *
   *
   */
  void merge(node *to_merge) {

    if(this->head == nullptr) this->head = to_merge;
    else {
      node * current_heap_pos = this->head;
      node * carry_over = nullptr;
      for(node * curr = to_merge; curr != nullptr; curr = curr->sibling) {
        if(carry_over != nullptr) {

        } else {
          if(curr->order == current_heap_pos->order) {
            carry_over = this->_merge(curr, current_heap_pos);
          }else{
						if(curr->order > current_heap_pos->order){
							//TODO: Figure out this case.
						}else{
							
						}
					}
        }
      }
    }
  }

  node* _merge(node *tree1, node *tree2) {
    if(tree1->order != tree2->order) return nullptr;

    if(tree1->priority >= tree2->priority) {
      tree2->sibling = tree1->child;
      tree1->child = tree2;
      tree2->parent = tree1;
      tree1->order++;
      return tree1;
    } else {
      tree1->sibling = tree2->child;
      tree2->child = tree1;
      tree1->parent = tree2;
      tree2->order++;
      return tree2;
    }
  }

  void del(const unsigned int priority) {

  }
};
}

#endif
