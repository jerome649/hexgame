#include "hex_board.hpp"
#include "hex_ai.hpp"
#include <iostream>

int main_unsafe() {
  HexBoard* hex_board = new HexBoard(11);
  hex_board->print();

  HexAi* hex_ai = new HexAi(hex_board, 500);

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
        std::cin >> a >> b;
        can_play = hex_board->can_play(a, b);
      } else {
        HexNode* node = hex_ai->best_move(player);
        a = node->get_id_i();
        b = node->get_id_j();
        can_play = true;
      }
    }

    hex_board->play(a, b, player);
    hex_board->print();
    std::cout << "Checking player " << player << std::endl;
    finish = hex_board->has_win(player);
    std::cout << "Player " << player << " is " << finish << std::endl;
  }

  std::cout << "Player " << player << " is the winner" << std::endl;

  delete hex_ai;
  delete hex_board;
  return 0;
}

int main() {
  try {
    main_unsafe();
    //throw new std::string("jerome");
  } catch (std::string* s) {
    std::cout << "crash" << std::endl;
    std::cout << *s << std::endl;
  } catch (char const * a) {
    std::cout << "crash string" << std::endl;
    std::cout << a << std::endl;
  }
}
