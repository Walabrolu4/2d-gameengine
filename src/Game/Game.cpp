#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>

#include <glm/glm.hpp>

#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "SDL_timer.h"

Game::Game() { Logger::Log("Game Constructor Called"); }

Game::~Game() { Logger::Log("Game Destructor Called"); }

void Game::Init() {
  // INIT SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::Err("Error Initializing SDL.");
  }

  // Create Window
  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = 800;
  windowHeight = 600;
  window =
      SDL_CreateWindow("DAN-D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       windowWidth, windowHeight, 0);

  if (!window) {
    Logger::Err("Error in creating a window. Please do better. Thank you");
    return;
  }

  // Assign Window to renderer
  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    Logger::Err(
        "Errer in creating SDL Renderer. Please call your administrator");
  }
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  isRunning = true;
}

void Game::Run() {
  Setup();
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::ProcessInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
      case SDL_QUIT:
        isRunning = false;
        return;

      case SDL_KEYDOWN:
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
          isRunning = false;
        }
        break;
    }
  }
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;
void Game::Setup() {
  playerPosition = glm::vec2(10.0, 20.0);
  playerVelocity = glm::vec2(10.0, 5.0);
}

void Game::Update() {
  // If we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
  int timeToWait =
      MILLISECONDS_PER_FRAME - (SDL_GetTicks() - millisecondsForPreviousFrame);

  if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  double deltaTime = (SDL_GetTicks() - millisecondsForPreviousFrame) / 1000.0f;

  millisecondsForPreviousFrame = SDL_GetTicks();
  // std::cout << "frame time is " << millisecsPreviousFrame << ".\n";

  playerPosition.x += playerVelocity.x * deltaTime;
  playerPosition.y += playerVelocity.y * deltaTime;
}

void Game::Render() {
  // Draw Background
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  // Load a PNG as a texture
  SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  // Assign texture to a rectangle
  SDL_Rect destRect = {static_cast<int>(playerPosition.x),
                       static_cast<int>(playerPosition.y), 32, 32};
  SDL_RenderCopy(renderer, texture, NULL, &destRect);
  SDL_DestroyTexture(texture);

  // Swap buffers
  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  // Opposite order of creation
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
