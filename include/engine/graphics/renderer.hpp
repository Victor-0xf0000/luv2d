#pragma once

#include <SDL2/SDL.h>

#include <memory>

namespace luv
{
  struct Window;
  struct Renderer
  {
  private:
    SDL_Renderer* sdl_renderer_ptr;
    
    bool vsync;
  public:
    Renderer();
    ~Renderer();

    void create(std::shared_ptr<luv::Window> window);
    
    bool get_vsync() const;
    void set_vsync(bool vsync);
  };
}
