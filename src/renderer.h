#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "breaker.h"

class Renderer{
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  SDL_Texture* loadTexture(const char* p_filePath);
  void cleanUp();
  void clear();
  void render(Entity& p_entity);
  void render(int x, int y, SDL_Texture* p_tex);
  void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
  void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
  void display();

  void Render(Breaker const breaker, SDL_Point[] const &wall);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif