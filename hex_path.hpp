#ifndef HEX_PATH_H_
#define HEX_PATH_H_

#include "hex_node.hpp"

class HexPath {
public:
  HexPath(int grid_size, HexNode* node);
  ~HexPath();
  int get_depth();
  int get_size();
  HexNode* head();
  HexNode** get_nodes();
  bool is_in_path(HexNode* node);
  HexPath* fork(HexNode* node);
  int get_score();
  void print();
  HexNode* get_deepest();
private:
  HexPath(int grid_size);
  HexNode** nodes;
  int size;
  int grid_size;
};

#endif
