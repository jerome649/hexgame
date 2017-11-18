#include "hex_board.hpp"
#include <iostream>
#include <vector>
#include <stack>

HexBoard::HexBoard(int size) : size(size), nodes(new HexNode**[size]) {
  std::cout << "new HexBoard()" << std::endl;
  for (int i = 0; i < this->size; i++) {
    this->nodes[i] = new HexNode*[size];
    for (int j = 0; j < this->size; j++) {
      this->nodes[i][j] = new HexNode(i, j);
    }
  }
  this->fill_neighbours();
}

HexBoard* HexBoard::clone() {
  HexBoard* hex_board = new HexBoard(this->size);

  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      hex_board->play(i, j, this->get_node(i, j)->get_player());
    }
  }

  return hex_board;
}

void HexBoard::fill_neighbours() {
  int moves_i[6] = {+0, +0, -1, -1, +1, +1};
  int moves_j[6] = {-1, +1, +0, +1, -1, +0};

  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      std::vector<HexNode*> v;
      int ni, nj;

      for (int l = 0; l < 6; l++) {
        ni = i + moves_i[l];
        nj = j + moves_j[l];
        if (this->in_board(ni, nj)) {
          v.push_back(this->nodes[ni][nj]);
        }
      }

      int s = v.size();
      HexNode** res = new HexNode*[s];
      for (int k = 0; k < s; k++) {
        res[k] = v[k];
      }
      this->nodes[i][j]->set_neighbours(res, s);
    }
  }
}

int HexBoard::get_size() {
  return this->size;
}

HexNode* HexBoard::get_node(int i, int j) {
  return this->nodes[i][j];
}

bool HexBoard::can_play(int i, int j) {
  return this->in_board(i, j) && this->nodes[i][j]->get_player() == 0;
}

void HexBoard::play(int i, int j, int p) {
  if (this->can_play(i, j)) {
    this->nodes[i][j]->set_player(p);
  }
}

bool HexBoard::in_board(int i, int j) {
  return 0 <= i && i < this->size && 0 <= j && j < this->size;
}

HexBoard::~HexBoard() {
  std::cout << "delete HexBoard()" << std::endl;
  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      delete this->nodes[i][j];
    }
    delete [] this->nodes[i];
  }
  delete [] this->nodes;
}

std::vector<HexNode*> HexBoard::available_moves() {
  std::vector<HexNode*> v;

  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      if (this->can_play(i, j)) {
        v.push_back(this->get_node(i, j));
      }
    }
  }

  return v;
}

void HexBoard::print() {
  std::string head1 = " /\\ ";
  std::string head2 = "/  \\";
  std::string bottom1 = "\\  /";
  std::string bottom2 = " \\/ ";
  std::cout << "  ";
  for (int i = 0; i < this->size; i++) {
    std::cout << i << "   ";
  }
  std::cout << std::endl << " ";
  for (int i = 0; i < this->size; i++) {
    std::cout << head1;
  }
  std::cout << std::endl << " ";
  for (int i = 0; i < this->size; i++) {
    std::cout << head2;
  }
  std::string blanks = "";
  std::cout << std::endl;
  for (int line = 0; line < this->size; line++) {
    std::cout << line << blanks << "|";
    for (int i = 1; i < this->size + 1; i++) {
      std::cout << " " << this->nodes[line][i-1]->get_letter() << " |";
    }
    std::cout << std::endl << blanks << " ";
    for (int i = 0; i < this->size; i++) {
      std::cout << bottom1;
    }
    if (line < this->size - 1) {
      std::cout << "\\";
    }
    std::cout << std::endl << blanks << " ";
    for (int i = 0; i < this->size; i++) {
      std::cout << bottom2;
    }
    if (line < this->size - 1) {
      std::cout << " \\";
    }
    std::cout << std::endl;
    blanks = blanks + " ";
  }
}

void HexBoard::print_details() {
  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      this->nodes[i][j]->print_details();
    }
  }
}

bool HexBoard::has_win(int p) {
  bool visited[this->size][this->size];
  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      visited[i][j] = false;
    }
  }

  std::stack<HexNode*> to_visit;

  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      if (this->nodes[i][j]->get_player() == p && this->nodes[i][j]->get_id(p - 1) == 0) {
        to_visit.push(this->nodes[i][j]);
      }
    }
  }

  bool has_win = false;
  bool finish = false;

  while (!finish && !to_visit.empty()) {
    HexNode* node = to_visit.top();
    to_visit.pop();
    visited[node->get_id_i()][node->get_id_j()] = true;
    if (node->get_id(p - 1) == (this->size - 1)) {
      finish = true;
      has_win = true;
    } else {
      for (int i = 0; i < node->get_neighbours_size(); i++) {
        HexNode* neighbour = node->get_neighbours()[i];
        if (neighbour->get_player() == p && !visited[neighbour->get_id_i()][neighbour->get_id_j()]) {
          to_visit.push(neighbour);
        }
      }
    }
  }

  return has_win;
}
