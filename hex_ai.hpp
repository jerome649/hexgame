#include "hex_board.hpp"
#include "hex_node.hpp"

class HexAi {
public:
  HexAi(HexBoard* hex_board, int mc_steps);
  ~HexAi();
  HexNode* best_move(int player);

private:
  HexBoard* hex_board;
  int mc_steps;
};
