#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <engine/graphics/renderer.hpp>
#include <engine/engine.hpp>
#include <engine/window.hpp>
#include <stdio.h>

int main(int argc, const char** argv)
{
  luv::Engine engine;
  engine.start();
  engine.get_renderer()->set_vsync(true);
  engine.get_window()->change_title("LOVELY TEST");
  engine.get_window()->set_resizable(true);
  
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
      case SDL_WINDOWEVENT:
        if (e.window.event == SDL_WINDOWEVENT_RESIZED)
        {
          engine.get_window()->resize(e.window.data1, e.window.data2);
        }
        break;
      }
    }
    
  }

  return 0;
}
