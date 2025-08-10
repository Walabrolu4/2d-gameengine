#define SOL_ALL_SAFETIES_ON 1

#include "Game.h"

int main(int argc, char* argv[]) {
  Game game;

  game.Init();

  game.Run();

  game.Destroy();

  return 0;
}
