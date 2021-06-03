#include <algorithm>

#include "board.h"

Board::Board(int h, int w) : _h(h), _w(w), cur_x(0), cur_y(0) {
  board_array = std::unique_ptr<Array2D>(new Array2D(h, w));
}

Board::~Board() {}

bool Board::IsFree(int row, int col) { return board_array->at(row, col) == 0; }

/*
 * Update board state with tetromino
 */
void Board::UpdateBoard(Tetro *tetro) {
  int pos_x, pos_y;
  tetro->GetPos(pos_x, pos_y);
  for (int r = -2; r <= 2; r++) {
    for (int c = -2; c <= 2; c++) {
      if (!tetro->IsFree(r, c)) {
        if ((r + pos_y) < _h && (c + pos_x) < _w && (r + pos_y) >= 0 &&
            (c + pos_x) >= 0) {
          board_array->at(r + pos_y, c + pos_x) = 1;
        }
      }
    }
  }
}

/*
 * Check if there's a unit and clear the line if needed
 */
int Board::CheckUnite(int py) {
  int score = 0;
  for (int r = -2; r <= 2; r++) {
    if ((py + r) < 0 || (py + r) >= _h) {
      continue;
    }
    bool is_full = true;
    for (int c = 0; c < _w; c++) {
      if (IsFree(py + r, c)) {
        is_full = false;
        break;
      }
    }
    if (is_full) {
      score += 1;
      // Move the blocks down
      for (int n = py + r; n > 1; n--) {
        for (int c = 0; c < _w; c++) {
          board_array->at(n, c) = board_array->at(n - 1, c);
        }
      }
    }
  }
  return score;
}
