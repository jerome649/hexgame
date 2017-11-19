#include "hex_board.hpp"
#include "hex_node.hpp"

class HexAi {
public:
  HexAi(HexBoard* hex_board, int mc_steps);
  ~HexAi();
  HexNode* best_move(int player);
  HexNode* best_move_thread(int player);
private:
  //int run_mc(HexBoard* hex_board, std::vector<HexNode*>& available_moves, int choice, int player);
  HexBoard* hex_board;
  int mc_steps;
};
