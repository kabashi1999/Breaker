#include "SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <vector>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "tile.h"

SDL_Texture* ballTexture = window.loadTexture("res/ball.png");
SDL_Texture* breakerTexture = window.loadTexture("res/breakout_breaker.png");
SDL_Texture* tileLightTexture32 = window.loadTexture("res/tile32_light.png");
//SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");

//TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);

Game::Game(std::size_t grid_width, std::size_t grid_height)
{
  ball = Ball(Vector2f(0, 0), ballTexture);
  breaker = Breaker(Vector2f(0, 0),breakerTexture);
  tiles ={};
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  LoadLevel();
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool init = true;
  
  Uint64 currentTick = SDL_GetPerformanceCounter();
  Uint64 lastTick = 0;
  double deltaTime = 0;

  while (running) {
    
    lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );
    
    
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, breaker);
    breaker.update(deltaTime);
    ball.update(deltaTime, init, breaker, tiles);
    renderer.render(ball);
    renderer.render(breaker);
    for (Tile& t : tiles)
	{ 
		renderer.render(t);
	}

    frame_end = SDL_GetTicks();

    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }


    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void LoadLevel(){
  tiles = LoadTiles();
  balls.setVelocity(1, 1);
  balls.setScale(1, 1);
  balls.setPos(320,320);
  breaker.setScale(1, 1);
  breaker.setPos(320,320);
}

std::vector<Tile> LoadTiles(){
  std::vector<Tile> temp = {};
  for(int i=0;i<10;i++){
   temp.push_back(Tile(Vector2f(32*i,0), tileLightTexture32)); 
  }
  
  return temp;
}





int Game::GetScore() const { return 1; }
int Game::GetSize() const { return 1; }