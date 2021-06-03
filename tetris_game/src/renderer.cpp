#include <iostream>
#include <string>

#include "renderer.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t block_size, const std::size_t board_width,
                   const std::size_t board_height)
    : screen_width(screen_width), screen_height(screen_height),
      board_width(board_width), board_height(board_height),
      block_size(block_size) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Tetris Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

/*
 * Render the main board
 */
void Renderer::DrawBoard(Board *brd) {
  SDL_Rect block;
  const int y_off = 40;
  block.w = block_size - 2;
  block.h = block_size - 2;

  for (int i = 0; i < board_height / block_size; i++) {
    for (int j = 0; j < board_width / block_size; j++) {
      if (!brd->IsFree(i, j)) {
        block.x = block_size * j + 1;
        block.y = block_size * i + 1 + y_off;
        SDL_RenderFillRect(sdl_renderer, &block);
      } else {
        int x = block_size * j + block_size / 2;
        int y = block_size * i + block_size / 2 + y_off;
        SDL_RenderDrawPoint(sdl_renderer, x, y);
      }
    }
  }
}

/*
 * Draws the Current Tetromino in motion
 */
void Renderer::DrawTetro(Tetro *tetro) {
  SDL_Rect block;
  const int y_off = 40;
  block.w = block_size - 2;
  block.h = block_size - 2;
  int cur_x = 0;
  int cur_y = 0;
  tetro->GetPos(cur_x, cur_y);
  int clr[3];
  tetro->GetColor(clr);
  SDL_SetRenderDrawColor(sdl_renderer, clr[0], clr[1], clr[2], 0xFF);

  for (int r = -2; r <= 2; r++) {
    for (int c = -2; c <= 2; c++) {
      if (!tetro->IsFree(r, c)) {
        block.x = (block_size * (c + cur_x)) + 1;
        block.y = (block_size * (r + cur_y)) + 1 + y_off;
        SDL_RenderFillRect(sdl_renderer, &block);
      }
    }
  }
}

/*
 * Draws the next tetromino to come
 */
void Renderer::DrawNextTetro(Tetro *tetro) {
  SDL_Rect block;
  const int y_off = 160;
  const int x_off = board_width + 20;
  block.w = block_size * 1.5 - 2;
  block.h = block_size * 1.5 - 2;

  int clr[3];
  tetro->GetColor(clr);
  SDL_SetRenderDrawColor(sdl_renderer, clr[0], clr[1], clr[2], 0xFF);

  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      if (!tetro->IsFree(r - 2, c - 2)) {
        block.x = (block_size * 1.5 * c) + 1 + x_off;
        block.y = (block_size * 1.5 * r) + 1 + y_off;
        SDL_RenderFillRect(sdl_renderer, &block);
      }
    }
  }
}

/*
 * Main render function called from outside
 */
void Renderer::Render(Board *board, Tetro *tetro, Tetro *ntetro) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawLine(sdl_renderer, 2, 2, 2, screen_height - 2);
  SDL_RenderDrawLine(sdl_renderer, 2, screen_height - 2, board_width,
                     screen_height - 2);
  SDL_RenderDrawLine(sdl_renderer, board_width, screen_height - 2, board_width,
                     2);

  DrawBoard(board);
  DrawTetro(tetro);
  DrawNextTetro(ntetro);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

/*
 * Update Title Name of the Windows while game is on
 */
void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Tetris Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

/*
 * Update Title Name of the Windows when game gets over
 */
void Renderer::UpdateWindowTitle(std::string _string) {
  SDL_SetWindowTitle(sdl_window, _string.c_str());
}
