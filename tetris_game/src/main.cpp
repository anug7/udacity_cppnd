#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kBoardWidth{kScreenWidth - 280};
  constexpr std::size_t kBoardHeight{kScreenHeight - 40};
  constexpr std::size_t kBlockSize{30};

  Renderer renderer(kScreenWidth, kScreenHeight, kBlockSize, kBoardWidth,
                    kBoardHeight);
  Controller controller;
  Game game(kBoardWidth / kBlockSize, kBoardHeight / kBlockSize);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}
