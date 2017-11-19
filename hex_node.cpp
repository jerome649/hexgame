#include "hex_node.hpp"
#include <iostream>
#include <string>

HexNode::HexNode(int id_i, int id_j) : id_i(id_i), id_j(id_j), player(0) {
  //std::cout << "new HexNode()" << std::endl;
}

HexNode::~HexNode() {
  //std::cout << "delete HexNode()" << std::endl;
  delete [] this->neighbours;
}

void HexNode::set_neighbours(HexNode** n, int s) {
  this->neighbours = n;
  this->neighbours_size = s;
}

int HexNode::get_player() {
  return this->player;
}

void HexNode::set_player(int p) {
  this->player = p;
}

std::string HexNode::get_letter() {
  if (this->player == 1) {
    return "X";
  } else if (this->player == 2) {
    return "O";
  } else {
    return " ";
    //std::string i_s = std::to_string(this->id_i);
    //std::string j_s = std::to_string(this->id_j);
    //return i_s + j_s;
  }
}

int HexNode::get_id_i() {
  return this->id_i;
}

int HexNode::get_id_j() {
  return this->id_j;
}

int HexNode::get_id(int axis) {
  if (axis == 0) {
    return this->get_id_i();
  } else {
    return this->get_id_j();
  }
}

HexNode** HexNode::get_neighbours() {
  return this->neighbours;
}

int HexNode::get_neighbours_size() {
  return this->neighbours_size;
}

void HexNode::print_details() {
  std::cout << "[" << id_i << "," << id_j << "]: ";
  for (int i = 0; i < this->neighbours_size; i++) {
    std::cout << "[" << this->neighbours[i]->id_i;
    std::cout << "," << this->neighbours[i]->id_j << "] ";
  }
  std::cout << std::endl;
}
