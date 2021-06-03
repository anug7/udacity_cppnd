#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>

#include <SDL.h>

#include "board.h"
#include "tetro.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t block_size, const std::size_t board_width, 
           const std::size_t board_height);
  ~Renderer();

  void Render(Board *board, Tetro *tetro, Tetro *ntetro);
  void UpdateWindowTitle(std::string _string);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  void DrawBoard(Board *board);
  void DrawTetro(Tetro *tetro);
  void DrawNextTetro(Tetro *tetro);
  const std::size_t board_width;
  const std::size_t board_height;
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t block_size;
};

#endif
