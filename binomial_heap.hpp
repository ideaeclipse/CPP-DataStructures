#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <map>
#include <iostream>

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

  std::map<unsigned int, node*> forest;

public:

  binomial_heap() {}

  binomial_heap(const std::map<unsigned int, node*> &pre_set) : forest(pre_set) {}

  void insert(const unsigned int priority) {
    node *_new = new node();

    _new->order = 0;
    _new->priority = priority;

    std::map<unsigned int, node*> new_map;
    new_map.insert(std::make_pair(0, _new));

    this->merge(new_map);
  }


  void merge(const std::map<unsigned int, node*> &to_merge) {
    std::pair<unsigned int, node*> carry_over_pair = this->_make_null_pair();

    for(auto &pair: to_merge) {
      const unsigned int current_order = pair.first;
      node *current_tree = pair.second;

      std::cout << "Current order: " << current_order << std::endl;

      if(carry_over_pair.second == nullptr) {

        std::cout << "No carry over" << std::endl;

        if(this->forest.count(current_order)) { // collision has occured and thus we merged the two trees and set carry over to their product
          std::cout << "Merge" << std::endl;

          node *co = this->_merge(this->forest.at(current_order), current_tree);
          this->forest.erase(current_order);
          carry_over_pair.first = current_order + 1;
          carry_over_pair.second = co;
        } else { // No carry over and no collision thus you can freely insert into the tree
          std::cout << "Insert" << std::endl;
          this->forest.insert(std::make_pair(current_order, current_tree));
        }
      } else { // Carr over exists.

        std::cout << "Carry over exists" << std::endl;

        unsigned int carry_over_order = carry_over_pair.first;
        node * carry_over_tree = carry_over_pair.second;

        bool finished = false;

        if(carry_over_order < current_order) std::cout << "Outdated" << std::endl;

        // Loop through all the bounds between the carry_over and the current tree.
        // Either merge them together into a new carry over if there is a conflict
        // or insert it and break the loop.
        while(carry_over_order < current_order) {
          if(this->forest.count(carry_over_order)) {
            std::cout << "Merge at order: " << carry_over_order << std::endl;
            carry_over_tree = this->_merge(carry_over_tree, this->forest.at(carry_over_order));
            this->forest.erase(carry_over_order);
            carry_over_order += 1;
          } else {
            std::cout << "Insert" << std::endl;
            this->forest.insert(std::make_pair(carry_over_order, carry_over_tree));
            carry_over_pair = this->_make_null_pair();
            finished = true;
            break;
          }
        }

        // If finished is true we need to continue the outer loop
        if(finished) continue;
        else if(carry_over_order == current_order) { // Just ensures that they are the same. They should always be the same
          std::cout << "Carry over is up to date with current_order of: " << current_order << std::endl;
          if(this->forest.count(current_order)) {
            std::cout << "Merge current and tree in forest" << std::endl;
            node *new_merge = this->_merge(current_tree, this->forest.at(current_order));
            this->forest.insert(std::make_pair(current_order, carry_over_tree));
            carry_over_pair.first = current_order + 1;
            carry_over_pair.second = new_merge;
          } else {
            std::cout << "Merge carry with current" << std::endl;
            carry_over_pair.first = current_order + 1;
            carry_over_pair.second = this->_merge(current_tree, carry_over_tree);
          }
        } else {
          std::cout << "This shouldn't occur" << std::endl;
        }
      }
    }

    if(carry_over_pair.second != nullptr) {

      std::cout << "Carry over exists after all to_merged trees after been looked after" << std::endl;

      unsigned int carry_over_order = carry_over_pair.first;
      node * carry_over_tree = carry_over_pair.second;

      while(true) {
        if(this->forest.count(carry_over_order)) {
          carry_over_tree = this->_merge(this->forest.at(carry_over_order), carry_over_tree);
          this->forest.erase(carry_over_order);
          carry_over_order += 1;
        } else {
          this->forest.insert(std::make_pair(carry_over_order, carry_over_tree));
          break;
        }
      }

    }
  }

  std::pair<unsigned int, node *> _make_null_pair() {
    return std::make_pair(-1, nullptr);
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

  int get_max() {
    unsigned int max_priority = 0;
    for(auto &x: this->forest) if(x.second->priority > max_priority) max_priority = x.second->priority;
    return max_priority;
  }

	int extract_max(){
		node * max_node = nullptr;
		for(auto &x: this->forest){
			if(max_node == nullptr) max_node = x.second;
			else if(x.second->priority > max_node->priority) max_node = x.second;
		}

		int max = max_node->priority;

		std::map<unsigned int, node*> new_map;

		node * child = max_node->child;

		while(child != nullptr){
			child->parent = nullptr;
			new_map.insert(std::make_pair(child->order, child));
			child = child->sibling;
		}	

		this->forest.erase(max_node->order);

		delete max_node;	

		this->merge(new_map);

		return max;

	}

  void print_trees() {
    for(auto &x : this->forest) std::cout << x.first << std::endl;
  }

  ~binomial_heap() {
    std::cout << "Delete" << std::endl;

    for(auto &x: this->forest) delete x.second;
  }
};
}

#endif
