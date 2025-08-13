#define SOL_ALL_SAFETIES_ON 1

#include <iostream>

#include "Game.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
  // Test the Logger curId functionality
  Logger::Log("First message - should have ID 0");
  Logger::Err("Second message - should have ID 1");
  Logger::Warn("Third message - should have ID 2");
  Logger::Log("Fourth message - should have ID 3");

  // Print the IDs to verify they increment
  for (const auto& entry : Logger::messages) {
    std::cout << "Message ID: " << entry.id << " - " << entry.message
              << std::endl;
  }

  Game game;

  game.Init();

  game.Run();

  game.Destroy();

  return 0;
}
