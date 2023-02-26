#include <engine/graphics/renderer.hpp>

#include <engine/window.hpp>

luv::Renderer::Renderer()
  : sdl_renderer_ptr(nullptr), vsync(false)
{
  
}

luv::Renderer::~Renderer()
{
  SDL_DestroyRenderer(this->sdl_renderer_ptr);
}

void luv::Renderer::create(std::shared_ptr<luv::Window> window)
{
  // Vsync is unabled by default
  this->sdl_renderer_ptr = SDL_CreateRenderer(window->get_sdl_window(),
      -1, SDL_RENDERER_ACCELERATED);
  if (!this->sdl_renderer_ptr)
  {
    printf("Failed creating renderer! Error: %s\n", SDL_GetError());
  }

  this->vsync = false;
}

bool luv::Renderer::get_vsync() const
{
  return this->vsync;
}

void luv::Renderer::set_vsync(bool vsync)
{
  this->vsync = vsync;

  // TODO: Save vsync state
  if (!SDL_RenderSetVSync(this->sdl_renderer_ptr, vsync))
  {
    printf("Failed setting vsync! Error: %s\n", SDL_GetError());
    printf("VSYNC may be set when restarting the game.\n");
  }
}
