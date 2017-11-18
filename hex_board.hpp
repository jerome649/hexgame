#ifndef HEX_BOARD_H_
#define HEX_BOARD_H_

#include "hex_node.hpp"
#include "hex_path.hpp"

class HexBoard {
public:
  HexBoard(int size);
  ~HexBoard();
  bool can_play(int i, int j);
  void play(int i, int j, int p);
  void print();
  void print_details();
  bool has_win(int p);
  HexNode* get_node(int i, int j);
  int get_size();
  HexBoard* clone();
  std::vector<HexNode*> available_moves();
private:
  bool in_board(int i, int j);
  void fill_neighbours();
  int size;
  HexNode*** nodes;
};

#endif
