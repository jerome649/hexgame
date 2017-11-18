#ifndef HEX_NODE_H_
#define HEX_NODE_H_

#include <string>

class HexNode {
public:
  HexNode(int id_i, int id_j);
  ~HexNode();
  int get_id_i();
  int get_id_j();
  int get_id(int axis);
  int get_player();
  void set_player(int p);
  HexNode** get_neighbours();
  int get_neighbours_size();
  void set_neighbours(HexNode** n, int s);
  std::string get_letter();
  void print_details();
private:
  int id_i;
  int id_j;
  int neighbours_size;
  HexNode** neighbours;
  int player;
};

#endif
