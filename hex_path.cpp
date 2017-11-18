#include "hex_path.hpp"
#include <iostream>

HexPath::HexPath(int grid_size)
  : nodes(new HexNode*[grid_size * grid_size]), size(0), grid_size(grid_size) {
    //std::cout << "new HexPath()" << std::endl;
}

HexPath::HexPath(int grid_size, HexNode* node)
  : nodes(new HexNode*[grid_size * grid_size]), size(1), grid_size(grid_size) {
    //std::cout << "new HexPath()" << std::endl;
    this->nodes[0] = node;
}

HexPath::~HexPath() {
  //std::cout << "delete HexPath()" << std::endl;
  delete [] this->nodes;
}

int HexPath::get_size() {
  return this->size;
}

int HexPath::get_score() {
  return this->get_depth() * this->grid_size * this->grid_size + this->size;
}

int HexPath::get_depth() {
  int min = this->grid_size * this->grid_size + 1;
  int max = -1;
  int player = this->nodes[0]->get_player();
  for (int i = 0; i < this->size; i++) {
    int level = this->nodes[i]->get_id(player - 1);
    if (level > max) {
      max = level;
    }
    if (level < min) {
      min = level;
    }
  }
  return max - min + 1;
}

HexNode* HexPath::get_deepest() {
  HexNode* max = NULL;

  int player = this->nodes[0]->get_player();
  for (int i = 0; i < this->size; i++) {
    int level = this->nodes[i]->get_id(player - 1);
    if (max == NULL or level > max->get_id(player - 1)) {
      max = this->nodes[i];
    }
  }

  return max;
}

HexNode** HexPath::get_nodes() {
  return this->nodes;
}

HexNode* HexPath::head() {
  return this->nodes[size - 1];
}

bool HexPath::is_in_path(HexNode* node) {
  int i = 0;
  bool res = false;

  while (!res && i < this->size) {
    if (this->nodes[i]->get_id_i() == node->get_id_i()
        && this->nodes[i]->get_id_j() == node->get_id_j()) {
      res = true;
    }
    i = i + 1;
  }
  return res;
}

HexPath* HexPath::fork(HexNode* node) {
  HexPath* res = new HexPath(this->grid_size);
  res->size = this->size + 1;
  for (int i = 0; i < this->size; i++) {
    res->nodes[i] = this->nodes[i];
  }
  res->nodes[this->size] = node;
  return res;
}

void HexPath::print() {
  std::cout << "[" << this->nodes[0]->get_id_i();
  std::cout << "," << this->nodes[0]->get_id_j() << "]";

  for (int i = 1; i < this->size; i++) {
    std::cout << " -> [" << this->nodes[i]->get_id_i();
    std::cout << "," << this->nodes[i]->get_id_j() << "]";
  }

  std::cout << " depth=" << this->get_depth();

  std::cout << std::endl;
}
