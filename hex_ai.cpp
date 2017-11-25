#include "hex_ai.hpp"
#include <algorithm>
#include <random>
#include <iostream>
#include <thread>
#include <chrono>


HexAi::HexAi(HexBoard* hex_board, int mc_steps) : hex_board(hex_board), mc_steps(mc_steps) {

}

HexAi::~HexAi() {

}

int run_mc(HexBoard* hb, std::vector<HexNode*>& available_moves, int choice, int player, int mc_steps) {
  HexNode* choice_node = available_moves[choice];
  hb->play(choice_node->get_id_i(), choice_node->get_id_j(), player);

  int size = available_moves.size();

  int win_count = 0;
  for (int j = 0; j < mc_steps; j++) {
    int moves[size - 1];

    int move_idx = 0;
    for (int k = 0; k < size - 1; k++) {
      if (move_idx == choice) {
        move_idx = move_idx + 1;
      }
      moves[k] = move_idx;
      move_idx = move_idx + 1;
    }

    int seed = 2 * j;
    std::shuffle(moves, moves + (size - 1), std::default_random_engine(seed));

    int p = player;
    for (int l = 0; l < size - 1; l++) {
      p = (p == 2) ? 1 : 2;
      HexNode* hex_node = available_moves[moves[l]];
      hb->play(hex_node->get_id_i(), hex_node->get_id_j(), p);
    }

    bool has_win = hb->has_win(player);
    if (has_win) {
      win_count = win_count + 1;
    }
    for (int l = 0; l < size - 1; l++) {
      HexNode* hex_node = available_moves[moves[l]];
      hb->get_node(hex_node->get_id_i(), hex_node->get_id_j())->set_player(0);
    }
  }

  hb->get_node(choice_node->get_id_i(), choice_node->get_id_j())->set_player(0);
  return win_count;
}


void job(HexBoard* hb, std::vector<int> choices, int player, int mc_steps, int* win_counts) {
  auto start = std::chrono::system_clock::now();

  HexBoard* clone = hb->clone();
  std::vector<HexNode*> available_moves = clone->available_moves();

  for (int i = 0; i < choices.size(); i++) {
    int choice = choices[i];

    int win_count = run_mc(clone, available_moves, choice, player, mc_steps);

    win_counts[choice] = win_count;
  }

  delete clone;
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "thread took: " << elapsed_seconds.count() << " seconds" << " for nb of MC=" << choices.size() << std::endl;
}

HexNode* HexAi::best_move_thread(int player) {
  auto start = std::chrono::system_clock::now();

  std::vector<HexNode*> available_moves = this->hex_board->available_moves();
  int size = available_moves.size();

  std::vector<int> choices_0;
  std::vector<int> choices_1;
  std::vector<int> choices_2;
  std::vector<int> choices_3;

  int* win_counts = new int[size];

  int max_proba = -1;
  HexNode* best_move = NULL;

  for (int choice = 0; choice < size; choice++) {
    int mod = choice % 4;
    if (mod == 0) {
      choices_0.push_back(choice);
    } else if (mod == 1) {
      choices_1.push_back(choice);
    } else if (mod == 2) {
      choices_2.push_back(choice);
    } else if (mod == 3) {
      choices_3.push_back(choice);
    }
  }

  std::thread thread_0(job, this->hex_board, choices_0, player, this->mc_steps, win_counts);
  std::thread thread_1(job, this->hex_board, choices_1, player, this->mc_steps, win_counts);
  std::thread thread_2(job, this->hex_board, choices_2, player, this->mc_steps, win_counts);
  std::thread thread_3(job, this->hex_board, choices_3, player, this->mc_steps, win_counts);

  thread_0.join();
  thread_1.join();
  thread_2.join();
  thread_3.join();

  for (int choice = 0; choice < size; choice++) {
    if (win_counts[choice] > max_proba) {
      max_proba = win_counts[choice];
      best_move = available_moves[choice];
    }
  }

  delete [] win_counts;

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "threaded AI took: " << elapsed_seconds.count() << " seconds" << std::endl;
  return best_move;
}

HexNode* HexAi::best_move(int player) {
  auto start = std::chrono::system_clock::now();

  std::vector<HexNode*> available_moves = this->hex_board->available_moves();

  int max_proba = -1;
  HexNode* best_move = NULL;

  for (int choice = 0; choice < available_moves.size(); choice++) {
    //std::cout << "Progress : " << i << " / " << size << std::endl;

    int win_count = run_mc(this->hex_board, available_moves, choice, player, this->mc_steps);

    if (win_count > max_proba) {
      max_proba = win_count;
      best_move = available_moves[choice];
    }

  }

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cout << "AI took: " << elapsed_seconds.count() << " seconds" << " for nb of MC=" << available_moves.size() << std::endl;
  return best_move;
}
