#include "hex_ai.hpp"
#include <algorithm>
#include <random>
#include <iostream>


HexAi::HexAi(HexBoard* hex_board, int mc_steps) : hex_board(hex_board), mc_steps(mc_steps) {

}

HexAi::~HexAi() {

}

HexNode* HexAi::best_move(int player) {
  std::vector<HexNode*> available_moves = this->hex_board->available_moves();

  int size = available_moves.size();
  int max_proba = -1.0;
  HexNode* best_move = NULL;

  for (int i = 0; i < size; i++) {
    //std::cout << "Progress : " << i << " / " << size << std::endl;
    this->hex_board->play(available_moves[i]->get_id_i(), available_moves[i]->get_id_j(), player);

    int win_count = 0;
    for (int j = 0; j < this->mc_steps; j++) {
      int moves [size - 1];

      int move_idx = 0;
      for (int k = 0; k < size - 1; k++) {
        if (move_idx == i) {
          move_idx = move_idx + 1;
        }
        moves[k] = move_idx;
        move_idx = move_idx + 1;
      }

      int seed = 2 * j;
      std::shuffle(moves, moves + (size - 1), std::default_random_engine(seed));

      //for (int k = 0; k < size - 1; k++) {
      //  std::cout << moves[k] << " ";
      //}

      //std::cout << std::endl;

      int p = player;
      for (int l = 0; l < size - 1; l++) {
        p = (p == 2) ? 1 : 2;
        HexNode* hex_node = available_moves[moves[l]];
        this->hex_board->play(hex_node->get_id_i(), hex_node->get_id_j(), p);
      }

      bool has_win = this->hex_board->has_win(player);
      if (has_win) {
        win_count = win_count + 1;
      }
      for (int l = 0; l < size - 1; l++) {
        HexNode* hex_node = available_moves[moves[l]];
        hex_node->set_player(0);
      }
    }

    //std::cout << "----------------" << std::endl;

    if (win_count > max_proba) {
      max_proba = win_count;
      best_move = available_moves[i];
    }

    this->hex_board->get_node(available_moves[i]->get_id_i(), available_moves[i]->get_id_j())->set_player(0);
  }

  return best_move;
}
