#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>

#include <glm/glm.hpp>
#include <iostream>

#include "SDL_timer.h"

Game::Game() { std::cout << "Game constructor called \n"; }

Game::~Game() { std::cout << "Game destructor called\n"; }

void Game::Init() {
  // INIT SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error Initializing SDL." << std::endl;
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
    std::cerr << "Error in creating a window. Please do better. Thank you"
              << std::endl;
    return;
  }

  // Assign Window to renderer
  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    std::cerr
        << "Errer in creating SDL Renderer. Please call your administrator"
        << std::endl;
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
  playerVelocity = glm::vec2(1.0, 1.0);
}

void Game::Update() {
  // If we are too fast, waste some time until we reach the MILLISECS_PER_FRAME
  while (!SDL_TICKS_PASSED(
      SDL_GetTicks(), millisecondsForPreviousFrame + MILLISECONDS_PER_FRAME));

  millisecondsForPreviousFrame = SDL_GetTicks();
  // std::cout << "frame time is " << millisecsPreviousFrame << ".\n";

  playerPosition.x += playerVelocity.x;
  playerPosition.y += playerVelocity.y;
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
