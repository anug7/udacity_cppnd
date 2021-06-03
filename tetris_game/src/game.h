#ifndef GAME_H
#define GAME_H

#include <random>
#include <SDL.h>
#include "controller.h"
#include "renderer.h"
#include "board.h"
#include "tetro.h"

class Game {
 public:
  Game(std::size_t board_width, std::size_t board_height);
  ~Game();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  
 private:
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> randm;
  std::unique_ptr<Board> board;  
  int score{0};
  std::unique_ptr<Tetro> cur_tetro;
  std::unique_ptr<Tetro> next_tetro;
  const size_t board_width;
  const size_t board_height;
  bool IsCollision(Board *board, Tetro *tetro);
  bool IsCollision(Board *board, Tetro *tetro, int x, int y);
  bool IsCollision(Board *board, Tetro *tetro, int rot);
};

#endif
