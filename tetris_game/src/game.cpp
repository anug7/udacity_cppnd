#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t _board_width, std::size_t _board_height)
    : engine(dev()), randm(0, 6), board_width(_board_width),
      board_height(_board_height)

{
  board = std::unique_ptr<Board>(new Board(board_height, board_width));
  cur_tetro = std::unique_ptr<Tetro>(new Tetro(randm(engine)));
  cur_tetro->Move(board_width / 2, 0);
  next_tetro = std::unique_ptr<Tetro>(new Tetro(randm(engine)));
}

Game::~Game() {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  int cur_x = 0;
  int cur_y = 0;
  int x = 0;
  int y = 0;
  int rot = 0;
  bool game_over = false;

  while (running) {
    frame_start = SDL_GetTicks();
    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, x, y, rot);
    if (!game_over) {
      if (!IsCollision(board.get(), cur_tetro.get(), x, y)) {
        cur_tetro->Move(x, y);
      }
      if (rot != 0) {
        IsCollision(board.get(), cur_tetro.get(), rot);
      }
    }
    renderer.Render(board.get(), cur_tetro.get(), next_tetro.get());
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      if (!game_over) {
        renderer.UpdateWindowTitle(score, frame_count);
        cur_tetro->Move(0, 1);
        // Is bottom of the board is reached
        if (IsCollision(board.get(), cur_tetro.get())) {
          cur_tetro->Move(0, -1);
          // Attach tetro to board
          board->UpdateBoard(cur_tetro.get());
          int _px = 0, _py = 0, dx = -2;
          cur_tetro->GetPos(_px, _py);
          // Check if a line is completed
          score += board->CheckUnite(_py);
          cur_tetro = std::move(next_tetro);
          cur_tetro->Move(board_width / 2, 2);
          next_tetro = std::unique_ptr<Tetro>(new Tetro(randm(engine)));
          if (IsCollision(board.get(), cur_tetro.get())) {
            renderer.UpdateWindowTitle(std::string("GameOver"));
            game_over = true;
            dx = -1;
          }
          cur_tetro->Move(0, dx);
        }
      }
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

/*
 * Check if new movement by x & y result in collision
 */
bool Game::IsCollision(Board *board, Tetro *tetro, int x, int y) {
  int pos_x = 0, pos_y = 0;
  tetro->GetPos(pos_x, pos_y);
  pos_x += x;
  pos_y += y;
  for (int r = -2; r <= 2; r++) {
    for (int c = -2; c <= 2; c++) {
      if (!tetro->IsFree(r, c)) {
        if ((pos_x + c) < 0 || (pos_x + c) >= board_width || (pos_y + r) < 0 ||
            (pos_y + r) >= board_height) {
          return true;
        }

        if (!board->IsFree(pos_y + r, pos_x + c)) {
          return true;
        }
      }
    }
  }
  return false;
}

/*
 * check if rotation of shape result in collision
 */
bool Game::IsCollision(Board *board, Tetro *tetro, int rot) {
  int pos_x = 0, pos_y = 0;
  tetro->GetPos(pos_x, pos_y);
  tetro->rot_all = (tetro->rot_all + rot) % 4;
  for (int r = -2; r <= 2; r++) {
    for (int c = -2; c <= 2; c++) {
      if (!tetro->IsFree(tetro->rot_all, r, c)) {
        if ((pos_x + c) < 0 || (pos_x + c) >= board_width || (pos_y + r) < 0 ||
            (pos_y + r) >= board_height) {
          return true;
        }

        if (!board->IsFree(pos_y + r, pos_x + c)) {
          return true;
        }
      }
    }
  }
  tetro->UpdateRotate(tetro->rot_all);
  return false;
}

/*
 * Check if current tetro results in collision
 * done at the end to decide new tetro or end of
 * board
 */
bool Game::IsCollision(Board *board, Tetro *tetro) {
  int pos_x = 0, pos_y = 0;
  tetro->GetPos(pos_x, pos_y);
  for (int r = -2; r <= 2; r++) {
    for (int c = -2; c <= 2; c++) {
      if (!tetro->IsFree(r, c)) {
        if ((pos_x + c) < 0 || (pos_x + c) >= board_width || (pos_y + r) < 0 ||
            (pos_y + r) >= board_height) {
          return true;
        }
        if (!board->IsFree(pos_y + r, pos_x + c))
          return true;
      }
    }
  }
  return false;
}

int Game::GetScore() const { return score; }
