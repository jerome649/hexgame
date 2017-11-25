#include "hex_board.hpp"
#include "hex_ai.hpp"
#include <iostream>

int main_unsafe(int size, int steps) {
  HexBoard* hex_board = new HexBoard(size);
  hex_board->print();

  HexAi hex_ai(hex_board, steps);
  HexAi hex_ai2(hex_board, steps);

  bool finish = false;
  int player = 2;
  while (!finish) {
    player = (player == 2) ? 1 : 2;
    int a;
    int b;
    bool can_play = false;
    std::cout << "Player " << player << " to play" << std::endl;

    while (!can_play) {
      if (player == 1) {
        HexNode* node = hex_ai2.best_move_thread(player);
        HexNode* node2 = hex_ai2.best_move(player);
        std::cout << "AI advise is " << node->get_id_i() << " / " << node->get_id_j() << std::endl;
        std::cin >> a >> b;
        //a = node->get_id_i();
        //b = node->get_id_j();
        can_play = hex_board->can_play(a, b);
      } else {
        HexNode* node = hex_ai.best_move(player);
        a = node->get_id_i();
        b = node->get_id_j();
        can_play = true;
      }
    }

    hex_board->play(a, b, player);
    hex_board->print();
    finish = hex_board->has_win(player);
  }

  std::cout << "Player " << player << " is the winner" << std::endl;

  delete hex_board;
  return 0;
}

int main(int argc, char *argv[]) {
  main_unsafe(std::stoi(argv[1]), std::stoi(argv[2]));
}
