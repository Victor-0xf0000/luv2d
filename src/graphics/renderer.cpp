#include <engine/graphics/renderer.hpp>
#include <engine/graphics/color.hpp>
#include <engine/graphics/texture.hpp>

#include <engine/window.hpp>
#include <engine/base.hpp>

#include <SDL2/SDL_Image.h>

luv::Renderer::Renderer()
  : sdl_renderer_ptr(nullptr), vsync(false)
{
  
}

luv::Renderer::~Renderer()
{
  SDL_DestroyRenderer(this->sdl_renderer_ptr);
}

void luv::Renderer::create(Ref<luv::Window> window)
{
  // Vsync is unabled by default
  this->sdl_renderer_ptr = SDL_CreateRenderer(window->get_sdl_window(),
      -1, SDL_RENDERER_ACCELERATED);
  if (!this->sdl_renderer_ptr)
  {
    printf("Failed creating renderer! Error: %s\n", SDL_GetError());
  }

  this->vsync = false;
  this->background_color = luv::Color(40, 40, 40, 255);
}

bool luv::Renderer::get_vsync() const
{
  return this->vsync;
}

void luv::Renderer::set_vsync(bool vsync)
{
  this->vsync = vsync;

  // TODO: Save vsync state
  if (SDL_RenderSetVSync(this->sdl_renderer_ptr, vsync) != 0)
  {
    printf("Failed setting vsync! Error: %s\n", SDL_GetError());
    printf("VSYNC may be set when restarting the game.\n");
  }
}


void luv::Renderer::set_background_color(Color color)
{
  this->background_color = color;
}

luv::Ref<luv::Texture> luv::Renderer::loadTexture(const char* path)
{
  luv::Ref<luv::Texture> texture = createRef<luv::Texture>();
  SDL_Texture* sdl_texture = IMG_LoadTexture(this->sdl_renderer_ptr, path);
  if (!sdl_texture)
  {
    fprintf(stderr, "Couldn't load texture %s, error: %s\n", path, SDL_GetError());
    return nullptr;
  }
  texture->sdl_texture_ptr = sdl_texture;
  return texture;
}

void luv::Renderer::begin_render()
{
  SDL_SetRenderDrawColor(this->sdl_renderer_ptr, this->background_color.r, this->background_color.g, 
      this->background_color.b, this->background_color.a);
  SDL_RenderClear(this->sdl_renderer_ptr);
}

void luv::Renderer::render_texture(Ref<Texture> texture, int x, int y, int width, int height)
{
  SDL_Rect dst {x, y, width, height};
  SDL_Rect src {0, 0, width, height};
  SDL_RenderCopy(this->sdl_renderer_ptr, texture->sdl_texture_ptr, &src, &dst);
}
void luv::Renderer::end_render()
{
  SDL_RenderPresent(this->sdl_renderer_ptr);
}
