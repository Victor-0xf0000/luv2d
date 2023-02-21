#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, const char** argv)
{
  printf("LUV2D ENGINE!\n");
  
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow("Luv2D", SDL_WINDOWPOS_CENTERED, 
      SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  bool should_quit = false;
  
  while (!should_quit)
  {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      switch (e.type)
      {
      case SDL_QUIT:
        should_quit = true;
        break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 40, 4, 30, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  return 0;
}
